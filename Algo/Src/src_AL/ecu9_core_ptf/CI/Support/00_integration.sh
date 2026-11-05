#!/bin/bash

echo
echo +++ 00_integration.sh: Start +++

# Display the timestamp
# call 02_timestamp.bat

# DB maintenance
sh 10_db_maintenance.sh

# Build main app
# call 20_build_app.bat

# Evaluate if app was successfully built ***THIS BELONGS TO THE REPORT, IS EXECUTED SEPARATELY IN THE CI ENGINE
# call 30_eval_app_build.bat

# Evaluate compiler warnings
# call 40_run_warning.bat

# Analyze the binary size with ALSize
# call 42_analyze_size.bat

# Calculate memory consumption
# call 45_analyze_map.bat

# Evaluate QAC + HIS metrics
#call 50_run_qac.bat

# Build and evaluate all Unit and Integration tests
sh 60_run_all_tests.sh

# Create report for the integrator
sh 70_do_report_integration.sh

# Also export data to doors
# call 80_report_doors.bat

# The overall report file is under:
# /CI/TestResults/SingleFileReport.txt

echo
echo +++ 00_integration.sh: Done +++
