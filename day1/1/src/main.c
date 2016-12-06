#include <stdio.h>
#include <stdlib.h>

#define TURN_RIGHT 'R'
#define TURN_LEFT  'L'
#define BUFFER_SIZE 8

int
main( int argc, char *argv[] ) {
	FILE *f;
	char  r;
	int x, y, dx, dy, disp;
	char buf[BUFFER_SIZE];

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

	/* Read next instruction */
	while( fscanf(f, "%s", buf)  != EOF ) {
		/* Parse instruction */
		sscanf(buf, "%c%d\n", &r, &disp);

		/* Rotate */
		dy = dy * ( 1 - 2*( r==TURN_LEFT ) );
		dx = dx * ( 1 - 2*( r==TURN_RIGHT) ); 
		
		dy ^= dx;
		dx ^= dy;
		dy ^= dx;

		/* Move */
		x += disp * dx;
		y += disp * dy;
	}

	printf("%d\n", abs(x)+abs(y));
	
	/* Close input file */
	fclose(f);
	
	return EXIT_SUCCESS;
}
