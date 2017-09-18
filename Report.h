// Report.h: interface for the CReport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORT_H__EBF1CAC2_3456_11D3_BC71_A096F26BE03D__INCLUDED_)
#define AFX_REPORT_H__EBF1CAC2_3456_11D3_BC71_A096F26BE03D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PrsnRcd.h"

typedef struct
{
    int                 total_rec_cnt; 
    int                 total_attendance; 
    int                 total_member_cnt;
    int                 total_visitor_cnt; 
    int                 visitor_cnt; 
    int                 member_cnt; 
    int                 total_first_visit_cnt; 
} rpt_summary_data_t;

class CReport : public CObject  
{

public:
	CReport();
	virtual ~CReport();
    CReport( const CReport & );
    CReport &operator=( const CReport & );
    CString Summary[8];


    void      AddPerson( CPrsnRcd* );
    CPrsnRcd* GetNextPerson( );
    CPrsnRcd* GetCurrentPerson( );
    CString   GetRcdString( CTime &date );
    CString   GetMonthString( CTime v );
    void SetSummary( rpt_summary_data_t summary );
    void      Clear( );


    void SetTitle  ( CString t ) { title = t; }
    void SetHeader ( CString h ) { header = h; }
    void SetFooter ( CString f ) { footer = f; }
    void Add2Title ( CString t ) { title += t; }
    void Add2Header( CString h ) { header += h; }
    void Add2Footer( CString f ) { footer += f; }
    int  GetPrsnCnt( )           { return total_rcd; }
    int  GetCurrentRcd( )        { return current_rcd; }
    void SetCurrentRcd( int r )  { current_rcd = r; }
    int  GetTotalRcd( )          { return total_rcd; }
    CString GetHeader( )         { return header; }
    CString GetFooter( )         { return footer; }

protected:
    CString title,header,footer;
    CString summary[7];
    
    CObArray prsns;
    int current_rcd,total_rcd;

    
};


#endif // !defined(AFX_REPORT_H__EBF1CAC2_3456_11D3_BC71_A096F26BE03D__INCLUDED_)
