// MbrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OutReach.h"
#include "MbrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMbrDlg dialog


CMbrDlg::CMbrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMbrDlg::IDD, pParent)
	, s_case(false)
{
	//{{AFX_DATA_INIT(CMbrDlg)
	m_name = _T("");
	m_city = _T("");
	m_address = _T("");
	m_phone = _T("");
	m_email = _T("");
	m_zip = _T("");
	m_state = _T("");
	//}}AFX_DATA_INIT

   m_member = false;
   m_visitor = true;
   m_constituent = false;
   m_inactive = false;
   m_status = 2;
   s_case = false;
}


void CMbrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMbrDlg)
	DDX_Text(pDX, IDC_EDIT_Name, m_name);
	DDV_MaxChars(pDX, m_name, 20);
	DDX_Text(pDX, IDC_EDIT_City, m_city);
	DDV_MaxChars(pDX, m_city, 16);
	DDX_Text(pDX, IDC_EDIT_Address, m_address);
	DDV_MaxChars(pDX, m_address, 28);
	DDX_Text(pDX, IDC_EDIT_Phone, m_phone);
	DDV_MaxChars(pDX, m_phone, 13);
	DDX_Text(pDX, IDC_EDIT_Email, m_email);
	DDV_MaxChars(pDX, m_email, 36);
	DDX_Text(pDX, IDC_EDIT_Zip, m_zip);
	DDV_MaxChars(pDX, m_zip, 5);
	DDX_Text(pDX, IDC_EDIT_State, m_state);
	DDV_MaxChars(pDX, m_state, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMbrDlg, CDialog)
	//{{AFX_MSG_MAP(CMbrDlg)
	ON_BN_CLICKED(IDC_MemberFlag, OnMemberFlag)
	ON_BN_CLICKED(IDC_InactiveFlag, OnInactiveFlag)
	ON_BN_CLICKED(IDC_VisitorFlag, OnVisitorFlag)
	ON_BN_CLICKED(IDC_ConstituentFlag, OnConstituentFlag)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_Phone, &CMbrDlg::OnEnChangeEditPhone)
	ON_BN_CLICKED(IDC_CaseSenFind, &CMbrDlg::OnBnClickedCasesenfind)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbrDlg message handlers

void CMbrDlg::OnMemberFlag() 
{
    m_member = true;
    m_visitor = false;
    m_constituent = false;
    m_inactive = false;
    m_status = 1;
}

void CMbrDlg::OnInactiveFlag() 
{
    m_member = false;
    m_visitor = false;
    m_constituent = false;
    m_inactive = true;
    m_status = 8;
}

void CMbrDlg::OnVisitorFlag() 
{
    m_member = false;
    m_visitor = true;
    m_constituent = false;
    m_inactive = false;
    m_status = 2;
}

void CMbrDlg::OnConstituentFlag() 
{
    m_member = false;
    m_visitor = false;
    m_constituent = true;
    m_inactive = false;
    m_status = 4;
}


void CMbrDlg::OnEnChangeEditPhone()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMbrDlg::OnBnClickedCasesenfind()
{
	if (s_case) s_case = false;
	else s_case = true;
}
