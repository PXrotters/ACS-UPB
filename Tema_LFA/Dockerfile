FROM ghcr.io/open-education-hub/vmcheker-next-base-image/base-container:latest

RUN apt update -y && apt upgrade -y
RUN apt install cabal-install -y

COPY ./checker ${CHECKER_DATA_DIRECTORY}
