#!/bin/sh

#${PATH_TOOLSGENERIC} is a variable which can be set from outside (e.g. in Linux or in a Jenkinsfile)
#${TOOLSGENERIC_PATH} is a variable used internally in the CI/Support scripts
#if ${PATH_TOOLSGENERIC} is not set, use default "../../../toolsgeneric"

TOOLSGENERIC_PATH=${PATH_TOOLSGENERIC}

if [ "${PATH_TOOLSGENERIC}X" = "X" ];
then
     export TOOLSGENERIC_PATH=../../../toolsgeneric
fi

DB=../db/unix_nightly.sqlite3
DB_TOOL=sqlite3
TEST_RESULT_PARSER_TOOL="../../../../toolsalinternal/ALTestResult/Build/build_easy_on_host/ALTestResultUnix.exe"
GIT=git
PYTHON=${TOOLSGENERIC_PATH}/Utilities/CommonDomain/python/python27/python.exe

#TAILOR

PAR_ECU=W00
PAR_MCAL=Gen_Gen
PAR_CC=UNIX_GCC
PAR_TEST=CUnit
PAR_COVER=GCOV
PAR_CORE=x64
PAR_PRJ=In005
PAR_VAR=Test
PAR_BUILD=Mt_ApplBenchmark
PAR_KEY=NonKey
PAR_RULE=rebuild
PAR_RULE_DELIVERY=rebuild_delivery

PAR_ECU_UT=W00

PLATFORM_NAME=In005
MAIN_APP_NAME=${PAR_ECU}${PAR_PRJ}_${PAR_VAR}_${PAR_BUILD}
MAIN_APP_PACKAGE_NAME=
BUILD_BIN_PATH=../../Build/Bin
ERROR_LIST_PATH=../../Build/Tmp/${MAIN_APP_NAME}/err
REPORT_PATH=../TestResults
REPORT_PATH_SQL=..//TestResults
SINGLE_FILE_REPORT=${REPORT_PATH}/SingleFileReport_UT.txt
UT_TMP=../Tmp
CONFIG_PATH=../Config
CONFIG_PATH_SQL=../Config

if [ ! -d "${UT_TMP}" ]
then
  mkdir "${UT_TMP}"
fi

if [ ! -d "${REPORT_PATH}" ]
then
  mkdir "${REPORT_PATH}"
fi
