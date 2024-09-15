FROM postgres:16.4

# add ecpg to preprocess pcg code
RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
    libecpg-dev \  
    libecpg6
