#if !defined(AFX_RPTSELDLG_H__22F58821_32F1_11D3_BC71_44455354616F__INCLUDED_)
#define AFX_RPTSELDLG_H__22F58821_32F1_11D3_BC71_44455354616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RptSelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRptSelDlg dialog

class CRptSelDlg : public CDialog
{
// Construction
public:
	CRptSelDlg(CWnd* pParent = NULL);   // standard constructor

	enum
	{
		FIRST_VISIT = 0,
		SECOND_VISIT = 1,
		THIRD_VISIT = 2,
		MISSED_FOUR = 3,
		MISSED_EIGHT = 4,
		ATTEND_OFTEN = 5,
		ALL_VISITORS = 6,
		ALL_MEMBERS = 7,
		BULK_MAIL = 8,
		EVERYONE = 9,
		SERVICE_DATE = 10,
		ALL_CONSTITUENT = 11,
		NOTES_REPORT = 12
        };

// Dialog Data
	//{{AFX_DATA(CRptSelDlg)
	enum { IDD = IDD_SelRpt };
	int		m_rpt_selection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRptSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

    int m_report_sel;

protected:

	// Generated message map functions
	//{{AFX_MSG(CRptSelDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RPTSELDLG_H__22F58821_32F1_11D3_BC71_44455354616F__INCLUDED_)
