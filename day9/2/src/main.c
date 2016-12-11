#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define BUFFER_SIZE 16

uint64_t
decompress( FILE *f, int *deleted) {
	uint64_t width;
	int nrepeats, nchars, disp, nspaces, del;
	char buf[BUFFER_SIZE];
	char c;

	fscanf(f, "%[^)]s)", buf);
	sscanf(buf, "%dx%d", &nchars, &nrepeats);
	getc(f); /* Discard closing paren */
	
	disp    = ftell(f);
	width   = nchars;
	nspaces = 0;

	/* Del is the number of characters deleted by recursive calls to */
	/* this function                                                 */
	del = 0;
	
	while ((ftell(f)-disp+nspaces) < nchars) {
		c = getc(f);

		/* So we can skip spaces */
		nspaces += isspace(c);

		/* Nested compressed data */
		if(c=='(') {
			width += decompress(f, &del);
		}
	}

	/* Remove characters consumed by recursion from our own width */
	width -= del;

	/* If the calling function wants to know how many characters we have consumend */
	if(deleted){
		/* We ate the length the string containing our arguments, + 2 for */
		/* the opening and closing parenthesis + the number of characters */
		/* we read                                                        */
			*deleted += strlen(buf) + 2 + nchars;
	}

	/* Compute the amount by which we expanded and return */
	return width*nrepeats;
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	uint64_t count;
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
			count += decompress(f, NULL);
		} else {
			count += !isspace(c);
		}
	}

	printf("%lu\n",count);
	
	fclose(f);
	return EXIT_SUCCESS;
}
