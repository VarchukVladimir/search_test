/*
 * xreate_xml.c
 *
 *  Created on: Jul 15, 2014
 *      Author: Volodymyr Varchuk
 */

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#undef TEST

void open_xml ( int fxml )
{
	const char *header =
			"<?xml version=\"1.0\" encoding=\"utf-8\"?>\
\n\
<sphinx:docset>\n\
<sphinx:schema>\n\
<sphinx:attr name=\"file_name_attr\" type=\"string\"/>\n\
<sphinx:field name=\"file_name\"/>\n\
<sphinx:field name=\"content\"/>\n\
</sphinx:schema>\n";
	write( fxml, header, strlen( header ) );
}

void close_xml ( int fxml )
{
	const char *xml_close = "\
</sphinx:docset>\n";
	write( fxml, xml_close, strlen( xml_close ) );
}

void open_xml_doc ( int fxml, long doc_id, char *fname )
{
	char *str_ =
			"<sphinx:document id=\"%ld\">\n\
<file_name_attr><![CDATA[%s]]></file_name_attr>\n\
<file_name><![CDATA[%s]]></file_name>\n\
<content><![CDATA[";
	char *buff = NULL;
	int buffsize = 0;
	buffsize = strlen( str_ ) + strlen( fname ) * 20;
	buff = malloc( buffsize );
	snprintf( buff, buffsize, str_, doc_id, fname, fname );
	write( fxml, buff, strlen( buff ) );
#ifdef TEST
	fwrite( buff, 1, strlen( buff ), stderr );
#endif
	free( buff );
}

void close_xml_doc ( int fxml )
{
	const char *str = "]]></content>\n\
</sphinx:document>\n \n";
	write( fxml, str, strlen( str ) );
}

int main ( int argc, char ** argv )
{
	int fxml;

	DIR *dir;
	struct dirent *entry;
	long doc_id = 1;
	if ( argc != 3 )
	{
		fprintf ( stderr, "Wrong number of arguments!\n" );
		return -1;
	}

	if ( strncmp ( argv[1], "--stdout", 8 ) == 0 )
		fxml = 1;
	else
		fxml = open( argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR );

	if ( fxml < 0 )
	{
		fprintf ( stderr, "Wrong file name\n" );
		return -1;
	}
	dir = opendir( argv[2] );

	open_xml( fxml );
	while(( entry = readdir( dir ) ) != NULL)
	{
		if ( entry->d_type == DT_REG )
		{
			if ( strncasecmp (entry->d_name + strlen ( entry->d_name ) - 4, ".txt", 3) != 0 )
				continue;
			char *fpath = NULL;
			char *buff = NULL;
			FILE *f = NULL;
			int fpath_len = strlen( argv[2] ) + strlen( entry->d_name ) + 2;
			fpath = malloc( fpath_len );
			snprintf( fpath, fpath_len, "%s/%s", argv[2], entry->d_name );
			struct stat finfo;
			if ( stat( fpath, &finfo ) != 0 )
			{
				fprintf ( stderr, "Error stat\n" );
				closedir(dir);
				return -1;
			}
			f = fopen( fpath, "r" );
			if ( !f )
			{
				fprintf ( stderr, "Error fopen\n" );
				closedir(dir);
				return -1;
			}
			buff = malloc( finfo.st_size );
			open_xml_doc( fxml, doc_id++, fpath );
			fread( buff, 1, finfo.st_size, f );
			int i = 0;
			for( i = 0; i < finfo.st_size - 1; i++ )
			{
				//if ( !(buff[i] >= 'A' && buff[i] <= 'Z' || buff[i] >= 'a' && buff[i] <= 'z' || buff [i] == '\n' || buff[i] >= 0 && buff[i] <= 9) )
				if ( !isalnum( buff[i] ) && buff[i] != '\n' )
					buff[i] = ' ';
			}
			write( fxml, buff, finfo.st_size - 1 );
			close_xml_doc( fxml );
			fclose( f );
			free( fpath );
			free( buff );
			if ( strncmp ( argv[1], "--stdout", 8 ) != 0 )
				if ( ( doc_id % 150 ) == 0 )
					printf( "files added to xml %ld\r", doc_id );
		}
	}
	close_xml( fxml );
	closedir(dir);
	if ( strncmp ( argv[1], "--stdout", 8 ) != 0 )
		printf( "total files added to xml %ld\r", doc_id );
	printf( "\n" );
	close( fxml );
	return 0;
}
