// OutReach.h : main header file for the OUTREACH application
//

#if !defined(AFX_OUTREACH_H__859C16C5_6D0C_11D2_8045_44455354616F__INCLUDED_)
#define AFX_OUTREACH_H__859C16C5_6D0C_11D2_8045_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COutReachApp:
// See OutReach.cpp for the implementation of this class
//
const UINT OUTREACH_VERSION = 0;
extern BOOLEAN OldFileUpdate;

class COutReachApp : public CWinApp
{
public:
   UINT SetLandscape();

	COutReachApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutReachApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COutReachApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTREACH_H__859C16C5_6D0C_11D2_8045_44455354616F__INCLUDED_)
