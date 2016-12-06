#include <stdio.h>
#include <stdlib.h>

#define MOVE_UP    'U'
#define MOVE_DOWN  'D'
#define MOVE_LEFT  'L'
#define MOVE_RIGHT 'R'

#define KEYPAD_WIDTH  3

int
to_key(int x, int y) {
	return x + 2 + (y+1)*KEYPAD_WIDTH;
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
	x  = 0; y  = 0;
	dx = 0; dy = 1;

	/* Read sequence of instructions */
	while( (c = getc(f))  != EOF ) {

		dx = (c==MOVE_RIGHT) - (c==MOVE_LEFT);
		dy = (c==MOVE_DOWN)  - (c==MOVE_UP);

		x += dx*(x!=dx);
		y += dy*(y!=dy);

		if (c == '\n') {
			printf("%d", to_key(x,y));
		}
	}
	printf("\n");
	/* Close input file */
	fclose(f);
	
	return EXIT_SUCCESS;
}
