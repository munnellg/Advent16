#include <stdio.h>
#include <stdlib.h>

#define N_SIDES       3 /* Number of sides in our shape */
#define BUFFER_SIZE  32 /* Size of our input buffer     */

/* Validate triangle according to the rule of sides */
int
valid( int s1, int s2, int s3 ) {
	return (s1+s2 > s3) && (s2+s3 > s1) && (s3+s1 > s2);
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	int t1[N_SIDES];
	int t2[N_SIDES];
	int t3[N_SIDES];
	int i, n_valid;
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
	n_valid = 0;
	i = 0;
		
	/* Read sequence of instructions */
	while( (fgets(buf, BUFFER_SIZE, f))  != NULL ) {
		/* Read values for each triangle side */
		if(sscanf(buf, "%d %d %d", &t1[i%N_SIDES], &t2[i%N_SIDES], &t3[i%N_SIDES]) > 0 ) {
			/* Check if we've read a trio of sides */
			if( !(++i % N_SIDES) ) {
				/* Validate if we have three triangles */
				n_valid += valid(t1[0], t1[1], t1[2]);
				n_valid += valid(t2[0], t2[1], t2[2]);
				n_valid += valid(t3[0], t3[1], t3[2]);
			}
		}
	}
	printf("%d\n", n_valid);
	/* Close input file */
	fclose(f);
	
	return EXIT_SUCCESS;
}
