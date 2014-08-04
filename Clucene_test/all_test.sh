#!/bin/bash


NF=$1

echo ""
echo "$NF"
rm ~/search_test/clucene/index/*
rm ~/search_test/test_data/temp/*
rm "$NF"_time.txt
rm "$NF"_output.txt
./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp ~/search_test/clucene/index "$NF" > "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text vladimir  ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index blahblahblah ; } 2>> "$NF"_output.txt

NF=1000
echo ""
echo "$NF"
rm ~/search_test/clucene/index/*
rm ~/search_test/test_data/temp/*
rm "$NF"_time.txt
rm "$NF"_output.txt
./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp ~/search_test/clucene/index "$NF" > "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text vladimir  ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index blahblahblah ; } 2>> "$NF"_output.txt

NF=750
echo ""
echo "$NF"
rm ~/search_test/clucene/index/*
rm ~/search_test/test_data/temp/*
rm "$NF"_time.txt
rm "$NF"_output.txt
./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp ~/search_test/clucene/index "$NF" > "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text vladimir  ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index blahblahblah ; } 2>> "$NF"_output.txt

NF=500
echo ""
echo "$NF"
rm ~/search_test/clucene/index/*
rm ~/search_test/test_data/temp/*
rm "$NF"_time.txt
rm "$NF"_output.txt
./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp ~/search_test/clucene/index "$NF" > "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text vladimir  ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index blahblahblah ; } 2>> "$NF"_output.txt

NF=250
echo ""
echo "$NF"
rm ~/search_test/clucene/index/*
rm ~/search_test/test_data/temp/*
rm "$NF"_time.txt
rm "$NF"_output.txt
./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp ~/search_test/clucene/index "$NF" > "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text vladimir  ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index blahblahblah ; } 2>> "$NF"_output.txt


NF=100
echo ""
echo "$NF"
rm ~/search_test/clucene/index/*
rm ~/search_test/test_data/temp/*
rm "$NF"_time.txt
rm "$NF"_output.txt
./incremental_test.sh ~/search_test/test_data/gutenberg ~/search_test/test_data/temp ~/search_test/clucene/index "$NF" > "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index test text vladimir  ; } 2>> "$NF"_output.txt
{ time ./build/bin/cl_demo -search ~/search_test/clucene/index blahblahblah ; } 2>> "$NF"_output.txt


