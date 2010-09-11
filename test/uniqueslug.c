#include <string.h>
#include <stdlib.h>

#include "utility.h"

struct exclude {
	int count;
	char ** existing_slugs;
};

static int is_slug_unique( char * test, void * context_data ) {

	if( !test || !(*test) ) return 0;
	
	struct exclude * exclusions = (struct exclude *)context_data;

	int i = 0;
	for(i=0; i<exclusions->count; i++) {
		char * one_existing = *(exclusions->existing_slugs + i);

		if(!strcmp(one_existing,test)) return 0;
	}
	return 1;
}

/* Usage: ./uniqueslug input output existing [existing...]
 */
int main(int argc, char ** argv ) {

	if(argc < 3) return -1;

	char * test = *(argv+1);

	struct exclude exclusion;
	exclusion.count = argc - 3;
	exclusion.existing_slugs = argv+3;

	char * expected = *(argv+2);

	char * returned = locate_unique_slug( test, &is_slug_unique, &exclusion );

	int success = returned && !strcmp( expected, returned );
	if(returned) {
		free(returned);
		returned = NULL;
	}

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
