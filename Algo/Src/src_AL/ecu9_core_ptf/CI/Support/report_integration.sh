#!/bin/bash
. ./settings.sh

if [ -f *.tmp ];
then
	rm *.tmp
fi

rm ${UT_TMP}/*.tmp > /dev/null 2>&1

SPACES="     "

echo "*** Single file report of project $PLATFORM_NAME ***"
echo

# Display the timestamp
. ./02_timestamp.sh

echo
GIT_COMMIT_HASH_VALUE=`git rev-parse HEAD`
echo git hash: $GIT_COMMIT_HASH_VALUE
echo
echo
echo "*** Unit Test compiler statistics ***"
$DB_TOOL $DB < ut_report_compilerstatistics.sql
#echo select ".width", "5", max(length(name)), "9" from v_ut_results; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\ut_report_integration.tmp
echo ".width 16 6"> $UT_TMP/ut_report_compilerstatistics.tmp
echo ".headers on">> $UT_TMP/ut_report_compilerstatistics.tmp
echo ".mode column">> $UT_TMP/ut_report_compilerstatistics.tmp
echo "select project, result from v_ut_results_compiler_statistics;">> $UT_TMP/ut_report_compilerstatistics.tmp

$DB_TOOL $DB < $UT_TMP/ut_report_compilerstatistics.tmp

echo
echo
echo "*** Unit Test results ***"
$DB_TOOL $DB < ut_report_integration.sql
#echo select ".width", "5", max(length(name)), "9" from v_ut_results; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\ut_report_integration.tmp
echo ".width 5 24 9"> $UT_TMP/ut_report_integration.tmp
echo ".headers on">> $UT_TMP/ut_report_integration.tmp
echo ".mode column">> $UT_TMP/ut_report_integration.tmp
echo "select * from v_ut_results;">> $UT_TMP/ut_report_integration.tmp

COUNT_UT_PASSED=`$DB_TOOL $DB "select count(*) from v_ut_results where lower(result)='passed';"`
COUNT_UT_FAILED=`$DB_TOOL $DB "select count(*) from v_ut_results where lower(result)='*failed*';"`
echo "Passed: $COUNT_UT_PASSED   Failed: $COUNT_UT_FAILED"

$DB_TOOL $DB < $UT_TMP/ut_report_integration.tmp


echo
echo
echo "*** Integration Test results ***"
$DB_TOOL $DB < it_report_integration.sql
#echo select ".width", "12", max(length(name)), "9" from v_it_results; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\it_report_integration.tmp
echo ".width 12 9"> $UT_TMP/it_report_integration.tmp
echo ".headers on">> $UT_TMP/it_report_integration.tmp
echo ".mode column">> $UT_TMP/it_report_integration.tmp
echo "select * from v_it_results;">> $UT_TMP/it_report_integration.tmp

COUNT_IT_PASSED=`$DB_TOOL $DB "select count(*) from v_it_results where lower(result)='passed';"`
COUNT_IT_FAILED=`$DB_TOOL $DB "select count(*) from v_it_results where lower(result)='*failed*';"`
echo "Passed: $COUNT_IT_PASSED   Failed: $COUNT_IT_FAILED"

$DB_TOOL $DB < $UT_TMP/it_report_integration.tmp

echo
echo
echo "*** Module coverage statistics ***"
$DB_TOOL $DB < co_report_integration.sql

#echo select ".width", max(length(Project)), "-11", "-11", "-11", "-11", "-11", "-11" from v_ut_coverage_module; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\ut_coverage_module.tmp
echo ".width -11 -11 -11 -11 -11 -11"> $UT_TMP/ut_coverage_module.tmp
echo ".headers on">> $UT_TMP/ut_coverage_module.tmp
echo ".mode column">> $UT_TMP/ut_coverage_module.tmp
echo "select * from v_ut_coverage_module;">> $UT_TMP/ut_coverage_module.tmp
$DB_TOOL $DB < $UT_TMP/ut_coverage_module.tmp


echo
echo
echo "*** Function coverage statistics ***"
# rem $DB_TOOL $DB < co_report_integration.sql
#echo select ".width", "-10", "-10", max(length(function_name)), max(length(project)) from v_ut_coverage; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\co_report_integration.tmp
echo ".width -10 -10"> $UT_TMP/co_report_integration.tmp
echo ".headers on">> $UT_TMP/co_report_integration.tmp
echo ".mode column">> $UT_TMP/co_report_integration.tmp
echo "select * from v_ut_coverage;">> $UT_TMP/co_report_integration.tmp

COUNT_TOTAL=`$DB_TOOL $DB "select count(*) as c from v_ut_coverage_latest;"`
OUTPUT=$COUNT_TOTAL

echo "Count of functions total              :     $OUTPUT"
echo "                                               C0        C1"

COUNT_FULLCOV_C0=`$DB_TOOL $DB "select count(*) as c from v_ut_coverage_latest where C0_percent=100;"`
COUNT_FULLCOV_C1=`$DB_TOOL $DB "select count(*) as c from v_ut_coverage_latest where C1_percent=100;"`
OUTPUT0="${SPACES}${COUNT_FULLCOV_C0}"
OUTPUT1="${SPACES}${COUNT_FULLCOV_C1}"
echo "Count of functions with  100% coverage:     $OUTPUT0     $OUTPUT1"

COUNT_1_99_COV_C0=`$DB_TOOL $DB "select count(*) as c from v_ut_coverage_latest where 0<C0_percent and C0_percent<100;"`
COUNT_1_99_COV_C1=`$DB_TOOL $DB "select count(*) as c from v_ut_coverage_latest where 0<C1_percent and C1_percent<100;"`
OUTPUT0="${SPACES}${COUNT_1_99_COV_C0}"
OUTPUT1="${SPACES}${COUNT_1_99_COV_C1}"
echo "Count of functions with 99-1% coverage:     $OUTPUT0     $OUTPUT1"

COUNT_ZEROCOV_C0=`$DB_TOOL $DB "select count(*) as c from v_ut_coverage_latest where C0_percent=0;"`
COUNT_ZEROCOV_C1=`$DB_TOOL $DB "select count(*) as c from v_ut_coverage_latest where C1_percent=0;"`
OUTPUT0="${SPACES}${COUNT_ZEROCOV_C0}"
OUTPUT1="${SPACES}${COUNT_ZEROCOV_C1}"
echo "Count of functions with    0% coverage:     $OUTPUT0     $OUTPUT1"

$DB_TOOL $DB < $UT_TMP/co_report_integration.tmp
echo
echo "*** End of Single file report ***"
