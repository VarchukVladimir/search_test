#!/bin/bash


echo "5000"
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

echo "1000"
echo ""

rm ../../test_data/temp/*
rm index/*
rm 1000_time.txt
rm 1000_output.txt
time ./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp 1000 > 1000_output.txt
rm index/testindex_delta*
du -h -b -d 1

time search -c sphinx.conf -i testindex test
time search -c sphinx.conf -i testindex test text
time search -c sphinx.conf -i testindex test text vladimir
time search -c sphinx.conf -i testindex blahblahblah

echo "750"
echo ""

rm ../../test_data/temp/*
rm index/*
rm 750_time.txt
rm 750_output.txt
time ./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp 750 > 750_output.txt
rm index/testindex_delta*
du -h -b -d 1

time search -c sphinx.conf -i testindex test
time search -c sphinx.conf -i testindex test text
time search -c sphinx.conf -i testindex test text vladimir
time search -c sphinx.conf -i testindex blahblahblah

echo "500"
echo ""

rm ../../test_data/temp/*
rm index/*
rm 500_time.txt
rm 500_output.txt
time ./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp 500 > 500_output.txt
rm index/testindex_delta*
du -h -b -d 1

time search -c sphinx.conf -i testindex test
time search -c sphinx.conf -i testindex test text
time search -c sphinx.conf -i testindex test text vladimir
time search -c sphinx.conf -i testindex blahblahblah

echo "250"
echo ""

rm ../../test_data/temp/*
rm index/*
rm 250_time.txt
rm 250_output.txt
time ./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp 250 > 250_output.txt
rm index/testindex_delta*
du -h -b -d 1

time search -c sphinx.conf -i testindex test
time search -c sphinx.conf -i testindex test text
time search -c sphinx.conf -i testindex test text vladimir
time search -c sphinx.conf -i testindex blahblahblah

echo "100"
echo ""

rm ../../test_data/temp/*
rm index/*
rm 100_time.txt
rm 100_output.txt
time ./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp 100 > 100_output.txt
rm index/testindex_delta*
du -h -b -d 1

time search -c sphinx.conf -i testindex test
time search -c sphinx.conf -i testindex test text
time search -c sphinx.conf -i testindex test text vladimir
time search -c sphinx.conf -i testindex blahblahblah


