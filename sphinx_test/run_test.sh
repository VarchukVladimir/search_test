#!/bin/bash

CUR_DIR=`pwd`
if [ $# -lt 1 ] 
then
    echo "Usage: `basename $0` index path"
    exit $WRONG_ARGS
fi
INDEX_PATH=$1

sed s@{ABS_PATH}@$CUR_DIR@ sphinx.conf.template | \
sed s@{INDEX_PATH}@$INDEX_PATH@ > sphinx.conf

CONF_FILE=$CUR_DIR/sphinx.conf
if ! [ -f index ]; then
	mkdir -p index
fi

rm "$2"_time.txt

{ time indexer -c $CONF_FILE testindex ; } 2>> "$2"_time.txt

#time search -c $CONF_FILE -i testindex "test" text
