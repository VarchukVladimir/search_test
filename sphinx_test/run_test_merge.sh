#!/bin/bash

CUR_DIR=`pwd`
if [ $# -ne 1 ] 
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

{ time indexer -c $CONF_FILE testindex_delta ; } 2>> time.txt

{ time indexer -c $CONF_FILE --merge testindex testindex_delta ; } 2>> time.txt

