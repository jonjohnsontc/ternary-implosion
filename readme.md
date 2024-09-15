# POSTGRES ECPG Demo

Initially, I put this together as a exploration of the EXPLAIN command in postgres.
I still want to do that, but I've decided to use this scaffolding to check out
embedded SQL in postgres  

I have a couple of different datasets that I can use for this exploration:

- the imbdb non-commerical datasets: <https://developer.imdb.com/non-commercial-datasets/>.
- some electricity markets data that was uploaded to kaggle:
<https://www.kaggle.com/datasets/jaredandreatta/pjm-and-miso-electricity-market-data?resource=download>

I wanted to put together a schema and exploration of how to really use EXPLAIN in postgres. I downloaded all of the tables from the imdb non-commercial listing at <https://developer.imdb.com/non-commercial-datasets/>.

## Plan

- [x] Compile C file from pgc file
- [x] Connect to postgres db
- [] Execute Query and return results to stdout from C program
- [] Get build error from syntatical error program

## Log

- I should probably read through the documentation more, before setting up the
postgres environment
- I need to know how to:
  - Use the ecpg preprocessor to compile a C source file from a .pcg file
  - Connect to a postgres db and verify that the connection is valid
  - execute a query
  - return results of query to stdout (I would like to return the results to a
  C named variable to see how)
- Here's an example statement that I'm building to connect to my docker postgres

```postgres
EXEC SQL CONNECT TO public@0.0.0.0/5432 USER postgres/example
```

- Right now, I am including the password in the connection string, but I would
like to include a more secure method for accessing it
- After installing the ecpg library unto the image, I was able to spin it up and
compile a pcg program into a c source file. However, when I try to compile it I
run into errors including the header, ecpglib.h
- I was able to find the correct way to link and compile the resulting c source
file via the ecpg documentation
- Because I need to link to postgres' libraries, and include some of its header
files, I think the best option is to run these against some "local" database,
rather than adding a C compiler to the Docker image that I was previously using
- The ecpg preprocessing + c source compilation steps were executed as follows:

```bash
ecpg src/main.pgc
cc -I/usr/local/pgsql/include -c src/main.c
cc -o main main.o -L/usr/local/pgsql/lib -lecpg
```

- Specifically, compilation requires the ECPG header files from Postrgres' include
directory, and linked against the libecpg library
- I'm running into some issues using postgres on my debian WSL instance, there is an
unresolved symbol: UP
- Turns out that I was linking to a version of libreadline on in my /usr/local/lib
directory, which is based off of a manual installation of it (probably for stone
cold SQL). I removed the shared library from the directory and ran `ldconfig` which
found the system libreadline for postgres
- Debian Postgres Wiki: <https://wiki.debian.org/PostgreSql>
- I used the instructions in the Debian Postgres wiki to create a new pg user (jon),
which matches the OS user on Debian, and then created a `ecpg_demo` db, which I've
decided can serve as the db for this exercise

```bash
su - postgres
createuser --pwprompt jon
createdb -O jon ecpg_demo
```

- I'm having an issue copying the data from `raw_data.csv` into the table that I created
via the sql/ddl script. Here's what happens:

```bash
psql ecpg_demo -f src/seed_tables/electricity_market.sql
psql:src/seed_tables/electricity_market.sql:1: ERROR:  invalid input syntax for type numeric: "69,151.88"
CONTEXT:  COPY electricity_market, line 2, column miso_rtload: "69,151.88"
```

- ChatGPT pointed me to leveraging sed or a similar tool to remove the commas,
as they were causing the errors on read
- To make things easier, I think I should either change the dataset or load the
data in stages, maybe using some other table to make some edits before hitting
it's final form
- I was able to get the correct sed incantation to take the stream of data and
insert it into the table I had created earlier

```bash
sed 's/"\(-\?[0-9]\{1,3\}\),\([0-9]\{3\}\)\(\.[0-9]*\)\?"/\1\2\3/g' raw_data.csv | psql ecpg_demo -c "\copy electricity_market FROM stdin CSV HEADER"
```

- Now that I have data together, I can put a query together using ecpg
