#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 4

#define STATE_OUT   0 /* Outside bracket */
#define STATE_IN    1 /* Inside bracket  */
#define NUM_STATES  2

#define HASH_WIDTH 5
#define BITVECTOR_WIDTH (sizeof(uint32_t)*8)
#define BITVECTOR_SIZE  ((0x1 << (HASH_WIDTH*(BUFFER_SIZE)) )/BITVECTOR_WIDTH)

#define ROOT_CHAR 'a'

int
hash_bab(char buf[]) {
	int hash;
	hash = 0;

	hash |= (buf[1]-ROOT_CHAR);
	hash = (hash << HASH_WIDTH) | (buf[0]-ROOT_CHAR);
	hash = (hash << HASH_WIDTH) | (buf[1]-ROOT_CHAR);

	return hash;
}

int
hash_aba(char buf[]) {
	int hash;
	hash = 0;
	
	hash |= (buf[0] - ROOT_CHAR);
	hash = (hash << HASH_WIDTH) | (buf[1] - ROOT_CHAR);
	hash = (hash << HASH_WIDTH) | (buf[2] - ROOT_CHAR);

	return hash;
}

int
has_overlap( uint32_t bv1[], uint32_t bv2[], int len ) {
	int i;
	int count;
	count = 0;
	for(i=0; i<len; i++) {
		count += bv1[i] & bv2[i];
	}
	return count > 0;
}

void
clear( uint32_t bitvector[], int len ) {
	memset( bitvector, 0, sizeof(*bitvector)*len);
}

void
set ( uint32_t bitvector[], int value ) {
	bitvector[value/BITVECTOR_WIDTH] |= (0x1 << value%BITVECTOR_WIDTH);
}

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
	int  state, count, hash;
	uint32_t bvs[NUM_STATES][BITVECTOR_SIZE]; /* State bitvectors */
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
	clear(bvs[STATE_IN],  BITVECTOR_SIZE);
	clear(bvs[STATE_OUT], BITVECTOR_SIZE);
	
	/* Get next char from stream */
	while( (c = getc(f)) != EOF ) {
    /* Insert char at end of buffer */
		insert_at(buf, c, BUFFER_SIZE-2);
	
		/* Update state and validate substring */
		state += (c=='[') - (c==']');
		
		if(is_palindrome(buf, BUFFER_SIZE-1) && buf[0] != buf[1] && isalpha(buf[1])) {
			hash = (state)? hash_bab(buf) : hash_aba(buf);
			set(bvs[state], hash);
		}

		/* Newline means end of address. Check if valid */
		if(c == '\n') {
			count += has_overlap(bvs[STATE_IN], bvs[STATE_OUT], BITVECTOR_SIZE); 

			/* Reset states */
			state = 0;
			clear(bvs[STATE_IN],  BITVECTOR_SIZE);
			clear(bvs[STATE_OUT], BITVECTOR_SIZE);
		}
	}
	
	/* Close input file */
	fclose(f);

	printf("%d\n",count);
	
	return EXIT_SUCCESS;
}
