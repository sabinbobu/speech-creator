#!/bin/bash

. ./settings.sh

echo
echo "+++ 70_do_report_integration.sh: Start +++"

if [ -f $SINGLE_FILE_REPORT ];
then 
	rm $SINGLE_FILE_REPORT
fi

. ./report_integration.sh > $SINGLE_FILE_REPORT

echo
echo "+++ 70_do_report_integration.sh: Done +++"
