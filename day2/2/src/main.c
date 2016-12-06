#include <stdio.h>
#include <stdlib.h>

#define MOVE_UP    'U' /* Move Up command    */
#define MOVE_DOWN  'D' /* Move Down command  */
#define MOVE_LEFT  'L' /* Move Left command  */
#define MOVE_RIGHT 'R' /* Move right command */

#define KEYPAD_WIDTH  5
#define MAX_DIST      (KEYPAD_WIDTH/2)
#define CENTER_KEY    (KEYPAD_WIDTH+MAX_DIST)

/* Compute Manhattan distance from origin */
int
dist(int x, int y) {
	return abs(x) + abs(y);
}

/* Translate x,y coordinates to a key value */
int
to_key(int x, int y) {
	return x + CENTER_KEY + (abs(y)+1)*MAX_DIST*((y>0)-(y<0));
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	int x, y, dx, dy;
	char c;

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
	
	/* Initialize values */
	x  = -2; y  = 0;
	dx =  0; dy = 0;

	/* Read sequence of instructions */
	while( (c = getc(f))  != EOF ) {

		/* Compute orientation */
		dx = (c==MOVE_RIGHT) - (c==MOVE_LEFT);
		dy = (c==MOVE_DOWN)  - (c==MOVE_UP);

		/* Compute displacement */
		if( dist(x+dx, y+dy) <= MAX_DIST ) {
			x += dx;
			y += dy;
		}

		/* Print key if newline */
		if (c == '\n') {
			printf("%X", to_key(x,y));
		}
	}
	printf("\n");
	
	/* Close input file */
	fclose(f);
	
	return EXIT_SUCCESS;
}
