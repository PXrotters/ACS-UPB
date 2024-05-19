FROM gitlab.cs.pub.ro:5050/operating-systems/assignments-docker-base

COPY ./checker ${CHECKER_DATA_DIRECTORY}
RUN mkdir ${CHECKER_DATA_DIRECTORY}/../tests
COPY ./tests ${CHECKER_DATA_DIRECTORY}/../tests
RUN mkdir ${CHECKER_DATA_DIRECTORY}/../util
COPY ./util ${CHECKER_DATA_DIRECTORY}/../util
