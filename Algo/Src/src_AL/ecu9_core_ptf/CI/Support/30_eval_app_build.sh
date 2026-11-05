#!/bin/bash

. ./settings.sh

# check if build output hex file exists
buildOutput=Build/Bin/${MAIN_APP_NAME}/${MAIN_APP_NAME}_All.hex


if [ ! -f ../../$buildOutput ];
then
  echo "$buildOutput does not exist! Build error?"
  return
else
  echo "$buildOutput exists, Build OK."
fi

# check if additional package output exists
packageOutput="Build/Bin/$MAIN_APP_NAME/$MAIN_APP_PACKAGE_NAME"

if [ "$MAIN_APP_PACKAGE_NAME" = "" ];
then
  echo "Delivery package not defined, skipping check."
  return
fi

if [ ! -f ../../$packageOutput ];
then
  echo "$packageOutput does not exist! Package-build error?"
else
  echo `ls ../../${packageOutput}` exists, Package-build OK.
fi


