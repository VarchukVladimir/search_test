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

rm "$2"_time.txt
CONF_FILE=$CUR_DIR/sphinx.conf
if ! [ -f index ]; then
	mkdir -p index
fi

{ time indexer -c $CONF_FILE testindex_delta ; } 2>> "$2"_time.txt

{ time indexer -c $CONF_FILE --merge testindex testindex_delta ; } 2>> "$2"_time.txt

