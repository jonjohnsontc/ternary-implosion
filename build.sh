set -eux;
# Build ecpg example
ecpg src/main.pgc;
cc -c -I/usr/local/pgsql/include src/main.c;
cc -o main main.o -L/usr/local/pgql/lib -lecpg -lpgtypes;

# Build lipbq example
cc -c -I/usr/local/pgsql/include src/libpq_example.c;
cc -o libpq_ex libpq_example.o -L/usr/local/pgql/lib -lpq;
