#!/bin/sh

echo running $1 $2
LOG_NAME=$1
$PWD/test.py $ORDER | tee $PWD/inputs/input.$LOG_NAME | $PWD/test
if [ $? -ne 0 ];
then
	echo error proccessing input.$1
	exit 1;
fi

