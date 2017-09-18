// PrsnRcd.cpp: implementation of the CPrsnRcd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutReach.h"
#include "PrsnRcd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int TFIELD = 7;
const static int fldlngth[  TFIELD ] =   {     20, 28, 16,  6,  9,  1,  52 }; 
const static int fldstart[  TFIELD+1 ] = {  0, 20, 48, 64, 70, 79, 80, 132 };

static  CTimeSpan prsn_week( 7, 0, 0, 0);
static  CTimeSpan prsn_year( 365, 0, 0, 0);
static	CTime     today = CTime::GetCurrentTime();
static	CTime     ayear_ago = today - prsn_year;
static  CTime     reset_time( 2020, 1, 1, 12, 0, 0, -1 );
static  CTime     start_time( 2000, 1, 1, 1, 0, 0, -1 );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrsnRcd::CPrsnRcd()
{
   name               = "unknown";
   address            = " ";
   city               = " ";
   state              = " ";
   zip                = " ";
   phone              = " ";
   email			  = " ";
   mbr                = 2;
   attend_str         = "";
   attend_percent     = 0.0;
   total_visits       = 0;
   first_service_cnt  = 0;
   second_service_cnt = 0;
   third_service_cnt  = 0;
   sat_service_cnt    = 0;
   possible_visit_cnt = 1;
   last_visit         = CTime(0);
   first_visit        = CTime(0);
   first_attendance   = first_visit;
   note               = "";
   breakit_cnt        = 0;    
}

//////////////////////////////////////////////////////////////////////
CPrsnRcd::CPrsnRcd( CPrsnRcd& p)
{

   name               = p.name;
   address            = p.address;
   city               = p.city;
   state              = p.state;
   zip                = p.zip;
   phone              = p.phone;
   email			  = p.email;
   mbr                = p.mbr;
   attend_str         = p.attend_str;
   attend_percent     = p.attend_percent;
   total_visits       = p.total_visits;
   first_service_cnt  = p.first_service_cnt;
   second_service_cnt = p.second_service_cnt;
   third_service_cnt  = p.third_service_cnt;
   sat_service_cnt    = p.sat_service_cnt;
   possible_visit_cnt = p.possible_visit_cnt;
   last_visit         = p.last_visit;
   first_visit        = p.first_visit;
   first_attendance   = p.first_attendance;
   note               = p.note;
   breakit_cnt        = p.breakit_cnt;    
}

//////////////////////////////////////////////////////////////////////
CPrsnRcd::CPrsnRcd( CString old_rcd )
{
   cnv_str( old_rcd );
}

//////////////////////////////////////////////////////////////////////
CPrsnRcd &CPrsnRcd::operator=( CString& old_rcd )
{
   cnv_str( old_rcd );
   return *this;    
}

//////////////////////////////////////////////////////////////////////
bool CPrsnRcd::operator<( CPrsnRcd& p )
{
   return p.name < name;    
}

//////////////////////////////////////////////////////////////////////
bool CPrsnRcd::operator>( CPrsnRcd& p )
{
   return p.name > name;    
}

//////////////////////////////////////////////////////////////////////
bool CPrsnRcd::operator==( CPrsnRcd& p )
{

   return p.name == name;

}

//////////////////////////////////////////////////////////////////////
CPrsnRcd &CPrsnRcd::operator=( CPrsnRcd& p )
{
   if( &p != this)
   {
      name               = p.name;
      address            = p.address;
      city               = p.city;
      state              = p.state;
      zip                = p.zip;
      phone              = p.phone;
	  email				 = p.email;
      mbr                = p.mbr;
      attend_str         = p.attend_str;
      attend_percent     = p.attend_percent;
      total_visits       = p.total_visits;
      first_service_cnt  = p.first_service_cnt;
      second_service_cnt = p.second_service_cnt;
      third_service_cnt  = p.third_service_cnt;
      sat_service_cnt    = p.sat_service_cnt;
      possible_visit_cnt = p.possible_visit_cnt;
      last_visit         = p.last_visit;
      first_visit        = p.first_visit;
      first_attendance   = p.first_attendance;
      note               = p.note;
      attend_percent     = 100.0;
      breakit_cnt        = p.breakit_cnt;    

      SetMemberStr(mbr);
   }
   else 
   {
      TRACE( "Self assignment on person class\n" );
   }


   return *this;
}

