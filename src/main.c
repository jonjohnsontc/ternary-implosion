/* Processed by ecpg (15.8 (Debian 15.8-0+deb12u1)) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "src/main.pgc"
#include <stdio.h>
#include <stdlib.h>
#include <pgtypes_numeric.h>

/* exec sql whenever sql_warning  sqlprint ; */
#line 5 "src/main.pgc"
 
/* exec sql whenever sqlerror  sqlprint ; */
#line 6 "src/main.pgc"


int main() {
  /* exec sql begin declare section */
        
        
        
        
       
     
     
  
#line 10 "src/main.pgc"
 const char * pword = getenv ( "POSTGRES_PASSWORD" ) ;
 
#line 11 "src/main.pgc"
 const char * user = "jon" ;
 
#line 12 "src/main.pgc"
 const int filter = 4 ;
 
#line 13 "src/main.pgc"
 const char * dbname = "unix:postgresql://localhost:5433/ecpg_demo" ;
 
#line 14 "src/main.pgc"
 long long count ;
 
#line 15 "src/main.pgc"
 numeric * my_guy ;
 
#line 16 "src/main.pgc"
 int * my_guy_ind ;
/* exec sql end declare section */
#line 17 "src/main.pgc"
  

  if (pword == NULL) {
    fprintf(stderr, "Env var not found\n");
    exit(1);
  }

  { ECPGconnect(__LINE__, 0, dbname , user , pword , NULL, 0); 
#line 24 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 24 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 24 "src/main.pgc"

  printf("SQL connection executed\n");
  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( * ) from electricity_market where weekday = $1 ", 
	ECPGt_int,&(filter),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_long_long,&(count),(long)1,(long)1,sizeof(long long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 28 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 28 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 28 "src/main.pgc"

  printf("Total number of rows in electricity_market: %d\n", count);
  
  my_guy = PGTYPESnumeric_new();

  // use cursors for iterating over a result set
  /* declare thurs cursor for select miso_hydro_gen from electricity_market order by miso_hydro_gen */
#line 36 "src/main.pgc"

  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare thurs cursor for select miso_hydro_gen from electricity_market order by miso_hydro_gen", ECPGt_EOIT, ECPGt_EORT);
#line 37 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 37 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 37 "src/main.pgc"

  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from thurs", ECPGt_EOIT, 
	ECPGt_numeric,&(my_guy),(long)1,(long)0,sizeof(numeric), 
	ECPGt_int,&(my_guy_ind),(long)1,(long)0,sizeof(int), ECPGt_EORT);
#line 38 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 38 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 38 "src/main.pgc"
  
  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close thurs", ECPGt_EOIT, ECPGt_EORT);
#line 39 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 39 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 39 "src/main.pgc"


  if (*my_guy_ind < 0)
    printf("miso_hydro_gen was NULL\n");
  else
    printf("miso_hydro_gen is %s\n", PGTYPESnumeric_to_asc(my_guy, -1));



  { ECPGdisconnect(__LINE__, "ALL");
#line 48 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 48 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 48 "src/main.pgc"

  printf("SQL connection exited\n");
  return 0;
}