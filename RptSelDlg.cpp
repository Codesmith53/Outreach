// RptSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OutReach.h"
#include "RptSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRptSelDlg dialog


CRptSelDlg::CRptSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRptSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRptSelDlg)
	m_rpt_selection = FIRST_VISIT;
	//}}AFX_DATA_INIT

    m_report_sel = FIRST_VISIT;
}


void CRptSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRptSelDlg)
	DDX_CBIndex(pDX, IDC_SelPrtRpt, m_rpt_selection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRptSelDlg, CDialog)
	//{{AFX_MSG_MAP(CRptSelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRptSelDlg message handlers

