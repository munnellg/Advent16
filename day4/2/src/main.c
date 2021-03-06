#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE   128
#define CODE_MAX_LEN   64
#define CHECKSUM_LEN    5
#define NCHARS         26
#define ROOT_CHAR     'a'

struct room {
	int  id;
	char code[CODE_MAX_LEN];
	char check_sum[CHECKSUM_LEN+1];
};

/* Compare the value of two characters for our checksum */
int
compare( int a, int b, int freq[] ) {
	return (freq[a] - freq[b] == 0)? b-a : freq[a] - freq[b];
}

/* Swap the value of two ints */
void
swap( int *a, int *b ) {
	*a ^= *(b);
	*b ^= *(a);
	*a ^= *(b);
}

/* Build checksum from character frequencies */
void
build_checksum( char out[], int counts[] ) {
	int sorted[NCHARS] = {0};
	int  i;
	int *j;
	
	/* Insertion sort */
	for( i=0; i<NCHARS; i++ ) {
		sorted[i] = i;
		for( j=sorted+i; j!=sorted; j-- ) {
			if(compare(*j, *(j-1), counts) > 0) {
				swap(j, j-1);
			}
		}
	}

	/* Ords to chars */
	for(i=0; i<CHECKSUM_LEN; i++) {
		out[i] = sorted[i] + ROOT_CHAR;
	}
	out[CHECKSUM_LEN] = '\0';
}

/* Compute checksum of input string */
void
checksum( char in[], char out[] ) {
	int  ord;
	char *c;
	int   counts[NCHARS] = {0};

	/* Count frequency of each letter in code */
	for( c=in; *c!='\0'; c++ ) {
		ord = *c-ROOT_CHAR;
		if(ord>=0 && ord <NCHARS) {
			counts[ord]++;
		}
	}

	/* Use data to build checksum */
	build_checksum( out, counts );
}

void
decode( struct room *r, char out[] ) {
	char *c1, *c2;
	int   x;
	
	for(c1=r->code, c2=out; *c1 != '\0'; c1++, c2++) {
		if( *c1 == '-' ) {
			*c2 = ' ';
		} else {
			x = *c1 - ROOT_CHAR;
			x += r->id;
			x %= NCHARS;
			*c2 = x+ROOT_CHAR;
		}
	}
	*c2 = '\0';
}

/* Parse a buffer to extract room information */
void
str2room( struct room *r, char data[]) {
	char *c1, *c2;

	/* Parse code of arbitrary length */
	for(c1=data, c2=r->code; !isdigit(*c1); c1++, c2++) {
		*c2 = *c1;
	}
	/* Null terminate */
	*(c2-1) = '\0';

	/* Get ID and checksum from buffer */
	/* Data is formatted at this point, so let's just use sscanf */
	sscanf(c1, "%d[%[^]]s",&(r->id),r->check_sum);
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	int  id_sum;
	char buf[BUFFER_SIZE];
	char cs[CHECKSUM_LEN+1];
	struct room r;
	
	/* Check for correct usage */
	if(argc < 2) {
		printf("Usage: ./d2p1 FILE\n");
		return EXIT_FAILURE;
	}

	/* Try to open the file */
	f = fopen(argv[1], "r");

	/* Handle failed file open */
	if(!f) {
		printf("Unable to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	id_sum = 0;
	
	/* Read sequence of instructions */
	while( (fgets(buf, BUFFER_SIZE, f))  != NULL ) {
		str2room(&r, buf);
		checksum(r.code, cs);
		if(strcmp(cs, r.check_sum) == 0) {
			decode(&r, buf);
			printf("%4d: %s\n", r.id, buf);
		}
	}

	/* Close input file */
	fclose(f);
	
	return EXIT_SUCCESS;
}
