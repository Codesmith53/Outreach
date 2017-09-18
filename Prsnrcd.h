// PrsnRcd.h: interface for the CPrsnRcd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRSNRCD_H__859C16F3_6D0C_11D2_8045_44455354616F__INCLUDED_)
#define AFX_PRSNRCD_H__859C16F3_6D0C_11D2_8045_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

const int num_fields = 7;
const int attend_str_size = 53;

class CPrsnRcd : public CObject  
{
DECLARE_SERIAL( CPrsnRcd )

    protected:
        CString  name, address, city, state, zip;
        CString  phone,email;
        CString  attend_str;
        int      total_visits;
        int      first_service_cnt;
        int      second_service_cnt;
        int      third_service_cnt;
        int      sat_service_cnt;
        int      possible_visit_cnt;
        float    attend_percent;
        int      mbr;
        char     person_status;
        CTime    service_dates[attend_str_size];
        CTime    sschool_dates[attend_str_size];
        CTime    first_attendance;
        CTime    joined;
        CTime    last_visit;
        CTime    first_visit;
        CString  note;
        int      committees[10];
        void     cnv_str( CString );
        void     SortAttendance();
        void     DelCopyAttendance();
		int      breakit_cnt;
        void     breakit( void );
		int      GuessAttendance();

    public:
	    CPrsnRcd();
        CPrsnRcd( CPrsnRcd& p);
        CPrsnRcd( CString old_rcd);
        CPrsnRcd &operator=( CString& old_rcd);
        CPrsnRcd &operator=( CPrsnRcd& p);
        bool operator==( CPrsnRcd& p );
        bool operator<( CPrsnRcd& p);
        bool operator>( CPrsnRcd& p);

        CPrsnRcd( CString n, CString a, CString c, CString s, 
                  CString z, CString p, CString e, int m,
			      CString atd, CString pnote);

        void GetPrsn(    CPrsnRcd& p) const;
        void GetName(    CString &n ) const;
        void GetNote(    CString &pnote) const;
        void GetAddress( CString &a ) const;
        void GetCity(    CString &c ) const;
        void GetState(   CString &s ) const;
        void GetZip(     CString &z ) const;
        void GetPhone(   CString &p ) const;
		void GetEmail(   CString &e) const;
		void GetMember(  int &m     )  const;
        void GetMemberStr( CString &m )  const;
        void GetNoteStr( CString &n ) const;
		void GetAttendDateStr( CString &d ) const;


        CString GetPersonStr( CTime &date );
        CString GetPersonExportStr( CTime &date, char seperator );

        void GetAttendance( CString &atd ) const;

        void SetName(    CString &n )    { name = n; }
        void SetAddress( CString &a )    { address = a;}
        void SetCity(    CString &c )    { city = c; }
        void SetState(   CString &s )    { state = s;}
        void SetZip(     CString &z )    { zip = z; }
        void SetPhone(   CString &p )    { phone = p; }
		void SetEmail(   CString &e)     { email = e; }
		void SetNote(    CString &n )    { note = n; }
        void SetMember(  int &m    )     { mbr = m; }
        void SetPersonStatus(  char &s ) { person_status = s; }
        void SetLastVisit( CTime &v )    { last_visit = v; }
        void SetFirstVisit( CTime &v )   { first_visit = v; }

        void    SetAttedance( CString &a );
        void    SetAttedance( CTime &date );
        void    AddToAttedance( CTime &date );
        void    DeleteAttedance( CTime &date );
        CString GetAttedanceStr( CTime &date );
        void    SetMemberStr( int mbr );
        bool    Visited( CTime &date );
        bool    SameDate( CTime &date1, CTime &date2 );
        bool    SameWeek( CTime &date1, CTime &date2 );
        void    UpdateAttedanceStr( CTime &date );
        void    UpdateAttedance( void );
        void    CleanAttedance( void );
        int     GetVisitCnt( void );


        float   GetAttendPercent( void ) { return attend_percent; }
        CString GetName( void )          { return name; }
        CString GetNote( void )          { return note; }
        CString GetAddress( void )       { return address; }
        CString GetState( void )         { return state; }
        CString GetPhone( void )         { return phone; }
		CString GetEmail( void )           { return email; }
		CTime   GetLastVisit( void )     { return last_visit; }
        CTime   GetFirstVisit( void )    { return first_visit; }
        int     FieldCnt( void )         { return num_fields; } 
        int     IsMember( void )         { return mbr; }
        char    GetPersonStatus( void )  { return person_status; }
		int     GetPossibleCnt( void )   { return possible_visit_cnt; }
        
        int          GetMember( void );
        const int    GetFieldStart( int field );
        const int    GetFieldLen( int field );
        void         PadPerson( void );
        virtual void Serialize( CArchive &archive);
		CString      GetAttendDateStr( );


        enum { TFIELDS = 7 };

	    virtual ~CPrsnRcd();

};

#endif // !defined(AFX_PRSNRCD_H__859C16F3_6D0C_11D2_8045_44455354616F__INCLUDED_)
