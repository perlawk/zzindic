#include <stdio.h>
#include <stdlib.h>
#include "zigzag.h"

void readdata(char *path, int *dates, double *inhigh, double *inlow, long int *len) {
	FILE  *fp = fopen( path, "r");
	if ( !fp ) {
		fprintf(stderr, "open file %s error!\n", path);
		exit(0);
	}
	char header[128];
	/*char open[20];*/
	int y,m,d;
	double hi, lo, op, cl;
	fscanf( fp, "%[^\n]", header); // skip header
	int count=0;
	while( EOF != fscanf( fp, "%d-%d-%d,%lf,%lf,%lf,%lf%[^\n]\n", &y, &m, &d, &op, &hi, &lo, &cl, header)) {
			inhigh[count]	= hi;  // only hi and lo are used
			inlow[count] = lo;
			dates[count] = y*10000+m*100+d; // alter output format
			count++;
	}
	*len = count;
	fclose(fp);
	
}


int main( int argc, char *argv[]) {
	if ( argc < 2) {
		printf( "usage : %s csv_file\n", argv[0]);
		printf( "example: %s table.csv\n", argv[0]);
		return 0;
	}

	double inhigh[10000], inlow[10000], zz[10000];
	int dates[10000];

	double change;
	integer len, percent, retrace, lex;

	readdata( argv[1], dates, inhigh, inlow, &len);

	percent = 0; retrace = 0; lex = 0;
	change = 1.0;
	zigzag( inhigh, inlow, &len, &change, &percent, &retrace, &lex, zz );
	/*printf("len = %d\n", len);*/
	int i=0;
	while( i < len) {
		if( zz[i] > 0) {
			printf("%d %g\n", dates[i], zz[i]);
		}
		i++;
	}

	return 0;
}
