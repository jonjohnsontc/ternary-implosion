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

// EXEC SQL WHENEVER SQLERROR CALL print_sqlca();

void print_sqlca() {
    fprintf(stderr, "==== sqlca ====\n");
    fprintf(stderr, "sqlcode: %ld\n", sqlca.sqlcode);
    fprintf(stderr, "sqlerrm.sqlerrml: %d\n", sqlca.sqlerrm.sqlerrml);
    fprintf(stderr, "sqlerrm.sqlerrmc: %s\n", sqlca.sqlerrm.sqlerrmc);
    fprintf(stderr, "sqlerrd: %ld %ld %ld %ld %ld %ld\n", sqlca.sqlerrd[0],sqlca.sqlerrd[1],sqlca.sqlerrd[2],
                                                          sqlca.sqlerrd[3],sqlca.sqlerrd[4],sqlca.sqlerrd[5]);
    fprintf(stderr, "sqlwarn: %d %d %d %d %d %d %d %d\n", sqlca.sqlwarn[0], sqlca.sqlwarn[1], sqlca.sqlwarn[2],
                                                          sqlca.sqlwarn[3], sqlca.sqlwarn[4], sqlca.sqlwarn[5],
                                                          sqlca.sqlwarn[6], sqlca.sqlwarn[7]);
    fprintf(stderr, "sqlstate: %5s\n", sqlca.sqlstate);
    fprintf(stderr, "===============\n");
}

int main() {
  /* exec sql begin declare section */
        
        
       
  
#line 24 "src/main.pgc"
 const char * pword = getenv ( "POSTGRES_PASSWORD" ) ;
 
#line 25 "src/main.pgc"
 const char * dbname = "unix:postgresql://localhost:5432/ecpg_demo" ;
 
#line 26 "src/main.pgc"
 long long count ;
/* exec sql end declare section */
#line 27 "src/main.pgc"
  

  if (pword == NULL) {
    fprintf(stderr, "Env var not found\n");
    exit(1);
  }

  { ECPGconnect(__LINE__, 0, dbname , NULL, NULL , NULL, 0); 
#line 34 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 34 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 34 "src/main.pgc"
 
  printf("SQL connection executed\n");
  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( * ) from electricity_market", ECPGt_EOIT, 
	ECPGt_long_long,&(count),(long)1,(long)1,sizeof(long long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 36 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 36 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 36 "src/main.pgc"

  { ECPGtrans(__LINE__, NULL, "commit");
#line 37 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 37 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 37 "src/main.pgc"

  printf("Total number of rows in electricity_market: %d\n", count);
  { ECPGdisconnect(__LINE__, "ALL");
#line 39 "src/main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 39 "src/main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 39 "src/main.pgc"

  printf("SQL connected exited\n");
  return 0;
}