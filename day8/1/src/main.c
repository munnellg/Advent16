
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_RECT     "rect"
#define COMMAND_ROTATE "rotate"

#define COMMAND_SIZE 16
#define BUFFER_SIZE  32

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 6

static int g_screen[SCREEN_WIDTH*SCREEN_HEIGHT];

int
gcd( int a, int b ) {
	while( b != 0) {
		int c = a;
		a = b;
		b = c%a;
	}
	return a;
}

void
screen_shift( int axis, int n, int row_shift ) {
	int i, j, index, d, bound;
	int tmp1, tmp2; 
	int *x, *y;

	/* Initialize pointers and bounds depending on direction */
	bound = (row_shift)? SCREEN_WIDTH : SCREEN_HEIGHT;
	x = (row_shift)? &index : &axis;
	y = (row_shift)? &axis  : &index;

	/* Fix bounds */
	n %= bound;
	if( n < 0 ) {
		n += bound;
	}

	/* Determine the size of sets for shift */
	d = gcd( n, bound );

	/* Iterate over each set */
	for( i=0; i<d; i++ ) {
		/* Store value for final shift */
		index = i;
		tmp1 = g_screen[*x + (*y)*SCREEN_WIDTH];

		/* Iterate over set elements */
		for( j = i-n+bound; j != i; j=(j-n+bound)%bound ) {
			/* Get source */
			index = j;
			tmp2  = g_screen[*x + (*y)*SCREEN_WIDTH];

			/* Put in destination */
			index = (j + n) % bound;
			g_screen[*x + (*y)*SCREEN_WIDTH] = tmp2;
		}
		/* Shift final value */
		index = (i+n);
		g_screen[*x + (*y)*SCREEN_WIDTH] = tmp1;
	}
}

void
screen_draw_rect( int w, int h ) {
	int y;
	for(y=0; y<h; y++) {		
		memset(&g_screen[y*SCREEN_WIDTH], 1, w*sizeof(*g_screen) );
	}
}

int
screen_count_set() {
	int count, i;
	count = 0;
	for( i=0; i<SCREEN_WIDTH*SCREEN_HEIGHT; i++ ) {
		count += g_screen[i] != 0;
	}
	return count;
}


void
rotate( char buf[] ) {
	int  index, shift;
	char axis;

	char direction[COMMAND_SIZE];
	sscanf(buf, "%[^ ] %c=%d by %d", direction, &axis, &index, &shift);
	
	screen_shift(index, shift, axis=='y');
}

void
rect( char buf[] ) {
	int w, h;

	sscanf(buf, "%dx%d", &w, &h);
	screen_draw_rect(w, h);	
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	char buf[BUFFER_SIZE];
	char command[COMMAND_SIZE];

	if( argc < 2 ) {
		printf("usage: ./d8p1 FILE\n");
		return EXIT_FAILURE;
	}

	f = fopen(argv[1], "r");

	if(!f) {
		printf("Unable to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	while( fgets(buf, BUFFER_SIZE, f) != NULL ) {
		sscanf(buf, "%s", command);
		
		if(strcmp(command, COMMAND_RECT) == 0) {
			rect( &buf[strlen(command)+1]);
		} else if (strcmp(command, COMMAND_ROTATE) == 0) {
			rotate( &buf[strlen(command)+1] );
		}
	}
	fclose(f);

	printf("%d\n", screen_count_set());
	
	return EXIT_SUCCESS;
}
