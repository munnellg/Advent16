#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

#define HASH_SIZE       16
#define INPUT_SIZE      32
#define BUFFER_SIZE     64
#define PASSWORD_LENGTH  8
#define UNSET           -1
/* Converts hash to a password code */
int
decode( char hash[], int dest[] ) {
	int i, pos;
	pos = 0;

	for(i=0; i<3; i++) {
		pos <<= 8;
		pos |= (hash[i] & 0xFF);
	}

	if( pos < PASSWORD_LENGTH && dest[pos] == UNSET ) {
		dest[pos] = (hash[3]>>4) & 0xF;
		return 1;
	}
	
	return 0;
}

int
main( int argc, char *argv[] ) {
	int i, count;
	char buf[BUFFER_SIZE];
	char input[INPUT_SIZE];
	int password[PASSWORD_LENGTH];
	unsigned char hash[HASH_SIZE];

	for(i=0;i<PASSWORD_LENGTH;i++){password[i]=UNSET;}
	
	/* Prompt user for input */
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
		count += decode(hash, password);
	}

	for(i=0;i<PASSWORD_LENGTH;i++){
		printf("%X",password[i]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
