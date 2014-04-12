#!/bin/bash
export ORDER=1000
export TIMES=20

if [ ! -z $1 ];
then
ORDER=$1;
fi;

if [ ! -z $2 ];
then
TIMES=$2;
fi;
mkdir -p $PWD/inputs
seq $TIMES | sed -r "s/([0-9]+)/$$.\1/g" | \
	parallel --gnu --halt 1 "$PWD/run_single_test.sh"

