// OutReachView.cpp : implementation of the COutReachView class
//

#include "stdafx.h"
#include "OutReach.h"

#include "OutReachDoc.h"
#include "OutReachView.h"
#include "RptSelDlg.h"
#include <winspool.h>

#include <strstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutReachView

IMPLEMENT_DYNCREATE(COutReachView, CFormView)

BEGIN_MESSAGE_MAP(COutReachView, CFormView)
	//{{AFX_MSG_MAP(COutReachView)
	ON_LBN_SELCANCEL(IDC_LIST1, OnSelcancelList1)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_LBN_SETFOCUS(IDC_LIST1, OnSetfocusList1)
	ON_EN_CHANGE(IDC_Notes, OnChangeNotes)
	ON_BN_CLICKED(IDC_UpdateRec, OnUpdateRec)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_AddSelAttendance, OnAddSelAttendance)
	ON_BN_CLICKED(IDC_DelSelAttendance, OnDelSelAttendance)
	ON_BN_CLICKED(IDC_FindRec, OnFindRecButton)
	ON_BN_CLICKED(IDC_DeleteRec, OnDeleteRecButton)
	ON_BN_CLICKED(IDC_NewRec, OnNewRecButton)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_EN_CHANGE(IDC_Email, &COutReachView::OnEnChangeEmail)
	ON_EN_CHANGE(IDC_Phone, &COutReachView::OnEnChangePhone)
	ON_EN_CHANGE(IDC_Name, &COutReachView::OnEnChangeName)
	ON_EN_CHANGE(IDC_Address, &COutReachView::OnEnChangeAddress)
	ON_EN_CHANGE(IDC_StateMain, &COutReachView::OnEnChangeState)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutReachView construction/destruction

COutReachView::COutReachView()
	: CFormView(COutReachView::IDD)
{
	//{{AFX_DATA_INIT(COutReachView)
	m_name = _T("");
	m_phone = _T("");
	m_email = _T("");
	m_zip = _T("");
	m_address = _T("");
	m_city = _T("");
	m_state = _T("WA");
	m_member_total = 0;
	m_total_records = 0;
	m_vistor_total = 0;
	m_w_attendance = _T("");
	m_current_service = _T("");
	m_1service = 0;
	m_2service = 0;
	m_status = _T("");
	m_record = 0;
	m_Attend_Per = 0.0f;
	m_CalSelDate = CTime::GetCurrentTime();
	m_note = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

COutReachView::~COutReachView()
{
}

void COutReachView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutReachView)
	DDX_Control(pDX, IDC_Status, m_status_ctrl);
	DDX_Control(pDX, IDC_Worship_Attend, m_attend_ctrl);
	DDX_Control(pDX, IDC_Notes, m_notes_ctrl);
	DDX_Control(pDX, IDC_Phone, m_phone_ctrl);
	DDX_Control(pDX, IDC_Email, m_email_ctrl);
	DDX_Control(pDX, IDC_Zip, m_zip_ctrl);
	DDX_Control(pDX, IDC_City, m_city_ctrl);
	DDX_Control(pDX, IDC_Address, m_address_ctrl);
	DDX_Control(pDX, IDC_StateMain, m_state_ctrl);
	DDX_Control(pDX, IDC_Name, m_name_ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_service_date_ctrl);
	DDX_Control(pDX, IDC_HUMC_bitmap, m_humc_bitmap);
	DDX_Control(pDX, IDC_LIST1, m_mlist);

	DDX_Text(pDX, IDC_Name, m_name);
	DDV_MaxChars(pDX, m_name, 20);
	DDX_Text(pDX, IDC_Phone, m_phone);
	DDV_MaxChars(pDX, m_phone, 13);
	DDX_Text(pDX, IDC_Email, m_email);
	DDV_MaxChars(pDX, m_email, 36);
	DDX_Text(pDX, IDC_Zip, m_zip);
	DDV_MaxChars(pDX, m_zip, 5);
	DDX_Text(pDX, IDC_Address, m_address);
	DDV_MaxChars(pDX, m_address, 28);
	DDX_Text(pDX, IDC_City, m_city);
	DDV_MaxChars(pDX, m_city, 40);
	DDX_Text(pDX, IDC_StateMain, m_state);
	DDV_MaxChars(pDX, m_city, 40);
	DDX_Text(pDX, IDC_Member_total, m_member_total);
	DDV_MinMaxUInt(pDX, m_member_total, 0, 200000);
	DDX_Text(pDX, IDC_total_records, m_total_records);
	DDV_MinMaxUInt(pDX, m_total_records, 0, 200000);
	DDX_Text(pDX, IDC_Vistor_total, m_vistor_total);
	DDV_MinMaxUInt(pDX, m_vistor_total, 0, 200000);
	DDX_Text(pDX, IDC_Worship_Attend, m_w_attendance);
	DDV_MaxChars(pDX, m_w_attendance, 52);
	DDX_Text(pDX, IDC_Current_Service, m_current_service);
	DDV_MaxChars(pDX, m_current_service, 18);
	DDX_Text(pDX, IDC_1service_total, m_1service);
	DDV_MinMaxUInt(pDX, m_1service, 0, 2000);
	DDX_Text(pDX, IDC_2service_total, m_2service);
	DDV_MinMaxUInt(pDX, m_2service, 0, 2000);
	DDX_Text(pDX, IDC_Status, m_status);
	DDV_MaxChars(pDX, m_status, 8);
	DDX_Text(pDX, IDC_Record, m_record);
	DDV_MinMaxUInt(pDX, m_record, 0, 20000);
	DDX_Text(pDX, IDC_Attend_Per, m_Attend_Per);
	DDV_MinMaxFloat(pDX, m_Attend_Per, 0.f, 100.f);
	DDX_Text(pDX, IDC_Notes, m_note);
	//}}AFX_DATA_MAP
}

