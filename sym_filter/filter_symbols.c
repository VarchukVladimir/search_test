/*
 * filter_symbols.c
 *
 *  Created on: Jul 21, 2014
 *      Author: Volodymyr Varchuk
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


int main ( int argc, char **argv )
{
	int i = 0;
	char *dir_in = NULL;
	char *dir_out = NULL;
	DIR *dir = NULL;
	struct dirent *entry;
	int file_count = 0;
	int file_count_delta = 0;
	int file_count_temp;
	int percent = 0;

	dir_in = strdup( argv[1] );
	dir_out = strdup( argv[2] );

	dir = opendir( dir_in );
	if ( !dir )
	{
		printf ( "wrong dir\n" );
		return -1;
	}
	while(( entry = readdir( dir ) ))
	{
		file_count++;
	}
	closedir (dir);

	file_count_delta = file_count / 100;

	dir = opendir( dir_in );
	while(( entry = readdir( dir ) ))
	{
		if ( entry->d_type == DT_REG )
		{

			char *filePath = NULL;
			char *newfilePath = NULL;
			filePath = (char *) malloc( sizeof(char) * ( strlen( entry->d_name ) + strlen( dir_in ) + 2 ) );
			newfilePath = (char *) malloc( sizeof(char) * ( strlen( entry->d_name ) + strlen( dir_out ) + 2 ) );
			sprintf( filePath, "%s/%s", dir_in, entry->d_name );
			sprintf( newfilePath, "%s/%s", dir_out, entry->d_name );
			char *buff = NULL;
			struct stat st;
			if ( stat( filePath, &st ) != 0 )
				return -1;
			buff = malloc( st.st_size );

			FILE *fin = NULL;
			FILE *fout = NULL;
			fin = fopen( filePath, "r" );
			fout = fopen( newfilePath, "w" );
			fread( buff, st.st_size, 1, fin );
			int i = 0;
			for( i = 0; i < st.st_size; i++ )
				if ( !isalnum( buff[i] ) && buff[i] != '\n' )
					buff[i] = ' ';
			fwrite( buff, st.st_size, 1, fout );
			fclose( fin );
			fclose( fout );
			free( buff );
			free( filePath );
			free( newfilePath );
			file_count_temp++;
			if ( file_count_temp == file_count_delta )
			{
				file_count_temp = 0;
				percent++;
			}
			printf ( "processed %d%%, files left %d\r", percent, file_count - percent*file_count_delta);
		}
	}
	printf ( "processed %d%%, total files %d\n", percent, file_count);
	return 0;
}
