
/*
* See the file LICENSE for redistribution information.
*
* Copyright (c) 2012, 2017 WeilaiDb and/or its affiliates.  All rights reserved.
*
* $Id$
* File Name:bar_progress.c
Author:
Mail:
Created Time:2017年5月1日 22:36:07
*/




#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main()
{
	char bar[102];
	int i = 0;
	memset(bar, 0 ,sizeof(bar));
	char str[] = "|\\-/";
	
	while(i <= 100)
	{
		bar[i]='#';
		printf("[%-101s][%d%%][%c]\r", bar, i, str[i%4]);
		fflush(stdout);
		i++;
		usleep(100000);
	}
	printf("\n");
	
	
	return 0;
}





