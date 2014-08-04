#!/bin/bash

echo $#
if [ $# -ne 4 ]  
then
	echo "USAGE [folder with text files] [folder for temp files] [folder for save index] [number of file to be indexed at once]"	
	exit 1
fi

FILE_COUNTER=0
DIR_COUNTER=0
rm -fr "$2"/*
rm "$4"_time.txt
rm -fr "$3"/*

for file in $1/*; do
	if [ $FILE_COUNTER -eq $4 ] 
	then
		FILE_COUNTER=0
		let DIR_COUNTER=DIR_COUNTER+1
		if [ $DIR_COUNTER -eq 1 ] 
		then
			{ time ./build/bin/cl_demo -build "$2" "$3" ; } 2> "$4"_time.txt
		fi 
		{ time ./build/bin/cl_demo -add "$2" "$3" ; } 2>> "$4"_time.txt
		rm -fr "$2"/*
	fi	
	
	let FILE_COUNTER=FILE_COUNTER+1
	NEW_FILE=$2/${file##*/}
	echo "$file => $NEW_FILE $FILE_COUNTER, $DIR_COUNTER"
	cp "$file" "$NEW_FILE"
done

