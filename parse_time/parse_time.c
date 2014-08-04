/*
 * parse_time.c
 *
 *  Created on: Jul 24, 2014
 *      Author: Volodymyr Varchuk
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#undef TEST
#define TS "|"

long int getmillisecond (char *str)
{
	if ( str == NULL )
		return 0;
	int str_len = strlen (str);
	int i = 0;
	int m_len = 0;
	int s_len = 0;
	long int msec_total = 0;
	char m_buff[100];
	char s_buff[100];
	char ms_buff[100];
	for ( i =0; i< str_len; i++)
		if (isdigit (str[i]) )
			break;
	char *end_m = strstr ( str + i, "m" );
	char *end_s = strstr ( str, "." );
	m_len = (end_m - str) - i;
	strncpy ( m_buff, str + i, m_len);
	m_buff[m_len] = '\0';
	end_m++;
	s_len= end_s - end_m;
	strncpy ( s_buff, end_m, s_len);
	s_buff [s_len] = '\0';
	strncpy ( ms_buff, end_s + 1, 3 );
	ms_buff[3]  = '\0';
	msec_total = atoi (m_buff) * 1000 * 60 + atoi (s_buff) * 1000 + atoi (ms_buff);
#ifdef TEST
	printf ( "minutes %s, sec = %s, msec = %s, msectotal=%ld\n", m_buff, s_buff, ms_buff, msec_total );
#endif
	return msec_total;
}

typedef struct {
	long int real_time;
	long int user_time;
	long int sys_time;
}time_set;

time_set * init_time_set(  )
{
	time_set * ts = malloc ( sizeof (time_set) );
	ts->real_time = 0;
	ts->user_time = 0;
	ts->sys_time =0;
	return ts;
}


int main (int argc, char ** argv)
{
#ifdef TEST
	char *str = "real	500m59.333s";
	printf ( "%s\n", str );
	getmillisecond (str);
	return 0;
#endif

	if (argc == 1)
	{
		printf ( "USAGE:\n ./parse_time [file with time data] [-i if only indexation time records]\n");
		return -1;
	}
	char *filename = strdup (argv [1]);
	int si = 0;
	FILE *f = NULL;
	char line [100];
	line [100] = '\0';
	time_set *indexation_time = init_time_set();
	time_set *merge_time = init_time_set();
	int p_r = 0, p_u = 0, p_s = 0, p_i = 0, p_m = 0;

	int iteration_counter = 0;

	if ( argc == 3 )
		if (strncmp (argv[2],"-si", 3) == 0 )
			si = 1;
	if ( argc == 4 )
	{
		if ( strstr ( argv[3], "r" ) != NULL )
			p_r = 1;
		if ( strstr ( argv[3], "u" ) != NULL )
			p_u = 1;
		if ( strstr ( argv[3], "s" ) != NULL )
			p_s = 1;
		if ( strstr ( argv[3], "i" ) != NULL )
			p_i = 1;
		if ( strstr ( argv[3], "m" ) != NULL )
			p_m = 1;
	}
	f = fopen ( filename, "r" );
	if ( !f )
	{
		printf ("%s - wrong file\n", filename);
		return -1;
	}

	int is_merge_time = -1;
	while ( fgets (line, 100, f) != NULL )
	{
		if (line [0] == '\n')
			continue;
		long int cur_r = 0;
		long int cur_u = 0;
		long int cur_s = 0;

		if ( line[0] == 'r' )
		{
			iteration_counter++;
			if ( iteration_counter == 1 )
			{
				is_merge_time = 0;
			}
			else if ( iteration_counter % 2 == 0 && iteration_counter != 1 )
				is_merge_time = 0;
			else
				is_merge_time = 1;

			cur_r = getmillisecond( line );
			if ( is_merge_time == 0 )
			{
				indexation_time->real_time = indexation_time->real_time + cur_r;
				if ( p_i && p_r )
					printf ( "indexation real %s%ld \n", TS, cur_r );
			}
			else
			{
				merge_time->real_time = merge_time->real_time + cur_r;
				if ( p_m && p_r )
					printf ( "merge real %s%ld \n", TS, cur_r );
			}
		}
		if ( line[0] == 'u' )
		{
			cur_u = getmillisecond( line );
			if ( is_merge_time == 0 )
			{
				indexation_time->user_time = indexation_time->user_time + cur_u;
				if ( p_i && p_u )
					printf ( "indexation user %s%ld \n", TS, cur_u );
			}
			else
			{
				merge_time->user_time = merge_time->user_time + cur_u;
				if ( p_m && p_u )
					printf ( "merge user %s%ld \n", TS, cur_u );
			}
		}
		if ( line[0] == 's' )
		{
			cur_s = getmillisecond( line );
			if ( is_merge_time == 0 )
			{
				indexation_time->sys_time = indexation_time->sys_time + cur_s;
				if ( p_i && p_s )
					printf ( "indexation sys %s%ld \n",TS, cur_s );
			}
			else
			{
				merge_time->sys_time = merge_time->sys_time + cur_s;
				if ( p_m && p_s )
					printf ( "merge sys %s%ld \n", TS, cur_s );
			}
		}
	}

	printf ( "indexing total real %ld\n", indexation_time->real_time );
	printf ( "indexing total user %ld\n", indexation_time->user_time );
	printf ( "indexing total sys %ld\n", indexation_time->sys_time );

	printf ( "merge total real %ld\n", merge_time->real_time );
	printf ( "merge total user %ld\n", merge_time->user_time );
	printf ( "merge total sys %ld\n", merge_time->sys_time );

	long int m = 0;
	long int s = 0;
	long int ms = 0;
	m = (indexation_time->real_time + merge_time->real_time)/60000;
	s = ((indexation_time->real_time + merge_time->real_time) - m * 60000)/1000;
	ms = (indexation_time->real_time + merge_time->real_time) - m * 60000 - s * 1000;
	printf ("%ld = %ldm%ld.%lds\n", indexation_time->real_time + merge_time->real_time, m, s, ms );
	m = (indexation_time->user_time + merge_time->user_time)/60000;
	s = ((indexation_time->user_time + merge_time->user_time) - m * 60000)/1000;
	ms = (indexation_time->user_time + merge_time->user_time) - m * 60000 - s * 1000;
	printf ("%ld = %ldm%ld.%lds\n", indexation_time->user_time + merge_time->user_time, m, s, ms );
	m = (indexation_time->sys_time + merge_time->sys_time)/60000;
	s = ((indexation_time->sys_time + merge_time->sys_time) - m * 60000)/1000;
	ms = (indexation_time->sys_time + merge_time->sys_time) - m * 60000 - s * 1000;
	printf ("%ld = %ldm%ld.%lds\n", indexation_time->sys_time + merge_time->sys_time, m, s, ms );

	return 0;
}
