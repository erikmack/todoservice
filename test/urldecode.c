
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"


/* Usage: urldecode input expected */
int main(int argc, char ** argv) {

	if( argc != 3 ) return 1;

	char * input = *(argv + 1);
	char * expected = *(argv + 2);

	char * output = url_decode( input );

	if( !output ) return EXIT_FAILURE;

	int success = !strcmp( output, expected );
	
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
