// OutReachDoc.h : interface of the COutReachDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTREACHDOC_H__859C16CB_6D0C_11D2_8045_44455354616F__INCLUDED_)
#define AFX_OUTREACHDOC_H__859C16CB_6D0C_11D2_8045_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PrsnRcd.h"
#include "Report.h"

class COutReachDoc : public CDocument
{
protected: // create from serialization only
	COutReachDoc();
	DECLARE_DYNCREATE(COutReachDoc)

// Attributes
protected:
    CObArray PersonArray;
    UINT current_selection;
    void FindName( CString n, bool cs);
    void FindAddress( CString a);
    void FindPhone( CString p);
	void FindEmail(CString email);
	CTime today, last_worship, first_worship;
    CTime YearOfSundays[53];
    CString LastSundayStr;
    CString MonthsList[13];
    CString MonthsStr;
    bool database_active;


public:

// Operations
public:
    void AddPrsn( CString n, CString a, CString c, CString s, 
                  CString z, CString p, CString e, int m, CString atd, CString pnote);
    int         NumPrsn();
    void        GetPrsn( int x, CPrsnRcd &p );
    CPrsnRcd*   GetPrsn( int x );
    void        GetRptSel( int sel, CReport *rpt );
    void        SetWorshipDate(CTime date);
    void        SortPersons();
    void        UpdateDocViews();

    void        DeleteContents();

    void    SetSelection( int sel ) { current_selection = sel; }
    UINT    GetSelection( )         { return current_selection; }
    CString GetLastWorship( )    { return LastSundayStr; }
    CTime   GetLastWorshipDate( ){ return last_worship; }
    CString GetMonthStr( )       { return MonthsStr; }
    void    DoFindPerson( )      { OnEditFind();}
    void    DoDelPerson( )       { OnEditDelete();}
    void    DoAddPerson( )       { OnEditAdd();}

    
    CPrsnRcd ParseHistory( CString rec );
    enum { nLinesPerPage = 50 };

    // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutReachDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutReachDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutReachDoc)
	afx_msg void OnEditAdd();
	afx_msg void OnEditDelete();
	afx_msg void OnMaintHistory();
   afx_msg void OnMaintExportDos();
	afx_msg void OnEditFind();
	afx_msg void OnEditModify();
	afx_msg void OnMaintanceMerge();
	afx_msg void OnMaintanceExporttext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTREACHDOC_H__859C16CB_6D0C_11D2_8045_44455354616F__INCLUDED_)