BOOL COutReachView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutReachView printing

BOOL COutReachView::OnPreparePrinting(CPrintInfo* pInfo)
{

	CRptSelDlg m_rptSel;
	UINT num_pages;

	// clear all storage
	rpt.Clear();

	if (m_rptSel.DoModal() == IDOK)
	{
		format_report(m_rptSel.m_rpt_selection);
	}

	num_pages = (rpt.GetTotalRcd() / REC_PER_PAGE) + 1;
	pInfo->SetMaxPage(num_pages);

	// default preparation
	return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{

	int        i, nHeight;
	int        rpt_cnt;
	CString    str, rcdstr, month_header;
	CFont      font;
	TEXTMETRIC tm;

	// get the number of records
	rpt_cnt = rpt.GetPrsnCnt();

	// set the report record to the 1st record of the page
	rpt.SetCurrentRcd(int((pInfo->m_nCurPage - 1) * REC_PER_PAGE));

	// get the doc object
	COutReachDoc *pDoc = GetDocument();

	pDC->SetMapMode(MM_TWIPS);

	// Print the database 0.5 inch down and over;
	//  use 10-point Fixedsys
	font.CreateFont(-160, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN,
		"Courier New");

	pSysFont = (CFont*)pDC->SelectObject(&font);

	pDC->GetTextMetrics(&tm);
	nHeight = tm.tmHeight + tm.tmExternalLeading;

	// print header
	pDC->TextOut(7, 10, CString(rpt.GetHeader() + " " + m_current_service));
	//   pDC->TextOut((720/4)*50, 2 * nHeight - 720, rpt.GetMonthString( pDoc->GetLastWorshipDate() ) );

	   // print body
	for (i = 0; i < REC_PER_PAGE; i++)
	{
		if (rpt.GetCurrentRcd() < rpt.GetTotalRcd() &&
			rpt.GetCurrentRcd() < int(REC_PER_PAGE * pInfo->m_nCurPage))
		{
			pDC->TextOut(720, -i * nHeight - 720, rpt.GetRcdString(pDoc->GetLastWorshipDate()));
			rpt.SetCurrentRcd(rpt.GetCurrentRcd() + 1);
		}
	}
	// print footer, skip a line
	for (i = 1; i < 7; i++)
		pDC->TextOut(720, -(REC_PER_PAGE + i) * nHeight - 720, rpt.Summary[i - 1]);

	str.Format("%s%d", rpt.GetFooter(), pInfo->m_nCurPage);
	pDC->TextOut(14, -(REC_PER_PAGE + i + 1) * nHeight - 720, str);

	// reset the system font
	pDC->SelectObject(pSysFont);


}

/////////////////////////////////////////////////////////////////////////////
// COutReachView diagnostics

#ifdef _DEBUG
void COutReachView::AssertValid() const
{
	CFormView::AssertValid();
}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

/////////////////////////////////////////////////////////////////////////////
COutReachDoc* COutReachView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutReachDoc)));
	return (COutReachDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutReachView message handlers
/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	COutReachDoc *pDoc = GetDocument();
	int x, records;
	CString rec;

	records = pDoc->NumPrsn();
	if (records)
	{
		m_mlist.ResetContent();
		for (x = 0; x < pDoc->NumPrsn(); x++)
		{
			CString n;
			pDoc->GetPrsn(x)->GetName(n);
			m_mlist.AddString(n);
		}

		m_mlist.SetCurSel(pDoc->GetSelection());
		m_record = m_mlist.GetCurSel() + 1;
		DisplayCurrentPerson();
	}
	else
	{
		pDoc->SetSelection(LB_ERR);
		m_mlist.ResetContent();
	}

	m_current_service = GetDocument()->GetLastWorship();
}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	pDC->SetMapMode(MM_TWIPS);
	CFormView::OnPrepareDC(pDC, pInfo);
}
/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnInitialUpdate()
{
	COutReachDoc *pDoc = GetDocument();
	CFormView::OnInitialUpdate();

	// Set the current selected service
	m_current_service = pDoc->GetLastWorship();
}

