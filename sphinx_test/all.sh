#!/bin/bash

NF=$1

echo "$NF"
echo ""

rm ../../test_data/temp/*
rm index/*
rm 5000_time.txt
rm 5000_output.txt
time ./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp 5000 > 5000_output.txt
rm index/testindex_delta*
du -h -b -d 1

{ time search -c sphinx.conf -i testindex test ; } >> "$NF"_time
{ time search -c sphinx.conf -i testindex test text ; } >> "$NF"_time
{ time search -c sphinx.conf -i testindex test text vladimir ; } >> "$NF"_time
{ time search -c sphinx.conf -i testindex blahblahblah ; } >> "$NF"_time

