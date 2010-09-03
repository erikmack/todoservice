#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "utility.h"

/* result must be free()d */
char * create_unique_slug( const char * raw, 
	UniqueTestFunc * is_unique, void * context_data ) {

	if( !raw || !is_unique ) return NULL; // null input invalid

#define MAX_INDEX 9999
#define MAX_INDEX_STR TOSTRING( MAX_INDEX )
	
	size_t max_index_str_len = strlen( MAX_INDEX_STR );

#undef MAX_INDEX_STR

	size_t sz = 
		strlen( raw ) 
		+ 1 /* dash */ 
		+ max_index_str_len /* index digits (MAX_INDEX) */ 
		+ 1 /* null term */;

	char * result = malloc( sz );

	if( !result ) return result; // OOM

	memset( result, 0, sz );

	char r;
	// iterate through each char in raw
	for( ; (r=*raw); raw++ ) {
		
		if( isalpha(r) || isdigit(r) ) {
			*(result + strlen(result)) = tolower(r);
		} else if(result) { // don't append - before first token
			
			// Reached non-printable char, 
			// maybe the preceding part is unique enough
			if( is_unique( result, context_data ) ) return result;

			// Append - if preceding char wasn't -
			if( *(result + strlen(result) - 1) != '-' ) {
				*(result + strlen(result)) = '-';
			}
		}
	}

	// We reached the end of raw input.  If result still isn't
	// unique, start appending xxx-2, xxx-3, etc. until it is
	if( is_unique( result, context_data ) ) return result;
	else {

		// Append - if preceding char wasn't -
		if( *(result + strlen(result) - 1) != '-' ) {
			*(result + strlen(result)) = '-';
		}

		char * digits_start_here = result + strlen(result);

		int index;
		for(index = 2; index <= MAX_INDEX; index++ ) {
			memset( digits_start_here, 0, max_index_str_len );
			snprintf( digits_start_here, max_index_str_len, "%d", index );
			if( is_unique( result, context_data ) ) return result;
		}
	}


#undef MAX_INDEX


	return NULL;
}
