// Report.cpp: implementation of the CReport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutReach.h"
#include "Report.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReport::CReport()
{
    title = "Mill Plain Attendance Report";
    header = " ";
    footer = " Page -";
    current_rcd = 0;
    total_rcd = 0;
    Summary[0].Format("Total Present       = ");
    Summary[1].Format("  Members Present   = ");
    Summary[2].Format("  Visitors Present  = ");
    Summary[3].Format("Total Records       = ");
    Summary[4].Format("  Total Members     = ");
    Summary[5].Format("  Total Visitors    = ");

}

CReport::~CReport()
{
    prsns.RemoveAll();
}


CReport::CReport( const CReport &rpt )
{
    
    title = rpt.title;
    header = rpt.header;
    footer = rpt.footer;
    current_rcd = rpt.current_rcd;
    total_rcd = rpt.total_rcd;
    
    int rcd;
    for ( rcd = 0; rcd < rpt.prsns.GetSize(); rcd++)
    {
        prsns[rcd] = rpt.prsns[rcd];
    }
}

CReport &CReport::operator=( const CReport &rpt )
{
    title = rpt.title;
    header = rpt.header;
    footer = rpt.footer;
    current_rcd = rpt.current_rcd;
    total_rcd = rpt.total_rcd;
    
    int rcd;
    for ( rcd = 0; rcd < rpt.prsns.GetSize(); rcd++)
    {
        prsns[rcd] = rpt.prsns[rcd];
    }
    
    return *this;
}

//////////////////////////////////////////////////////////////////////
// Public member functions
void CReport::AddPerson( CPrsnRcd* prsn )
{
    prsns.Add( prsn );
    total_rcd++;
}

//////////////////////////////////////////////////////////////////////
void CReport::Clear( )
{
    prsns.RemoveAll();
    title = "Mill Plain Attendance Report";
    header = " ";
    footer = " Page -";
    current_rcd = 0;
    total_rcd = 0;
    Summary[0].Format("Total Present       = ");
    Summary[1].Format("  Members Present   = ");
    Summary[2].Format("  Visitors Present  = ");
    Summary[3].Format("Total Records       = ");
    Summary[4].Format("  Total Members     = ");
    Summary[5].Format("  Total Visitors    = ");
}
//////////////////////////////////////////////////////////////////////
void CReport::SetSummary( rpt_summary_data_t s )
{
    Summary[0].Format("Total Present       = %d",s.total_attendance);
    Summary[1].Format("  Members Present   = %d",s.member_cnt);
    Summary[2].Format("  Visitors Present  = %d",s.visitor_cnt);
    Summary[3].Format("Total Records       = %d",s.total_rec_cnt);
    Summary[4].Format("  Total Members     = %d",s.total_member_cnt);
    Summary[5].Format("  Total Visitors    = %d",s.total_visitor_cnt);
}
//////////////////////////////////////////////////////////////////////
CPrsnRcd* CReport::GetNextPerson( )
{
    
    if( total_rcd > 0 )
    {
        return( (CPrsnRcd*)prsns.GetAt( current_rcd++ ) );
    }
    else
    {
        return ((CPrsnRcd*)NULL);
    }
    
}
//////////////////////////////////////////////////////////////////////
CPrsnRcd* CReport::GetCurrentPerson( )
{
    
    if( total_rcd > 0 )
    {
        return( (CPrsnRcd*)prsns.GetAt( current_rcd ) );
    }
    else
    {
        return ((CPrsnRcd*)NULL);
    }
    
}
//////////////////////////////////////////////////////////////////////
CString  CReport::GetRcdString( CTime &date )
{
    CString name, addr, phone, email, atten, status;
    CString city, state, zip, note, temp_str;
    
    GetCurrentPerson()->GetName(temp_str);
    name.Format( "%-19.18s",temp_str);

    GetCurrentPerson()->GetAddress(temp_str);
    addr.Format( "%-26.25s",temp_str);

    GetCurrentPerson()->GetPhone(temp_str);
    phone.Format( "%13.12s",temp_str);

	GetCurrentPerson()->GetEmail(temp_str);
	email.Format("  %-26.25s", temp_str);

	GetCurrentPerson()->GetMemberStr(temp_str);
    status.Format( "%2.1s",temp_str);
    
    GetCurrentPerson()->GetCity(temp_str);
    city.Format( "%14.13s",temp_str);

    GetCurrentPerson()->GetState(temp_str);
    state.Format( "%3.2s",temp_str);

    temp_str = GetCurrentPerson()->GetAttedanceStr( date );
    atten.Format( "%17.16s",temp_str.Right(16));

    GetCurrentPerson()->GetZip(temp_str);
    zip.Format( "%6.5s",temp_str);

	GetCurrentPerson()->GetNote(temp_str);
	note.Format("%20.19s", temp_str);

	temp_str = name + addr + city + state + zip + phone + status + atten + email + note;

    return temp_str;
}
//////////////////////////////////////////////////////////////////////
CString CReport::GetMonthString( CTime cdate )
{

   CString rtn_strn;
   int month, cnt;
   static char *month_strs[] ={"Jan " ,"Feb  ",
                               "Mar  ","Apr ",
                               "May " ,"Jun  ",
                               "Jul " ,"Aug ",
                               "Sep  ","Oct ",
                               "Nov  ","Dec  "};

   month = cdate.GetMonth();

   for( cnt = 0; cnt < 4; cnt++ )
   {
      if( month > 11 ) month = 0;
      rtn_strn = rtn_strn + month_strs[ month++];
   }


   return rtn_strn;
}