//////////////////////////////////////////////////////////////////////
CPrsnRcd::CPrsnRcd( CString n, CString a, CString c, CString s, 
                   CString z, CString p, CString e, int m,     CString atd, CString pnote)
{
   name             = n;
   address          = a;
   city             = c;
   state            = s;
   zip              = z;
   phone            = p;
   email			= e;
   mbr              = m;
   attend_str       = atd;
   note             = pnote;
   attend_percent     = 0.0;
   total_visits       = 0;
   first_service_cnt  = 0;
   second_service_cnt = 0;
   third_service_cnt  = 0;
   sat_service_cnt    = 0;
   possible_visit_cnt = 1;
   last_visit         = CTime(0);
   first_visit        = CTime(0);
   first_attendance   = first_visit;

   SetMemberStr(m);


}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::Serialize( CArchive &archive)
{
   unsigned int cnt;

   CObject::Serialize(archive);

   if( archive.IsStoring() )
   {

      UpdateAttedance();
      archive << name << address << city << state << zip  << phone << email << mbr;
      archive << attend_str << attend_percent << total_visits << joined << first_attendance;
      archive << first_service_cnt << second_service_cnt << third_service_cnt << sat_service_cnt;
      archive << possible_visit_cnt << person_status << last_visit << first_visit << note;

      for ( cnt = 0; cnt < 52; cnt++ )
      {
         archive << service_dates[cnt] << sschool_dates[cnt];
      }

      for ( cnt = 0; cnt < 10; cnt++ )
      {
         archive << committees[cnt];
      }

   }
   else
   {
	   if (OldFileUpdate == TRUE)
	   {
		   archive >> name >> address >> city >> state >> zip >> phone >> mbr;
	   }
	   else
	   {
		   archive >> name >> address >> city >> state >> zip >> phone >> email >> mbr;
	   }
	  archive >> attend_str >> attend_percent >> total_visits >> joined >> first_attendance;
      archive >> first_service_cnt >> second_service_cnt >> third_service_cnt >> sat_service_cnt;
      archive >> possible_visit_cnt >> person_status >> last_visit >> first_visit >> note;

      for ( cnt = 0; cnt < 52; cnt++ )
      {
         archive >> service_dates[cnt] >> sschool_dates[cnt];
      }

      for ( cnt = 0; cnt < 10; cnt++ )
      {
         archive >> committees[cnt];
      }
      UpdateAttedance();


   }
}

