#if !defined(AFX_MBRDLG_H__859C16F1_6D0C_11D2_8045_44455354616F__INCLUDED_)
#define AFX_MBRDLG_H__859C16F1_6D0C_11D2_8045_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MbrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMbrDlg dialog

class CMbrDlg : public CDialog
{
// Construction
public:
	CMbrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMbrDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_name;
	CString	m_city;
	CString	m_address;
	CString	m_phone;
	CString	m_email;
	CString	m_zip;
	CString	m_state;
	//}}AFX_DATA

    bool m_visitor;
    bool m_constituent;
    bool m_inactive;
    int  m_status;
    bool m_member;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMbrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMbrDlg)
	afx_msg void OnMemberFlag();
	afx_msg void OnInactiveFlag();
	afx_msg void OnVisitorFlag();
	afx_msg void OnConstituentFlag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditPhone();
	afx_msg void OnBnClickedCasesenfind();
	bool s_case;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBRDLG_H__859C16F1_6D0C_11D2_8045_44455354616F__INCLUDED_)
