#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TURN_RIGHT      'R'
#define TURN_LEFT       'L'
#define BUFFER_SIZE       8
#define WORD_WIDTH       32
#define GRID_WIDTH      512
#define PLANE_WIDTH    (GRID_WIDTH/2)
#define BITVECTOR_SIZE (GRID_WIDTH*GRID_WIDTH)

uint32_t g_bitvector[BITVECTOR_SIZE/WORD_WIDTH] = {0};

int
idx(int x, int y) {
	return PLANE_WIDTH + x + (PLANE_WIDTH + y) * PLANE_WIDTH;
}

int
lookup(int x, int y) {
	int z;
	z = idx(x,y);
	return (g_bitvector[z/WORD_WIDTH] & (1 << (z%WORD_WIDTH))) > 0;
}

void
set (int x, int y) {
	int z;
	z = idx(x,y);
	g_bitvector[z/WORD_WIDTH] |= (1 << (z%WORD_WIDTH));
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	char  r;
	int x, y, dx, dy;
	int i, j,	disp;
	char buf[BUFFER_SIZE];
	
	/* Check for correct usage */
	if(argc < 2) {
		printf("Usage: ./d1p2 FILE\n");
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
		for( i=x+dx, j=y+dy; i!=(x + disp*dx) || j!=(y + disp*dy); i+=dx, j+=dy) {
			if( lookup(i,j) ){
					printf("%d\n", abs(i)+abs(j));
					return EXIT_SUCCESS;
			}
			set(i,j);
		}
		
		x = i;
		y = j;
	}
	
	/* Close input file */
	fclose(f);
	
	return EXIT_SUCCESS;
}
