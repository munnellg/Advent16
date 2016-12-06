#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE  32

int
main( int argc, char *argv[] ) {
	FILE *f;
	int s1, s2, s3;
	int n_valid;
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

	n_valid = 0;
	
	/* Read sequence of instructions */
	while( (fgets(buf, BUFFER_SIZE, f))  != NULL ) {
		if(sscanf(buf, "%d %d %d", &s1, &s2, &s3) > 0) {
			printf("%d %d %d\n", s1, s2, s3);
			n_valid += (s1+s2 > s3) && (s2+s3 > s1) && (s3+s1 > s2);
		}
	}
	printf("%d\n", n_valid);
	/* Close input file */
	fclose(f);
	
	return EXIT_SUCCESS;
}
