#!/bin/bash

. ./settings.sh
#set -x
# $1 = Mt_CddExample
# $2 = Unit / Integration
# $3 = CUnit
# $4 = CTC / GCOV

echo
echo +++ Running test: "$1" Start +++

GIT_COMMIT_HASH_VALUE=`git rev-parse HEAD`

cd ../../Build/VS
./build.sh W00
cd ../../CI/Support

export FILEPATH="${PAR_ECU_UT}""${PAR_PRJ}"_Test_"$1"
export FILENAME="${PAR_ECU_UT}""${PAR_PRJ}"_Test_"$1"_ExecutionResult

buildOutput=Build/Bin/"${FILEPATH}"
if [ ! -d ../../"${buildOutput}" ]
then
  echo "${buildOutput}" does not exist! Build error?
  export SUCCESS="FATAL"
else
  echo "${buildOutput}" exists, Build OK.
  export SUCCESS="OK"
 fi
echo
echo '+++ Parsing unit test results (Pass/Fail) +++'

export  INFILE_UT=../../Build/Bin/"${FILEPATH}"/"${FILENAME}".txt
export SQLFILE_UT=../../Build/Bin/"${FILEPATH}"/"${FILENAME}"_"$4".sql

if [ -e "${SQLFILE_UT}" ]
then
     rm "${SQLFILE_UT}"	
fi

"${TEST_RESULT_PARSER_TOOL}" --input="${INFILE_UT}" --output="${SQLFILE_UT}" --platform="${PLATFORM_NAME}" --project_name="$1" --test_type="$2" --tool_name="$4" --hash_value="${GIT_COMMIT_HASH_VALUE}" --parser_type=PassFail


echo "insert into ut_results (platform, project, tool, githash, date, time, type, name, result) values (\"$PLATFORM_NAME\", \"$1\", \"Compiler\", \"$GIT_COMMIT_HASH_VALUE\", \"`date -I`\", \"`date +"%T"`\", \"Statistics\", \"$1\", \"$SUCCESS\");" >> $SQLFILE_UT

echo .
echo +++ Feeding the DB with PassFail data +++

$DB_TOOL $DB < $SQLFILE_UT

echo .
echo +++ Parsing unit test coverage +++

if  [ "$4" = "GCOV" ]
then
INFILE_CO=../../Build/Bin/$FILEPATH/coverage_report.html
SQLFILE_CO=../../Build/Bin/$FILEPATH/GcovProfile.sql
fi

if [ "$2" = "Unit" ]
then
#TEST_RESULT_PARSER_TOOL is not able to parse the Ubuntu index.html file so we will use Unix commands
#$TEST_RESULT_PARSER_TOOL --input=$INFILE_CO --output=$SQLFILE_CO --platform=$PLATFORM_NAME --project_name=$1 --test_type=$2 --tool_name=$4 --hash_value=$GIT_COMMIT_HASH_VALUE --parser_type=$4_Coverage
	startline=`grep -n "Lines:" $INFILE_CO | head -1 | cut -f1 -d:`
	endline=`expr $startline + 3`
	sed -n "${startline},${endline}p" $INFILE_CO > /tmp/lines
	LineHit=`head -2 /tmp/lines | tail -1 | cut -f2 -d">" | cut -f1 -d"<"`
	LineTotal=`head -3 /tmp/lines | tail -1 | cut -f2 -d">" | cut -f1 -d"<"`
	LineCoverage=`head -4 /tmp/lines | tail -1 | cut -f2 -d">" | cut -f1 -d"<" | sed 's/%//g'`

	echo "create table if not exists ut_coverage (platform, project, tool, githash, date, time, C0_percent INTEGER, C0_tested_lines INTEGER, C0_testable_lines INTEGER, C1_percent INTEGER, C1_tested_lines INTEGER, C1_testable_lines INTEGER, function_name, UNIQUE (project, githash, function_name) ON CONFLICT IGNORE);" > $SQLFILE_CO
	echo "insert into ut_coverage (platform, project, tool, githash, date, time, C0_percent, C0_tested_lines, C0_testable_lines, C1_percent, C1_tested_lines, C1_testable_lines, function_name) values (\"$PLATFORM_NAME\",\"$1\",\"GCOV\",\"$GIT_COMMIT_HASH_VALUE\",\"`date -I`\",\"`date +%T`\",\"$LineCoverage\",\"$LineHit\",\"$LineTotal\",\"0\",\"0\",\"0\",\"\")" >> $SQLFILE_CO
	echo .
	echo +++ Feeding the DB with coverage data +++

	$DB_TOOL $DB < $SQLFILE_CO
fi

echo .
echo +++ Running test: "$1" Done +++

