// OutReachDoc.cpp : implementation of the COutReachDoc class
//

#include "stdafx.h"
#include <afx.h>
#include <afxdlgs.h>
#include <strstream> 
#include "OutReach.h"

#include "OutReachDoc.h"
#include "MbrDlg.h"
#include "PrsnRcd.h"
#include "RptSelDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutReachDoc

IMPLEMENT_DYNCREATE(COutReachDoc, CDocument)

BEGIN_MESSAGE_MAP(COutReachDoc, CDocument)
	//{{AFX_MSG_MAP(COutReachDoc)
	ON_COMMAND(ID_EDIT_ADD, OnEditAdd)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_MAINT_HISTORY, OnMaintHistory)
	ON_COMMAND(ID_MAINT_EXPORTOLDFILE, OnMaintExportDos)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_MODIFY, OnEditModify)
	ON_COMMAND(ID_MAINTANCE_MERGE, OnMaintanceMerge)
	ON_COMMAND(ID_MAINTANCE_EXPORTTEXT, OnMaintanceExporttext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutReachDoc construction/destruction

COutReachDoc::COutReachDoc()
{
	long dayofweek;
	current_selection = LB_ERR;
	CTime init_time(1985, 10, 03, 12, 0, 0, -1); // 1985, Oct, 03, 12:00:00

	// determine church start,  noon of a Sunday
	today = CTime::GetCurrentTime();
	dayofweek = today.GetDayOfWeek();
	CTimeSpan days_since_sunday(long(dayofweek - 1), 0, 0, 0);
	CTimeSpan one_week(7, 0, 0, 0);

	// initialize date members
	first_worship = init_time;
	last_worship = today - days_since_sunday;
	LastSundayStr = last_worship.Format("%B %d, %Y");

	// get a list of the last 52 sundays
	int cnt;
	YearOfSundays[0] = last_worship;
	for (cnt = 1; cnt < 52; cnt++)
	{
		YearOfSundays[cnt] = YearOfSundays[cnt - 1] - one_week;
	}
	int monthcnt;
	int month = 13;
	for (cnt = 0, monthcnt = 0; cnt < 52; cnt++)
	{
		if (month != YearOfSundays[cnt].GetMonth())
		{
			month = YearOfSundays[cnt].GetMonth();
			MonthsList[monthcnt] = YearOfSundays[cnt].Format("%b");
			monthcnt++;
		}
	}

	for (cnt = 0; cnt < 13; cnt++)
	{
		MonthsStr += MonthsList[cnt];
		MonthsStr += "   ";
	}

	database_active = false;

}

/////////////////////////////////////////////////////////////////////////////
COutReachDoc::~COutReachDoc()
{
	database_active = false;
}


/////////////////////////////////////////////////////////////////////////////
BOOL COutReachDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutReachDoc serialization

void COutReachDoc::Serialize(CArchive& ar)
{
	PersonArray.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		current_selection = 0;
		database_active = true;
		UpdateAllViews(NULL, 0, NULL);
		SetModifiedFlag();
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutReachDoc diagnostics

#ifdef _DEBUG
void COutReachDoc::AssertValid() const
{
	CDocument::AssertValid();
	ASSERT_VALID(&PersonArray);
}

void COutReachDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
	dc << PersonArray;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutReachDoc commands

void COutReachDoc::OnEditAdd()
{
	CMbrDlg addDlg;
	if (addDlg.DoModal() == IDOK)
	{
		AddPrsn(addDlg.m_name, addDlg.m_address, addDlg.m_city, addDlg.m_state,
			addDlg.m_zip, addDlg.m_phone, addDlg.m_email, addDlg.m_status, "", "");
		UpdateAllViews(NULL);
	}

}
/////////////////////////////////////////////////////////////////////////////
// COutReachDoc functions

void COutReachDoc::AddPrsn(CString n, CString a, CString c, CString s,
	CString z, CString p, CString e,
	int  m, CString atd, CString pnote)
{
	int pos;
	CPrsnRcd *prsn;

	PersonArray.Add(new CPrsnRcd(n, a, c, s, z, p, e, m, atd, pnote));
	pos = PersonArray.GetSize();
	prsn = (CPrsnRcd *)PersonArray.GetAt(pos - 1);
	prsn->SetFirstVisit(last_worship);
	prsn->SetLastVisit(last_worship);
	prsn->AddToAttedance(last_worship);
	SortPersons();
	SetModifiedFlag();
}

/////////////////////////////////////////////////////////////////////////////
int COutReachDoc::NumPrsn()
{
	return PersonArray.GetSize();
}

////////////////////////////////////////////////////////////////////////////
void COutReachDoc::GetPrsn(int x, CPrsnRcd &prsn)
{
	((CPrsnRcd *)PersonArray.GetAt(x))->GetPrsn(prsn);
}

/////////////////////////////////////////////////////////////////////////////
CPrsnRcd* COutReachDoc::GetPrsn(int x)
{
	return (CPrsnRcd *)(PersonArray.GetAt(x));
}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::DeleteContents()
{
	int x;
	for (x = 0; x < PersonArray.GetSize(); x++)
		delete(PersonArray.GetAt(x));
	PersonArray.RemoveAll();
	CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::OnEditDelete()
{
	// TODO: Add your command handler code here
	if (current_selection != LB_ERR)
	{
		delete PersonArray.GetAt(current_selection);
		PersonArray.RemoveAt(current_selection);
		current_selection--;
		UpdateAllViews(NULL, 0, NULL);
		SetModifiedFlag();
		current_selection = LB_ERR;
	}

}
/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::OnMaintExportDos()
{
	CStdioFile outfile;
	CFileException execpt;
	int f_status;
	CString rec;
	CPrsnRcd* person;

	CString filefilter("History Files (*.lst)|*.lst|");
	CString fileext("lst");
	CFileDialog fileDialog(TRUE, fileext, NULL, OFN_PATHMUSTEXIST, filefilter);

	if (fileDialog.DoModal() == IDOK)
	{
		f_status = outfile.Open(fileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite, &execpt);

		if (!f_status)
		{
			AfxMessageBox("Export File file error!");
			return;
		}
	}

	int rcd_cnt = 0;
	while (rcd_cnt < PersonArray.GetSize())
	{
		person = (CPrsnRcd *)PersonArray.GetAt(rcd_cnt++);
		outfile.WriteString(person->GetPersonStr(last_worship));
	}
	outfile.Close();

}
/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::OnMaintanceExporttext()
{
	CStdioFile outfile;
	CFileException execpt;
	int f_status;
	CString rec;
	CPrsnRcd* person;

	CString filefilter("Text Files (*.txt)|*.txt|");
	CString fileext("txt");
	CFileDialog fileDialog(TRUE, fileext, NULL, OFN_PATHMUSTEXIST, filefilter);

	if (fileDialog.DoModal() == IDOK)
	{
		f_status = outfile.Open(fileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite, &execpt);

		if (!f_status)
		{
			AfxMessageBox("Text Export file error!");
			return;
		}
	}
	outfile.WriteString("Name;Street;City;State;Zip;Phone;Email;Attendance;Notes;Last Visit;Visits-->\n");
	int rcd_cnt = 0;
	while (rcd_cnt < PersonArray.GetSize())
	{
		person = (CPrsnRcd *)PersonArray.GetAt(rcd_cnt++);
		outfile.WriteString(person->GetPersonExportStr(last_worship, ';'));
	}
	outfile.Close();

}
/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::OnMaintHistory()
{
	CStdioFile infile;
	CFileException execpt;
	int f_status;
	CString rec;
	CPrsnRcd* person;

	CString filefilter("History Files (*.lst)|*.lst|");
	CString fileext("lst");
	CFileDialog fileDialog(TRUE, fileext, NULL, OFN_FILEMUSTEXIST, filefilter);

	if (fileDialog.DoModal() == IDOK)
	{
		f_status = infile.Open(fileDialog.GetPathName(), CFile::modeRead, &execpt);

		if (!f_status)
		{
			AfxMessageBox("History file error!");
			return;
		}
	}
	int rcd_cnt = 0;
	while ((infile.ReadString(rec)) != NULL)
	{
		rcd_cnt++;
		person = new CPrsnRcd(rec);
		// here;
		person->SetAttedance(last_worship);
		PersonArray.Add(person);   // add the history record
	}

	if (rcd_cnt)
	{
		database_active = true;
	}

	SetModifiedFlag();
	UpdateAllViews(NULL);
	infile.Close();

}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::OnMaintanceMerge()
{
	// sets flag so data stream uses older database for input file data
	if (OldFileUpdate == FALSE) OldFileUpdate = TRUE;
	else OldFileUpdate = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::OnEditFind()
{
	// TODO: Add your command handler code here
	CMbrDlg addDlg;
	CString searchString;
	bool cs = false;

	if (addDlg.DoModal() == IDOK)
	{
		if (addDlg.s_case) cs = true;

		if (!addDlg.m_name.IsEmpty())
		{
			searchString = addDlg.m_name;
			FindName(searchString,cs);
		}
		else if (!addDlg.m_address.IsEmpty())
		{
			searchString = addDlg.m_address;
			FindAddress(searchString);
		}
		else if (!addDlg.m_phone.IsEmpty())
		{
			searchString = addDlg.m_phone;
			FindPhone(searchString);
		}
		else if (!addDlg.m_email.IsEmpty())
		{
			searchString = addDlg.m_email;
			FindEmail(searchString);
		}
		else
		{
			AfxMessageBox("Use Name, Address, Phone or email only for search!");
			searchString.Empty();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::OnEditModify()
{
	// TODO: Add your command handler code here
	CMbrDlg addDlg;

	if (current_selection != LB_ERR)
	{
		PersonArray.GetAt(current_selection);
		if (addDlg.DoModal() == IDOK)
		{
			UpdateAllViews(NULL, 0, NULL);
			SetModifiedFlag();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::FindName(CString n, bool cs)
{
	int x;
	CPrsnRcd p;

	CString DBPrsn,SPrsn;

	for (x = 0; x < PersonArray.GetSize(); x++)
	{
		p = *(CPrsnRcd *)PersonArray.GetAt(x);

		if (!cs)
		{
			DBPrsn = p.GetName().MakeLower();
			SPrsn = n.MakeLower();
		}
		else
		{
			DBPrsn = p.GetName();
			SPrsn = n;
		}

		if (DBPrsn.Find(SPrsn) >= 0)
		{
			current_selection = x;
			UpdateAllViews(NULL, 0, NULL);
			SetModifiedFlag();
			return;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::FindAddress(CString a)
{
	int x;
	CPrsnRcd p;
	CString DBPrsn;

	for (x = 0; x < PersonArray.GetSize(); x++)
	{
		p = *(CPrsnRcd *)PersonArray.GetAt(x);

		DBPrsn = p.GetAddress().MakeLower();

		if (DBPrsn.Find(a.MakeLower()) >= 0)
		{
			current_selection = x;
			UpdateAllViews(NULL, 0, NULL);
			SetModifiedFlag();
			return;
		}

	}
}
/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::FindPhone(CString ph)
{
	int x;
	CPrsnRcd p;
	CString DBPrsn;

	for (x = 0; x < PersonArray.GetSize(); x++)
	{
		p = *(CPrsnRcd *)PersonArray.GetAt(x);

		DBPrsn = p.GetPhone().MakeLower();

		if (DBPrsn.Find(ph.MakeLower()) >= 0)
		{
			current_selection = x;
			UpdateAllViews(NULL, 0, NULL);
			SetModifiedFlag();
			return;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::FindEmail(CString email)
{
	int x;
	CPrsnRcd p;
	CString DBPrsn;

	for (x = 0; x < PersonArray.GetSize(); x++)
	{
		p = *(CPrsnRcd *)PersonArray.GetAt(x);

		DBPrsn = p.GetEmail().MakeLower();

		if (DBPrsn.Find(email.MakeLower()) >= 0)
		{
			current_selection = x;
			UpdateAllViews(NULL, 0, NULL);
			SetModifiedFlag();
			return;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::GetRptSel(int sel, CReport *rpt)
{
	CPrsnRcd *person;
	CTimeSpan one_day(1, 0, 0, 0);
	CTimeSpan four_weeks((4 * 7), 0, 0, 0);
	CTimeSpan eight_weeks((8 * 7), 0, 0, 0);
	int rtn_position = -1;
	rpt_summary_data_t summary;

	summary.member_cnt = 0;
	summary.total_attendance = 0;
	summary.total_first_visit_cnt = 0;
	summary.total_member_cnt = 0;
	summary.total_rec_cnt = 0;
	summary.total_visitor_cnt = 0;
	summary.visitor_cnt = 0;

	if (database_active == true)
	{
		int cnt;

		switch (sel)
		{
		case CRptSelDlg::FIRST_VISIT:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				// add one day to correct for service time and data entry.
				if (((person->GetFirstVisit()) + one_day) > last_worship &&
					person->IsMember() != 1)
				{
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::SECOND_VISIT:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				// first visit does not add to total visits.
				if (person->GetVisitCnt() == 2 &&
					person->GetLastVisit() + one_day > last_worship  &&
					person->IsMember() != 1)
				{
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::THIRD_VISIT:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				// first visit does not add to total visits.
				if (person->GetVisitCnt() == 3 &&
					person->GetLastVisit() + one_day > last_worship   &&
					person->IsMember() != 1)
				{
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::MISSED_FOUR:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if ((last_worship - four_weeks) > person->GetLastVisit() && person->GetAttendPercent() > float(0.30))
				{
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::MISSED_EIGHT:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if ((last_worship - eight_weeks) > person->GetLastVisit() && person->GetAttendPercent() > float(0.30))
				{
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::ATTEND_OFTEN:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if (person->GetAttendPercent() > float(0.49) && person->IsMember() != 1 && person->GetVisitCnt() >= 4)
				{
					person->UpdateAttedanceStr(last_worship);
					person->UpdateAttedance();
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::ALL_MEMBERS:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if (person->IsMember() == 1)
				{
					person->UpdateAttedanceStr(last_worship);
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::ALL_VISITORS:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if (person->IsMember() != 1)
				{
					person->UpdateAttedanceStr(last_worship);
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::ALL_CONSTITUENT:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if (person->GetMember() == 4)
				{
					person->UpdateAttedanceStr(last_worship);
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::BULK_MAIL:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if (person->GetAttendPercent() > float(0.30) && person->IsMember() != 1 && person->GetPossibleCnt() >= 8 &&
					person->GetPossibleCnt() < 30 && ((person->GetState() == "") || (person->GetState() == "WA")))
				{
					person->UpdateAttedanceStr(last_worship);
					rpt->AddPerson(person);
				}
			}

			break;

		case CRptSelDlg::EVERYONE:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				rpt->AddPerson(person);
			}
			break;

		case CRptSelDlg::NOTES_REPORT:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				CString tempStr;
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				tempStr = person->GetNote();
				if (!tempStr.IsEmpty())
				{
					person->UpdateAttedanceStr(last_worship);
					rpt->AddPerson(person);
				}
			}
			break;

		case CRptSelDlg::SERVICE_DATE:
			for (cnt = 0; cnt < PersonArray.GetSize(); cnt++)
			{
				person = (CPrsnRcd *)PersonArray.GetAt(cnt);
				if (person->Visited(last_worship))
				{
					person->UpdateAttedanceStr(last_worship);
					rpt->AddPerson(person);
				}
			}
			break;

		}

		// report summary data 
		int  i;
		summary.total_rec_cnt = PersonArray.GetSize();
		for (i = 0; i < summary.total_rec_cnt; i++)
		{
			person = (CPrsnRcd *)PersonArray.GetAt(i);

			if (person->IsMember() != 1)
			{
				summary.total_visitor_cnt++;
				if (person->Visited(last_worship))
				{
					summary.total_attendance++;
					summary.visitor_cnt++;
				}
				if (((person->GetFirstVisit()) + one_day) > last_worship)
				{
					summary.total_first_visit_cnt++;
				}
			}
			else
			{
				summary.total_member_cnt++;
				if (person->Visited(last_worship))
				{
					summary.total_attendance++;
					summary.member_cnt++;
				}
			}
		}
		rpt->SetSummary(summary);
	}
}
/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::UpdateDocViews()
{
	UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::SetWorshipDate(CTime date)
{
	last_worship = date;
	LastSundayStr = last_worship.Format("%B %d, %Y");
	UpdateAllViews(NULL);

}

/////////////////////////////////////////////////////////////////////////////
void COutReachDoc::SortPersons()
{
	CPrsnRcd *temp;
	int p, j;
	CString one, two;

	for (p = 1; p < PersonArray.GetSize(); p++)
	{
		temp = (CPrsnRcd *)PersonArray.GetAt(p);

		for (j = p; j > 0 && CString(temp->GetName()) < CString(((CPrsnRcd *)(PersonArray[j - 1]))->GetName()); j--)
		{
			PersonArray[j] = PersonArray[j - 1];
		}
		PersonArray[j] = temp;
	}
}