/////////////////////////////////////////////////////////////////////////////
BOOL COutReachView::OnInitDialog()
{
	const int NUM_TABS = 2;
	int tabs[NUM_TABS] = { 30, 60 };
	COutReachDoc *pDoc = GetDocument();
	CTime WDate;

	// Set five tab stops
	WDate = pDoc->GetLastWorshipDate();
	m_mlist.SetTabStops(NUM_TABS, tabs);
	m_service_date_ctrl.SetTime(&WDate);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnSelcancelList1()
{
	// TODO: Add your control notification handler code here
	GetDocument()->SetSelection(LB_ERR);
}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnSelchangeList1()
{

	// set the current selection
	GetDocument()->SetSelection(m_mlist.GetCurSel());
	DisplayCurrentPerson();

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnSetfocusList1()
{
	// TODO: Add your control notification handler code here
	GetDocument()->SetSelection(m_mlist.GetCurSel());
	m_record = m_mlist.GetCurSel() + 1;

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::DisplayCurrentPerson()
{
	CPrsnRcd* prsn;
	int mem;
	CString state;
	int select;

	// get person members for display
	select = GetDocument()->GetSelection();

	// ensure selection is valid
	if (select >= 0)
	{
		prsn = GetDocument()->GetPrsn(select);

		prsn->GetName(m_name);
		prsn->GetAddress(m_address);
		prsn->GetCity(m_city);
		prsn->GetState(state);
		prsn->GetZip(m_zip);
		prsn->GetPhone(m_phone);
		prsn->GetEmail(m_email);
		prsn->GetState(m_state);
		prsn->GetMember(mem);
		m_w_attendance = prsn->GetAttedanceStr(GetDocument()->GetLastWorshipDate());
		prsn->GetNote(m_note);

		m_name.TrimLeft();
		m_address.TrimLeft();
		m_city.TrimLeft();
		state.TrimLeft();
		m_zip.TrimLeft();
		m_phone.TrimLeft();
		m_state.TrimLeft();
		m_email.TrimLeft();
		m_w_attendance.TrimLeft();
		m_note.TrimLeft();


		m_Attend_Per = (prsn->GetAttendPercent() * float(100.0));

		if (mem == 1)       m_status = "Member";
		else if (mem == 2) m_status = "Vistor";
		else if (mem == 4) m_status = "Constituent";
		else if (mem == 8) m_status = "Inactive";

		m_record = m_mlist.GetCurSel() + 1;

		m_total_records = GetDocument()->NumPrsn();

		UpdateData(false);
	}

}
/////////////////////////////////////////////////////////////////////////////

void COutReachView::OnChangeNotes()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.

	// TODO: Add your control notification handler code here
	// add note processing here, send to doc class
}
/////////////////////////////////////////////////////////////////////////////

void COutReachView::format_report(int sel)
{
	COutReachDoc *pDoc = GetDocument();

	switch (sel)
	{
	case CRptSelDlg::FIRST_VISIT:
		rpt.SetHeader(" **First Time Visitor Report**  ");
		pDoc->GetRptSel(CRptSelDlg::FIRST_VISIT, &rpt);
		break;

	case CRptSelDlg::SECOND_VISIT:
		rpt.SetHeader(" **Second Time Visitor Report**  ");
		pDoc->GetRptSel(CRptSelDlg::SECOND_VISIT, &rpt);
		break;

	case CRptSelDlg::THIRD_VISIT:
		rpt.SetHeader(" **Third Time Visitor Report**  ");
		pDoc->GetRptSel(CRptSelDlg::THIRD_VISIT, &rpt);
		break;

	case CRptSelDlg::MISSED_FOUR:
		rpt.SetHeader(" **Missed Four Services in a Row Report**  ");
		pDoc->GetRptSel(CRptSelDlg::MISSED_FOUR, &rpt);
		break;

	case CRptSelDlg::MISSED_EIGHT:
		rpt.SetHeader(" **Missed Eight Services in a Row Report**  ");
		pDoc->GetRptSel(CRptSelDlg::MISSED_EIGHT, &rpt);
		break;

	case CRptSelDlg::ATTEND_OFTEN:
		rpt.SetHeader(" **Attend Often Report**  ");
		pDoc->GetRptSel(CRptSelDlg::ATTEND_OFTEN, &rpt);
		break;

	case CRptSelDlg::ALL_VISITORS:
		rpt.SetHeader(" **All Visitors Report**  ");
		pDoc->GetRptSel(CRptSelDlg::ALL_VISITORS, &rpt);
		break;

	case CRptSelDlg::ALL_MEMBERS:
		rpt.SetHeader(" **All Members Report**  ");
		pDoc->GetRptSel(CRptSelDlg::ALL_MEMBERS, &rpt);
		break;

	case CRptSelDlg::ALL_CONSTITUENT:
		rpt.SetHeader(" **All Constituent Report**  ");
		pDoc->GetRptSel(CRptSelDlg::ALL_CONSTITUENT, &rpt);
		break;

	case CRptSelDlg::BULK_MAIL:
		rpt.SetHeader(" **Bulk mail printout**  ");
		pDoc->GetRptSel(CRptSelDlg::BULK_MAIL, &rpt);
		break;

	case CRptSelDlg::NOTES_REPORT:
		rpt.SetHeader(" **Note field printout**  ");
		pDoc->GetRptSel(CRptSelDlg::NOTES_REPORT, &rpt);
		break;

	case CRptSelDlg::EVERYONE:
		rpt.SetHeader(" **Complete Database printout**  ");
		pDoc->GetRptSel(CRptSelDlg::EVERYONE, &rpt);
		break;

	case CRptSelDlg::SERVICE_DATE:
		rpt.SetHeader(" **Attended Selected Service printout**  ");
		pDoc->GetRptSel(CRptSelDlg::SERVICE_DATE, &rpt);
		break;


	}

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnUpdateRec()
{

	CPrsnRcd* prsn;
	char temp;
	COutReachDoc *pDoc = GetDocument();


	// get person members for display
	int select = pDoc->GetSelection();

	if (select > -1)
	{
		// get the current person
		prsn = GetDocument()->GetPrsn(select);

		// change name
		m_name_ctrl.GetWindowText(m_name);
		prsn->SetName(m_name);

		// change address
		m_address_ctrl.GetWindowText(m_address);
		prsn->SetAddress(m_address);

		// change city
		m_city_ctrl.GetWindowText(m_city);
		prsn->SetCity(m_city);

		// change zip
		m_zip_ctrl.GetWindowText(m_zip);
		prsn->SetZip(m_zip);

		// change phone
		m_phone_ctrl.GetWindowText(m_phone);
		prsn->SetPhone(m_phone);

		// change state
		m_state_ctrl.GetWindowText(m_state);
		prsn->SetState(m_state);

		// change email
		m_email_ctrl.GetWindowText(m_email);
		prsn->SetEmail(m_email);

		// change notes
		m_notes_ctrl.GetWindowText(m_note);
		prsn->SetNote(m_note);

		// change status
		int status = 2;
		m_status_ctrl.GetWindowText(m_status);
		temp = m_status.GetAt(0);

		if (temp == 'M' || temp == 'm') status = 1;
		else if (temp == 'V' || temp == 'v') status = 2;
		else if (temp == 'C' || temp == 'c') status = 4;
		else if (temp == 'I' || temp == 'i') status = 8;

		prsn->SetMember(status);
	}

	// update the dialog
	UpdateData(false);
	pDoc->UpdateDocViews();
}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{

	CTime ct;
	COutReachDoc *pDoc = GetDocument();

	m_service_date_ctrl.GetTime(ct);

	// set the current worship date
	pDoc->SetWorshipDate(ct);

	// update the dialog
	UpdateData(false);

	*pResult = 0;
}


/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnAddSelAttendance()
{
	int select;
	CPrsnRcd* prsn;
	COutReachDoc *pDoc = GetDocument();
	CString test;

	// get person members for display
	select = pDoc->GetSelection();

	// ensure selection is valid
	if (select >= 0)
	{
		prsn = pDoc->GetPrsn(select);
		prsn->AddToAttedance(pDoc->GetLastWorshipDate());
		test = prsn->GetAttedanceStr(pDoc->GetLastWorshipDate());
		pDoc->UpdateDocViews();
	}

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnDelSelAttendance()
{
	int select;
	CPrsnRcd* prsn;
	COutReachDoc *pDoc = GetDocument();

	// get person members for display
	select = pDoc->GetSelection();

	// ensure selection is valid
	if (select >= 0)
	{
		prsn = pDoc->GetPrsn(select);
		prsn->DeleteAttedance(pDoc->GetLastWorshipDate());
		pDoc->UpdateDocViews();
	}

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnFindRecButton()
{
	COutReachDoc *pDoc = GetDocument();
	pDoc->DoFindPerson();
}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnDeleteRecButton()
{
	COutReachDoc *pDoc = GetDocument();
	pDoc->DoDelPerson();

}

/////////////////////////////////////////////////////////////////////////////
void COutReachView::OnNewRecButton()
{
	COutReachDoc *pDoc = GetDocument();
	pDoc->DoAddPerson();

}


void COutReachView::OnEnChangeEmail()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void COutReachView::OnEnChangePhone()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void COutReachView::OnEnChangeName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	m_name_ctrl.GetWindowText(m_name);
}


void COutReachView::OnEnChangeAddress()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void COutReachView::OnEnChangeState()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}