///////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetPrsn( CPrsnRcd& p) const
{

   p.name               = name;
   p.address            = address;
   p.city               = city;
   p.state              = state;
   p.zip                = zip;
   p.phone              = phone;
   p.email				= email;
   p.mbr                = mbr;
   p.attend_str         = attend_str;
   p.attend_percent     = attend_percent;
   p.total_visits       = total_visits;
   p.first_service_cnt  = first_service_cnt;
   p.second_service_cnt = second_service_cnt;
   p.third_service_cnt  = third_service_cnt;
   p.sat_service_cnt    = sat_service_cnt;
   p.last_visit         = last_visit;
   p.first_visit        = first_visit;
   p.first_attendance   = first_attendance;
   p.note               = note;

}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetName( CString &n ) const
{
   n = name;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetNote( CString &pnote ) const
{
   pnote = note;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetAddress( CString &a) const
{
   a = address;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetCity( CString &c ) const
{
   c = city;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetState( CString &s ) const
{
   s = state;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetZip( CString &z ) const
{
   z = zip;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetPhone( CString &p ) const
{
   p = phone;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetEmail(CString &e) const
{
	e = email;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetAttendance( CString &atd ) const
{
   atd = attend_str;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetMember( int &m ) const
{
   m = mbr;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetMemberStr( CString &m ) const
{
   if (mbr == 1)      m = 'm';
   else if (mbr == 4) m = 'c';
   else if (mbr == 8) m = 'i';
   else               m = 'v';
}

////////////////////////// Jess ///////////////////////////////////////////
void CPrsnRcd::GetNoteStr( CString &n ) const
{
   n = note;
}
//////////////////////////////////////////////////////////////////////
void CPrsnRcd::GetAttendDateStr( CString &d ) const
{
   int cnt;
   CString tempStr, FStr;


   if( total_visits >= attend_str_size-2 ) 
      cnt = attend_str_size-2;
   else
      cnt = total_visits-1;

   while (cnt >= 0) 
   {
      tempStr = service_dates[cnt].Format("%b %d, %Y ;");
      FStr = FStr + tempStr;
      cnt--;
   }
   d = FStr;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::SetMemberStr( int mbr )
{
   if (mbr == 1)      person_status = 'm';
   else if (mbr == 4) person_status = 'c';
   else if (mbr == 8) person_status = 'i';
   else               person_status = 'v';
}
//////////////////////////////////////////////////////////////////////
int CPrsnRcd::GetMember( void )
{
   return mbr;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::AddToAttedance( CTime &date )
{
   CTimeSpan five_years( 365*5, 0, 0, 0);

   // make sure date is ok
   if( date > today || date < (today - five_years) ) return;

   // make sure the attendance is not already present
   if( Visited(date) ) return;

   if( total_visits < attend_str_size )
      service_dates[total_visits] = date;
   else
      service_dates[0] = date;

   total_visits++;
   SetLastVisit( date );
   SortAttendance();
   attend_str = GetAttedanceStr(date);
   UpdateAttedance();
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::DeleteAttedance( CTime &date )
{
   int cnt, index;

   // make sure the attendance is not already present
   if( !Visited(date) ) return;

   index = total_visits;
   if( total_visits >= attend_str_size )
   {
      index = attend_str_size-1;
   }

   for( cnt = 1; cnt < index; cnt++ )
   {
      if( SameDate(service_dates[cnt], date) )
      {
         service_dates[cnt] = reset_time;
         SortAttendance();
         total_visits--;
         service_dates[index-1] = 0;
         attend_str = GetAttedanceStr(date);
         UpdateAttedance();
         break;
      }
   }
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::SetAttedance( CTime &date )
{
   CTime     start_week, cur_week;
   int       total_weeks = attend_str.GetLength();
   CTimeSpan attend_length( 7*(possible_visit_cnt-1), 0, 0, 0);
   int pos, cnt, next;

   next = 0;
   start_week = date - attend_length;
   if ( date <= CTime::GetCurrentTime() )  // validate date
   {
      cur_week = start_week;
      SetFirstVisit( (start_week - prsn_year) - prsn_week );
      for( cnt = 0; cnt < possible_visit_cnt; cnt++ )
      {
         pos = possible_visit_cnt - cnt;
         if(attend_str[ cnt ] != '-' && attend_str[ cnt ] != ' ' )
         {
            service_dates[next++] = cur_week;
            SetLastVisit( cur_week );
         }
         if(attend_str[ cnt ] == 'f')
         {
            SetFirstVisit( cur_week );
         }
         cur_week = cur_week + prsn_week;
      }
   }
   // verify data totals
   ASSERT( total_visits == next );
}

//////////////////////////////////////////////////////////////////////
CString CPrsnRcd::GetAttedanceStr( CTime &date )
{
   CTime cur_week;
   CTimeSpan offset(1, 0, 0, 0); // 3 days
   int cnt, next;
   CString rtn_strn;
   char chAttend;
   char strAttend[attend_str_size];

   cur_week = date;

   if( total_visits > attend_str_size ) 
      next = attend_str_size-1;
   else
      next = total_visits-1;

   if( next > 0)
      while(service_dates[next] <= 0 || service_dates[next] > (cur_week+offset)) next--;     
   else
      next = 0;

   for( cnt = attend_str_size; cnt > 0; cnt-- )
   {
      chAttend = ' ';
      if( SameWeek(first_visit, cur_week ) )
      {
         chAttend = 'f';
      }
      else if( SameWeek(service_dates[next],cur_week) )
      {
         chAttend = 'x';
         next--;
      }
      else if ( first_visit < cur_week )
      {
         chAttend = '-';
      }
      strAttend[cnt-1] = chAttend;
      cur_week = cur_week - prsn_week;
   }

   rtn_strn.Format( "%52.52s", &strAttend[1] );
   rtn_strn.TrimLeft();
   rtn_strn.TrimRight();
   return rtn_strn;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::UpdateAttedanceStr( CTime &date )
{

   attend_str = GetAttedanceStr(date);
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::CleanAttedance( void )
{
   int cnt, len;
   bool first_found = false;

   if( total_visits == 0)
   {
      total_visits = 1;
      service_dates[0] = first_visit;
      return;
   }

   len = total_visits;

   if( len > attend_str_size-1 )
   {
      len = attend_str_size-1;
   }

   for( cnt = 0; cnt < len; cnt++)
   {
      // look for invalid visit
      if(service_dates[cnt] > today)
      {
         service_dates[cnt] =  first_visit;
      }
      // look for missing first visit
      if( service_dates[cnt] == first_visit ) first_found = true;
   }

   if( (first_found == false) && (len < attend_str_size-2) )
   {
      service_dates[len] = first_visit;
      total_visits++;
   }

   DelCopyAttendance();
   SortAttendance();
}    
//////////////////////////////////////////////////////////////////////
int CPrsnRcd::GetVisitCnt( void )
{ 
   int num = 0;

   if( total_visits < attend_str_size-1)
   {
      num = GuessAttendance();		
      if(total_visits != num)
      {
         //		    CleanAttedance();
         total_visits = GuessAttendance();
      }
   }

   return total_visits; 
} 

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::UpdateAttedance( void )
{

   int attend_len, week_size, year_visit_cnt, index;
   CTimeSpan attendlength = today - first_visit;

   void* attnd = &attendlength;
   void* wk = &prsn_week;

   attend_len = *(int*)(attnd);
   week_size  = *(int*)(wk);

   possible_visit_cnt = attend_len / week_size;
   if(possible_visit_cnt > attend_str_size-1) possible_visit_cnt = attend_str_size-1;

   index = total_visits;
   if( total_visits >= attend_str_size )
   {
      index = attend_str_size-1;
   }

   //	CleanAttedance();
   int cnt;
   for( cnt = index, year_visit_cnt=0; cnt >= 0; cnt--)
   {
      if (service_dates[cnt] >= ayear_ago) year_visit_cnt++;
   }

   if( possible_visit_cnt )
   {
      attend_percent = float(year_visit_cnt) / float(possible_visit_cnt);
   }
   else 
   {
      attend_percent = 0.0;
   }

}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::SetAttedance( CString &a )
{
   int cnt;
   int missed, any_service, started;
   CTimeSpan weeks( 0, 0, 0, 0);

   a.TrimLeft();
   a.TrimRight();
   int total_weeks = a.GetLength();

   CTimeSpan start_week_offset( 7*total_weeks, 0, 0, 0);
   first_visit = CTime::GetCurrentTime() - start_week_offset;

   attend_str = a;
   missed = 0;
   total_visits = 0;
   any_service = 0;
   started = 0;
   first_service_cnt = 0;
   second_service_cnt = 0;
   third_service_cnt = 0;
   sat_service_cnt = 0;


   possible_visit_cnt = total_weeks;
   for( cnt = 0; cnt < total_weeks; cnt++ )
   {
      switch( a[cnt] )
      {

      case '-': 
         missed++;
         break;

      case 'f': 
         started++;
         service_dates[0] = first_visit;
         total_visits++;
         break;

      case 'x':
         any_service++;
         service_dates[total_visits % attend_str_size] = first_visit + weeks;
         total_visits++;
         break;

      case '1':
         first_service_cnt++;
         service_dates[total_visits % attend_str_size] = first_visit + weeks;
         total_visits++;
         break;

      case '2':
         second_service_cnt++;
         service_dates[total_visits % attend_str_size] = first_visit + weeks;
         total_visits++;
         break;

      case '3':
         third_service_cnt++;
         service_dates[total_visits % attend_str_size] = first_visit + weeks;
         total_visits++;
         break;

      case 's':
         sat_service_cnt++;
         service_dates[total_visits % attend_str_size] = first_visit + weeks;
         total_visits++;
         break;

      default:
         possible_visit_cnt--;
      }

      weeks += prsn_week;

   }

   int check_total = started + any_service + first_service_cnt + second_service_cnt + third_service_cnt + sat_service_cnt;
   SortAttendance();
   ASSERT( total_visits == check_total );

   if (possible_visit_cnt == 0 ) possible_visit_cnt = 1;
   attend_percent = float(total_visits) / float(possible_visit_cnt);
}

//////////////////////////////////////////////////////////////////////
const int CPrsnRcd::GetFieldStart( int field )
{ 
   ASSERT ( field <= TFIELD );
   return fldstart[ field ]; 

}

//////////////////////////////////////////////////////////////////////
const int CPrsnRcd::GetFieldLen( int field )
{ 

   ASSERT ( field < TFIELD );
   return fldlngth[ field ];

}

//////////////////////////////////////////////////////////////////////
CPrsnRcd::~CPrsnRcd()
{

}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::cnv_str( CString in_rec )
{

   bool rtn_state = false;
   bool sep_found = false;
   int reclen;
   int cnt, fldcnt, fldpos;
   int last_char[ CPrsnRcd::TFIELDS ];

   reclen = in_rec.GetLength();
   cnt = 0;

   for( fldcnt = 0; fldcnt < CPrsnRcd::TFIELDS; fldcnt++ )
   {
      last_char[fldcnt] = cnt; // initialize position to start
      for( fldpos = 0; fldpos < GetFieldLen( fldcnt ); fldpos++ )
      {
         if ( in_rec[cnt] != 0x20 ) 
         {
            last_char[fldcnt] = cnt;
         }
         cnt++;
      }
   }

   for(cnt=0; cnt <= ( last_char[0] - GetFieldStart(0) ); cnt++ )
      name += in_rec[ GetFieldStart(0) + cnt ];

   for(cnt=0; cnt <= ( last_char[1] - GetFieldStart(1) ); cnt++ )
      address += in_rec[ GetFieldStart(1) + cnt];

   for(cnt=0; cnt <= ( last_char[2] - GetFieldStart(2) ); cnt++ )
   {
      if( in_rec[GetFieldStart(2) + cnt] == ',' )
      {
         sep_found = true;
      }
      else
      {
         if( sep_found == false )
            city += in_rec[GetFieldStart(2) + cnt];
         else
            state += in_rec[GetFieldStart(2) + cnt];
      }
   }
   state.TrimLeft();
   sep_found = false;

   for(cnt=0; cnt <= ( last_char[3] - GetFieldStart(3) ); cnt++ )
      zip  += in_rec[ GetFieldStart(3) + cnt];

   for(cnt=0; cnt <= ( last_char[4] - GetFieldStart(4) ); cnt++ )
      phone += in_rec[ GetFieldStart(4) + cnt];

   for(cnt=0; cnt <= ( last_char[6] - GetFieldStart(6) ); cnt++ )
   {
      if( in_rec[ GetFieldStart(6) + cnt ] != ' ' )
      {
         attend_str += in_rec[ GetFieldStart(6) + cnt ];
      }
   }

   if (in_rec.GetAt( GetFieldStart(5) ) == 'm')
      mbr = 1;
   else if (in_rec.GetAt( GetFieldStart(5) ) == 'c')
      mbr = 4;
   else if (in_rec.GetAt( GetFieldStart(5) ) == 'i')
      mbr = 8;
   else
      mbr = 2;

   SetAttedance( attend_str );

}

/////////////////////////////////////////////////////////////////////////////
void CPrsnRcd::SortAttendance()
{
   CTime temp;
   int p,j, max_visits;

   if( total_visits > attend_str_size-1 )
      max_visits = attend_str_size-1;
   else
      max_visits = total_visits;

   for( p = 1; p < max_visits; p++ )
   {
      temp = service_dates[p];

      for( j = p; j > 0 && temp < service_dates[j-1]; j--)
      {
         service_dates[j] = service_dates[j-1];
      }
      service_dates[j] = temp;
   }

}

/////////////////////////////////////////////////////////////////////////////
void CPrsnRcd::DelCopyAttendance()
{
   CTime temp;
   int p,j, max_visits;

   if( total_visits > attend_str_size-1 )
      max_visits = attend_str_size-1;
   else
      max_visits = total_visits;

   for( p = 0; p < max_visits; p++ )
   {
      if( service_dates[p] == service_dates[p+1] )
      {
         for( j = p+1; j < max_visits-1; j++ )
         {
            service_dates[j] = service_dates[j+1];
         }
         max_visits--;
      }

   }
   if( total_visits != max_visits )
   {
      breakit();
      if(total_visits < attend_str_size-1) 
      {
         total_visits = max_visits;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
int CPrsnRcd::GuessAttendance()
{

   int visit_cnt = 0, max_visits, p;

   if( total_visits > attend_str_size-1 )
      max_visits = attend_str_size-1;
   else
      max_visits = total_visits;

   for( p = 0; p < max_visits; p++ )
   {
      if(( service_dates[p] <= today) || (service_dates[p] > start_time))
      {
         visit_cnt++;
      }
   }
   return visit_cnt;
}

/////////////////////////////////////////////////////////////////////////////
bool CPrsnRcd::Visited( CTime &date )
{
   int cnt,index;
   bool rtn = false;
   CTimeSpan one_day( 1, 0, 0, 0);

   index = total_visits;
   if( total_visits >= attend_str_size )
   {
      index = attend_str_size-1;
   }

   if( date.GetTime() > 0 )
   {
      for( cnt = 1; cnt < index; cnt++ )
      {
         if( SameWeek(service_dates[cnt], date) )
         {
            rtn = true;
         }
      }
   }
   return rtn;
}
//////////////////////////////////////////////////////////////////////
bool CPrsnRcd::SameDate( CTime &date1, CTime &date2 )
{
   bool rtn = false;
   int day1,day2;
   int mon1, mon2;
   int yr1, yr2;

   if( date1.GetTime() > 0 && date2.GetTime() > 0 )
   {
      day1 = date1.GetDay();
      day2 = date2.GetDay();
      mon1 = date1.GetMonth();
      mon2 = date2.GetMonth();
      yr1 = date1.GetYear();
      yr2 = date2.GetYear();

      if( day1 == day2 && mon1 == mon2 && yr1  == yr2 )
      {
         rtn = true;
      }
   }

   return rtn;

}
//////////////////////////////////////////////////////////////////////
bool CPrsnRcd::SameWeek( CTime &date1, CTime &date2 )
{
   bool rtn = false;

   CString test1 = date1.Format("%Y,%U");
   CString test2 = date2.Format("%Y,%U");

   if( test1 == test2)
      rtn = true;

   return rtn;

}
//////////////////////////////////////////////////////////////////////
CString CPrsnRcd::GetPersonStr( CTime &date )
{

   CString rtn_strn;
   CString name, addr, phone, atten, status;
   CString city, state, zip, temp_str2;
   CString note, attendNum;
   CString temp_str;

   GetName(temp_str);
   name.Format( "%-20.19s;",temp_str);

   GetAddress(temp_str);
   addr.Format( "%-28.28s;",temp_str);

   GetPhone(temp_str);
   phone.Format( "%9.8s;",temp_str);

   GetMemberStr(temp_str);
   status.Format( "%2.1s;",temp_str);

   GetZip(temp_str);
   zip.Format( "%-5.5s;",temp_str);

   GetCity(temp_str);

   GetState(temp_str2);
   if(temp_str2.GetLength() > 1 )
      temp_str = temp_str + ", " + temp_str2;

   city.Format( "%-16.16s;",temp_str);

   temp_str = GetAttedanceStr( date );
   atten.Format( "%52.52s;",temp_str);

   GetNoteStr(temp_str);
   note.Format( "%30.30s;",temp_str);


   rtn_strn = name+addr+city+zip+phone+status+atten+note+"\n";

   return rtn_strn;
}

//////////////////////////////////////////////////////////////////////
CString CPrsnRcd::GetPersonExportStr( CTime &date, char seperator )
{
   CString rtn_strn;
   CString name, addr, phone, status;
   CString city, state, zip, temp_str;
   CString atten, note, attendNum;

   GetName(temp_str);
   name.Format( "%s%c",temp_str,seperator);

   GetAddress(temp_str);
   addr.Format( "%s%c",temp_str,seperator);

   GetPhone(temp_str);
   phone.Format( "%s%c",temp_str,seperator);

   GetCity(temp_str);
   city.Format( "%s%c",temp_str,seperator);

   GetState(temp_str);
   state.Format( "%s%c",temp_str,seperator);

   GetZip(temp_str);
   zip.Format( "%s%c",temp_str,seperator);

   GetMemberStr(temp_str);
   status.Format( "%s%c",temp_str,seperator);

   temp_str = GetAttedanceStr( date );
   atten.Format( "%s%c",temp_str,seperator);

   GetAttendDateStr(temp_str);
   attendNum.Format( "%s%c",temp_str,seperator);

   GetNoteStr(temp_str);
   note.Format( "%s%c",temp_str,seperator);

   rtn_strn = name+addr+city+state+zip+phone+status+atten+note+attendNum+"\n";

   return rtn_strn;
}

//////////////////////////////////////////////////////////////////////
CString CPrsnRcd::GetAttendDateStr( )
{

   CString rtn_strn = " ";
   int p, max_visits;

   if( total_visits > attend_str_size-1 )
      max_visits = attend_str_size-1;
   else
      max_visits = total_visits;

   for( p = 0; p < max_visits; p++ )
   {
      rtn_strn += service_dates[p].Format("%A, %B %d, %Y || ");
   }

   return rtn_strn;
}

//////////////////////////////////////////////////////////////////////
void CPrsnRcd::breakit( void )
{
   breakit_cnt++;
}

//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPrsnRcd, CObject, OUTREACH_VERSION)