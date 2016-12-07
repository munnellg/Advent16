#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4

#define STATE_OUT   0 /* Outside bracket */
#define STATE_IN    1 /* Inside bracket  */
#define NUM_STATES  2

int
is_palindrome( char buf[], int len ) {
	char *p1, *p2;
	p1 = buf;      /* Pointer to start */
	p2 = p1+len-1; /* Pointer to end   */

	/* Compare values and bring pointers together either until */
	/* palindrome disproved or pointers cross                  */
	do {
		if(*p1 != *p2){ return 0;} /* Not palindrome */
	} while( ++p1 <= --p2 );

	return 1; /* Palindrome */
}

void
insert_at(char buf[], char c, int idx) {
	char *p;

	/* Bump each char down one */
	for( p=buf; p-buf < idx; p++ ) {
		*p = *(p+1);
	}
	/* Insert char */
	*p = c;
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	int  state, count;
	int  npd[NUM_STATES] = {0}; /* Num valid palindromes for each state */
	char c;
	char buf[BUFFER_SIZE] = {0};
	
	/* Check for correct usage */
	if(argc < 2) {
		printf("Usage: ./d7p1 FILE\n");
		return EXIT_FAILURE;
	}

	/* Try to open the file */
	f = fopen(argv[1], "r");

	/* Handle failed file open */
	if(!f) {
		printf("Unable to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	/* Count of valid strings */
	count = 0;
	
	/* Get next char from stream */
	while( (c = getc(f)) != EOF ) {
    /* Insert char at end of buffer */
		insert_at(buf, c, BUFFER_SIZE-1);

		/* Update state and validate substring */
		state += (c=='[') - (c==']');
		npd[state] += is_palindrome(buf, BUFFER_SIZE) && buf[0] != buf[1];

		/* Newline means end of address. Check if valid */
		if(c == '\n') {
			count += (npd[STATE_OUT] > 0 && npd[STATE_IN] < 1);

			/* Reset states */
			npd[STATE_OUT] = npd[STATE_IN] = 0;
			state = 0;
		}
	}
	
	/* Close input file */
	fclose(f);

	printf("%d\n",count);
	
	return EXIT_SUCCESS;
}
