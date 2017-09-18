// OutReachView.h : interface of the COutReachView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTREACHVIEW_H__859C16CD_6D0C_11D2_8045_44455354616F__INCLUDED_)
#define AFX_OUTREACHVIEW_H__859C16CD_6D0C_11D2_8045_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Report.h"
#include <afxdtctl.h>

class COutReachView : public CFormView
{
protected: // create from serialization only
	COutReachView();
	DECLARE_DYNCREATE(COutReachView)

public:
	//{{AFX_DATA(COutReachView)
	enum { IDD = IDD_OUTREACH_FORM };
	CEdit	m_status_ctrl;
	CEdit	m_attend_ctrl;
	CEdit	m_notes_ctrl;
	CEdit	m_phone_ctrl;
	CEdit	m_email_ctrl;
	CEdit	m_zip_ctrl;
	CEdit	m_city_ctrl;
	CEdit	m_state_ctrl;
	CEdit	m_address_ctrl;
	CEdit	m_name_ctrl;
	CDateTimeCtrl	m_service_date_ctrl;
	CStatic	m_humc_bitmap;
	CListBox	m_mlist;
	CString	m_name;
	CString	m_phone;
	CString	m_email;
	CString	m_zip;
	CString	m_address;
	CString	m_state;
	CString	m_city;
	UINT	m_member_total;
	UINT	m_total_records;
	UINT	m_vistor_total;
	CString	m_w_attendance;
	CString	m_current_service;
	UINT	m_1service;
	UINT	m_2service;
	CString	m_status;
	UINT	m_record;
	float	m_Attend_Per;
	CTime	m_CalSelDate;
	CString	m_note;
	//}}AFX_DATA

// Attributes
public:
	COutReachDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutReachView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
    CReport rpt;

    virtual ~COutReachView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    void DisplayCurrentPerson();

protected:
  	enum { REC_PER_PAGE = 50 };

    void format_report( int sel );
    LPDEVMODE COutReachView::ChangeDevMode(HWND hWnd, char *pDevice);
    LPVOID COutReachView::MyAllocMem(DWORD cb);
    void COutReachView::SetLandscape();

	LPDEVMODE lpDevMode;
    CFont *pSysFont;

// Generated message map functions
protected:
	//{{AFX_MSG(COutReachView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelcancelList1();
	afx_msg void OnSelchangeList1();
	afx_msg void OnSetfocusList1();
	afx_msg void OnChangeNotes();
	afx_msg void OnUpdateRec();
	afx_msg void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddSelAttendance();
	afx_msg void OnDelSelAttendance();
	afx_msg void OnFindRecButton();
	afx_msg void OnDeleteRecButton();
	afx_msg void OnNewRecButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEmail();
	afx_msg void OnEnChangePhone();
	afx_msg void OnEnChangeName();
	afx_msg void OnEnChangeAddress();
	afx_msg void OnEnChangeState();
};

#ifndef _DEBUG  // debug version in OutReachView.cpp
inline COutReachDoc* COutReachView::GetDocument()
   { return (COutReachDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTREACHVIEW_H__859C16CD_6D0C_11D2_8045_44455354616F__INCLUDED_)
