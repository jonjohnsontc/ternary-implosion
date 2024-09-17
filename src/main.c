/* Processed by ecpg (15.8 (Debian 15.8-0+deb12u1)) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "src/main.pgc"
#include <stdio.h>
#include <stdlib.h>

/* exec sql whenever sql_warning  sqlprint ; */
#line 4 "src/main.pgc"
 
/* exec sql whenever sqlerror  sqlprint ; */
#line 5 "src/main.pgc"


int main() {
  /* exec sql begin declare section */
        
        
        
        
       
  
#line 9 "src/main.pgc"
 const char * pword = getenv ( "POSTGRES_PASSWORD" ) ;
 
#line 10 "src/main.pgc"
 const char * user = "jon" ;
 
#line 11 "src/main.pgc"
 const int filter = 4 ;
 
#line 12 "src/main.pgc"
 const char * dbname = "unix:postgresql://localhost:5433/ecpg_demo" ;
 
#line 13 "src/main.pgc"
 long long count ;
/* exec sql end declare section */
#line 14 "src/main.pgc"
  

  if (pword == NULL) {
    fprintf(stderr, "Env var not found\n");
    exit(1);
  }

  { ECPGconnect(__LINE__, 0, dbname , user , pword , NULL, 0); 
#line 21 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 21 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 21 "src/main.pgc"

  printf("SQL connection executed\n");
  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( * ) from electricity_market where weekday = $1 ", 
	ECPGt_int,&(filter),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_long_long,&(count),(long)1,(long)1,sizeof(long long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 25 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 25 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 25 "src/main.pgc"

  printf("Total number of rows in electricity_market: %d\n", count);
  { ECPGdisconnect(__LINE__, "ALL");
#line 27 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 27 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 27 "src/main.pgc"

  printf("SQL connected exited\n");
  return 0;
}