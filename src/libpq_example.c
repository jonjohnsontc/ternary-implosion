#include <stdio.h>
#include <libpq-fe.h> // Include the libpq library

int main() {
    // Connection parameters: change them to match your setup
    const char *conninfo = "host=localhost port=5433 dbname=postgres user=postgres password=example";
    
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
    PGresult *res = PQexec(conn, "SELECT version();");

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
