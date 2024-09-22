#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h> // Include the libpq library

int main() {
    // Connection parameters: change them to match your setup
    const char *pword = getenv("POSTGRES_PASSWORD");
    if (pword == NULL) {
      fprintf(stderr, "password not found\n");
      exit(1);
    }
    char conninfo[255] = "host=localhost port=5433 dbname=ecpg_demo user=jon password=";
    strcat(conninfo, pword);

    // Initialize the connection to PostgreSQL
    PGconn *conn = PQconnectdb(conninfo);

    // Check if the connection was successful
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);  // Close connection if failed
        return 1;
    }

    printf("Connected to database successfully.\n");

    // Execute a simple query (getting the PostgreSQL version)
    // PGresult *res = PQexec(conn, "SELECT version();");
    PGresult *res = PQexec(conn, "SELECT count(*) from electricity_market"); 

    // Check if the query was successful
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    // Print the result of the query (the version of PostgreSQL)
    printf("PostgreSQL version: %s\n", PQgetvalue(res, 0, 0));

    // Clear the result and close the connection
    PQclear(res);
    PQfinish(conn);

    return 0;
}
