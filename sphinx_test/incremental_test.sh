#!/bin/bash

echo $#
if [ $# -ne 3 ]  
then
	echo "USAGE [folder with text files] [folder for temp files] [number of file to be indexed at once]"	
	exit 1
fi

FILE_COUNTER=0
DIR_COUNTER=0
rm -fr "$2"/*
for file in $1/*; do
	if [ $FILE_COUNTER -eq $3 ] 
	then
		FILE_COUNTER=0
		let DIR_COUNTER=DIR_COUNTER+1
		if [ $DIR_COUNTER -eq 1 ] 
		then
			./run_test.sh "$2"
		fi 
#		echo "$file  $FILE_COUNTER ----- $DIR_COUNTEER"

		./run_test_merge.sh "$2"
		rm -fr "$2"/*
	fi	
	
	let FILE_COUNTER=FILE_COUNTER+1
	NEW_FILE=$2/${file##*/}
	echo "$file => $NEW_FILE $FILE_COUNTER, $DIR_COUNTER"
	cp "$file" "$NEW_FILE"
done

