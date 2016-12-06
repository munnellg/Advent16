#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NCHARS             26
#define MAX_MESSAGE_WIDTH   8
#define BUFFER_SIZE        16
#define ROOT_CHAR         'a'

int  g_freqs[MAX_MESSAGE_WIDTH*NCHARS] = {0};

void
update_freqs(char buf[]) {
	int i;
	int ord;
	
	for( i=0; i<MAX_MESSAGE_WIDTH && buf[i]!='\0'; i++ ) {
		ord = buf[i] - ROOT_CHAR;
		if(ord >= 0 && ord < NCHARS ) {
			g_freqs[ord + i*NCHARS]++;
		}
	}
}

void
decode_at(int depth) {
	int *p, *min;
	char c;
	
	min=&g_freqs[depth*NCHARS];

	if(depth < MAX_MESSAGE_WIDTH) {

		/* Find min entry */
		for(p=min; p-(&g_freqs[depth*NCHARS]) < NCHARS ; p++) {
			if( *p < *min || *min==0 ) {
				/* Ignore zeroes */
				min = ( *p > 0 )? p: min;
			}
		}

		/* If min is nonzero, then print it */
		if(*min) {
			c = (char)(min - &g_freqs[depth*NCHARS]);
			printf("%c", c + ROOT_CHAR);
			decode_at(depth+1);
		}
	}
}

void
decode() {
	/* Solved with recursion */
	decode_at(0);
	printf("\n");
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	char buf[BUFFER_SIZE];
	
	/* Check for correct usage */
	if(argc < 2) {
		printf("Usage: ./d6p2 FILE\n");
		return EXIT_FAILURE;
	}

	/* Try to open the file */
	f = fopen(argv[1], "r");

	/* Handle failed file open */
	if(!f) {
		printf("Unable to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	/* Read sequence of instructions */
	while( (fgets(buf, BUFFER_SIZE, f))  != NULL ) {
		/* Update the frequencies for each letter with new input */
		update_freqs(buf);
	}
	
	/* Close input file */
	fclose(f);

	/* Now decode the message */
	decode();
	
	return EXIT_SUCCESS;
}
