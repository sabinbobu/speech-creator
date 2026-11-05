#!/bin/bash
. ./settings.sh
echo .
echo +++ db_maintenance.bat: Start +++

$DB_TOOL $DB < create_empty_db.sql

$DB_TOOL $DB < create_blacklist.sql

#$DB_TOOL $DB < error_list_PAR_CC.sql

if [ ! -d $UT_TMP ]
then
   mkdir -p $UT_TMP
fi

if [ -f $UT_TMP/create_blacklist.tmp ];
then	
  rm $UT_TMP/create_blacklist.tmp
fi

# Removed "--skip 1" command from import

echo ".mode csv">> $UT_TMP/create_blacklist.tmp
echo ".import $CONFIG_PATH_SQL/module_size_plan.csv module_size_plan">> $UT_TMP/create_blacklist.tmp

echo ".mode csv">> $UT_TMP/create_blacklist.tmp
echo ".import $CONFIG_PATH_SQL/file_to_module.csv file_to_module">> $UT_TMP/create_blacklist.tmp

echo ".mode csv">> $UT_TMP/create_blacklist.tmp
echo ".import $CONFIG_PATH_SQL/section_to_memory.csv section_to_memory">> $UT_TMP/create_blacklist.tmp

$DB_TOOL $DB < $UT_TMP/create_blacklist.tmp

echo +++ db_maintenance.bat: Done +++
