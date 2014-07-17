#!/bin/bash

CUR_DIR=`pwd`
CONF_FILE=$CUR_DIR/sphinx.conf
if ! [ -f index ]; then
	mkdir -p index
fi

indexer -c $CONF_FILE testindex
