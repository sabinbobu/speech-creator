#!/bin/bash

. ./settings.sh

echo
echo +++ Run_all_tests.sh: Start +++

# if exist ../../Build/Make/Make_005_UserSettings.gmk del ../../Build/Make/Make_005_UserSettings.gmk

# Set the global test type to CTC or GCOV.
# For the test automation and production purposes you must use CTC
# This is configured in the settings
# SET TESTTYPE=CTC
# SET TESTTYPE=GCOV

export TESTTYPE="${PAR_COVER}"

# TAILOR
sh run_one_test.sh Mt_ApplBenchmark Unit "${PAR_TEST}" "${TESTTYPE}"


echo
echo +++ Run_all_tests.sh: Done +++
