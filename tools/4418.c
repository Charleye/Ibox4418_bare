/******************************************************************************
 *
 * ****************************************************************************
 * Copyright (C) 2016
 * Written by Kart (kartdream@163.com)
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 * ****************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 512

int main (int argc, char *argv[])
{

	if (argc != 5)
	{
		printf ("Usage: ./mk4418 <destination file> <Nsih.txt> <2ndboot.bin> <u-boot.bin>\n");
		return -1;
	}

	typedef unsigned char uchar;
	uchar *p = NULL;
	FILE *fp = NULL;
	FILE *nf = NULL;
	FILE *nd = NULL;
	FILE *bi = NULL;
	unsigned int data;

	p = (uchar *)malloc (SIZE);
	memset (p, 0, SIZE);
	if (p == NULL)
		return -1;

	nf = fopen (argv[1], "w+b");
	if (nf == NULL)
		return -1;

	fp = fopen (argv[2], "r");
	if (fp == NULL)
		return -1;

	nd = fopen (argv[3], "r");
	if (nd == NULL)
		return -1;
	
	bi = fopen (argv[4], "r");
	if (bi == NULL)
		return -1;

	while (fgets(p, SIZE, fp))
	{
		if (!isxdigit (p[0]))
			continue;
		sscanf (p, "%x", &data);
		fwrite (&data, sizeof(unsigned int), 1, nf);
	}

	unsigned int count = 0;
	unsigned int total = 0;
	while ((count = fread (p, sizeof(unsigned char), SIZE, nd)) != 0)
	{
		fwrite (p, sizeof(unsigned char), count, nf);
	}
	
	unsigned int * pp = (unsigned int *)malloc (4326 * sizeof(unsigned int));
	memset (pp, 0, 4326 * sizeof (unsigned int));

	fwrite (pp, sizeof(unsigned int), 4326, nf);
    
	rewind (fp);
	while (fgets(p, SIZE, fp))
	{
		if (!isxdigit (p[0]))
			continue;
		sscanf (p, "%x", &data);
		fwrite (&data, sizeof (unsigned int), 1, nf);
	}
	
	count = 0;
	while ((count = fread (p, sizeof (unsigned char), SIZE, bi)) != 0)
	{
		fwrite (p, sizeof (unsigned char), count, nf);
		total += count;
	}

	fseek (nf, 0x7e44, SEEK_SET);
	fwrite (&total, sizeof (unsigned int), 1, nf);
	count = 0x42C00000;
	fwrite (&count, sizeof (unsigned int), 1, nf);
	fwrite (&count, sizeof (unsigned int), 1, nf);
	

	free (p);
	free (pp);
	fclose (fp);
	fclose (nf);
	fclose (nd);
	fclose (bi);
	return 0;
}
