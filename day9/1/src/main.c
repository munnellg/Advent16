#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void
decompress( FILE *f, int *count) {
	int nchars, nrepeats, i;
	char c;
	
	fscanf(f, "%dx%d)", &nchars, &nrepeats);
	*count += nchars*nrepeats;

	c=' ';
	for(i=0; i<nchars; i+= !isspace(c)) {
		c = getc(f);
	}
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	int count;
	char c;
	
	if( argc < 2 ) {
		printf("usage: d9p1 FILE");
		return EXIT_FAILURE;
	}
	
	f = fopen(argv[1], "r");

	if(!f) {
		printf("Unable to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	count = 0;
	while( (c=getc(f)) != EOF ) {
		if(c=='(') {
			decompress(f, &count);
		} else {
			count += !isspace(c);
		}
	}

	printf("%d\n",count);
	
	fclose(f);
	return EXIT_SUCCESS;
}
