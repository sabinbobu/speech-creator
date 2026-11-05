#!/bin/bash
#Extract the year, month, day from the date
TIMESTAMP=`date +"%Y%m%d-%H%M"`
#Zero-pad the date if it is before 10th


#Extract the hour and minute from the time
DATE_TIME=`date +"%a %m/%d/%Y %H:%M:%S.%2N"`
#Zero-pad the hour if it is before 10am


echo Report creation timestamp: $TIMESTAMP

echo $DATE_TIME
