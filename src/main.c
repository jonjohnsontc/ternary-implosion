/* Processed by ecpg (15.8 (Debian 15.8-0+deb12u1)) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "src/main.pgc"
#include <stdio.h>

int main() {
  { ECPGconnect(__LINE__, 0, "public@0.0.0.0:5432" , "postgres" , "example" , NULL, 0); }
#line 4 "src/main.pgc"

  printf("SQL connection executed\n");
  { ECPGdisconnect(__LINE__, "ALL");}
#line 6 "src/main.pgc"

  printf("SQL connected exited\n");
  return 0;
}