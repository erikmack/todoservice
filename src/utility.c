/*
todoservice - a toy implementation of a not-quite-RESTful "todo" service implemented
              as a CGI program with Redis as a data store
Copyright (C) 2010 Free Software Foundation

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "utility.h"

/* result must be free()d */
char * url_decode( const char * raw ) {

	if( !raw ) return NULL;

	size_t sz = strlen( raw ) + 1;
	char * result = malloc( sz );
	memset( result, 0, sz );

	if( !result ) return result; // OOM

	char r;
	// iterate through each char in raw
	for( ; (r=*raw); raw++ ) {
		
		if( r == '%' ) {
			char c1, c2, cout;
			if( *(raw+1) && *(raw+2) ) {
				raw++;
				c1 = *raw;
				
				if(isdigit(c1)) cout = c1-'0';
				else if( c1>='a' && c1 <='f' ) cout = 10 + (c1-'a');
				else if( c1>='A' && c1 <='F' ) cout = 10 + (c1-'A');
				else return NULL;

				cout *= 16;
				
				raw++;
				c2 = *raw;
				
				if(isdigit(c2)) cout += (c2-'0');
				else if( c2>='a' && c2 <='f' ) cout += (10 + (c2-'a'));
				else if( c2>='A' && c2 <='F' ) cout += (10 + (c2-'A'));
				else return NULL;

				*(result + strlen( result )) = cout;

			} else return NULL;
		} else if( r == '+' ) {
			*(result + strlen( result )) = ' ';
		} else {
			*(result + strlen( result )) = r;
		}

	}

	return result;
}







/* result must be free()d */
char * locate_unique_slug( const char * raw, 
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
		if( *result && *(result + strlen(result) - 1) != '-' ) {
			*(result + strlen(result)) = '-';
		}

		char * digits_start_here = result + strlen(result);

		int index = 2;
		if( !*result ) index = 1;
		for(; index <= MAX_INDEX; index++ ) {
			memset( digits_start_here, 0, max_index_str_len );
			snprintf( digits_start_here, max_index_str_len, "%d", index );
			if( is_unique( result, context_data ) ) return result;
		}
	}


#undef MAX_INDEX


	return NULL;
}
