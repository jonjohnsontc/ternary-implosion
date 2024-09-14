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

- [] Compile C file from pgc file
- [] Connect to postgres db
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
