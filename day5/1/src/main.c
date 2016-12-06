#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

#define HASH_SIZE       16
#define INPUT_SIZE      32
#define BUFFER_SIZE     64
#define PASSWORD_LENGTH  8

/* Converts hash to a password code */
int
to_code( char hash[] ) {
	int code,i;
	code = 0;

	/* Code is simply the value of the first three bytes of the
	 * hash. Validity of the code will be determined later */
	for(i=0; i<3; i++) {
		code <<= 8;
		code |= (hash[i] & 0xFF);
	}
	return code;
}

int
main( int argc, char *argv[] ) {
	int i, count, code;
	char buf[BUFFER_SIZE];
	char input[INPUT_SIZE];
	unsigned char hash[HASH_SIZE];

	/* Prompt user for input */
	/* (Don't really feel like using a file) */
	printf("Enter ID: ");
	fgets(input, INPUT_SIZE, stdin);

	/* Remove trailing newline */
	input[strcspn(input, "\n")] = 0;

	/* Begin search */
	for(i=0, count=0; count<PASSWORD_LENGTH; i++) {
		/* Concate code with integer */
		sprintf(buf, "%s%d", input, i);

		/* Get hash of string */
		MD5(buf, strlen(buf), hash);

		/* Extract code from hash */
		code = to_code(hash);

		/* Validate code */
		if(code < 0x10) {
			/* Print code if valid */
			printf("%X", code);
			
			/* Increment count of digits found */
			count++;
		}
	}

	printf("\n");
	
	return EXIT_SUCCESS;
}
