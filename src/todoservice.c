#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "credis.h"
#include "utility.h"

#define XML_HEADER "<?xml version=\"1.0\"?>"
#define XHTML_PREFIX XML_HEADER "<html><body>"
#define XHTML_SUFFIX "</body></html>"

#define VERSION_CONTENT XHTML_PREFIX "<p>API Version: <span id=\"api-ver-major\">" \
	TOSTRING(API_VERSION_MAJOR) "</span>.<span id=\"api-ver-minor\">" \
	TOSTRING(API_VERSION_MINOR) "</span>.<span id=\"api-ver-age\">" \
	TOSTRING(API_VERSION_AGE) "</span>"

#define POST_RESULT_PREFIX XHTML_PREFIX "<a id=\"new-item-link\" href=\"/todos/"
#define POST_RESULT_SUFFIX "\">New item</a>" XHTML_SUFFIX

static void ensure_redis_connection( REDIS * rhp ) {
	// Only need to run once
	if( *rhp ) return;

	// Unit tests set this variable, so that unit tests
	// can manipulate data freely without clobbering live data
	char * is_test = getenv("TODO_TESTS");
	char * host;
	int port, db_index;

	if( is_test ) {
		host = REDIS_TESTS_HOST;
		port = REDIS_TESTS_PORT;
		db_index = REDIS_TESTS_INDEX;
	} else {
		host = REDIS_HOST;
		port = REDIS_PORT;
		db_index = REDIS_INDEX;
	}

	*rhp = credis_connect( host , port , REDIS_CONNECT_TIMEOUT );
	if( !(*rhp) ) exit(EXIT_FAILURE);

	// Switch databases if not default (0) database
	if( db_index ) {
		int result = credis_select( *rhp, db_index );
		if( result == -1 ) exit( EXIT_FAILURE);
	}

}

static void ensure_redis_closed( REDIS * rhp ) {
	if( *rhp ) credis_close( *rhp );
}

static int is_slug_unique( char * test, void * context_data ) {
	// Assume here that connection was established
	REDIS rh = (REDIS)context_data;
	int result = credis_sismember( rh, "ids", test );
	return result==-1;
}

int main( int argc, char ** argv ) {

	REDIS rh = NULL;

	char * err_format = 
		"HTTP/1.1 %d %s\r\n"
		"Content-Length: 0\r\n\r\n";

	char * uri = getenv("REQUEST_URI");
	char * method = getenv("REQUEST_METHOD");

	if(!uri || !method) goto err400;
	

	// TODO: need to detect proxy use?
	// That is, can REQUEST_URI come through as
	// a full URL like http://cnn.com?  I think
	// the web server filters these automtically,
	// but it's worth testing since Apache logs
	// show a lot of these

	char * prefragment, * portion, * slug;

	// Filter fragment.  User agents not allowed to send
	// ... anyway, we'll just strip it off
	prefragment = strtok_r( uri, "#", &uri );

	// portions split before/after query string
	portion = strtok_r( prefragment, "?", &prefragment );
	if( portion ) { // means uri was non-blank

		/*
		int is_root = 1;
		while((slug = strtok_r( portion, "/", &portion ))) {
			is_root = 0;
			found_slug( slug );	
		}

		char * pair, * key, * value;
		while((pair = strtok_r( prefragment, "&", &prefragment ))) {
			key = strtok_r( pair, "=", &pair );
			value = strtok_r( pair, "=", &pair );
			found_query_pair( key, value );
		}
		*/



		int is_root = 1;
		if((slug = strtok_r( portion, "/", &portion ))) {
			is_root = 0;

			char * ok_response = 
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: application/xhtml+xml\r\n"
				"Content-Length: %d\r\n\r\n"
				"%s%s%s";

			if(!strcmp("version",slug) ) {
				if(method && !strcmp("GET",method)) {
					printf(ok_response, strlen( VERSION_CONTENT ), 
						VERSION_CONTENT, "", "");
				} else goto err405;
			} else if(!strcmp("todos",slug) ) {
				
				if((slug = strtok_r( portion, "/", &portion ))) {
					// if there are slugs following "todos"

				} else { 
					// if "todos" is final slug
					if(method && !strcmp("POST",method)) {

						// Parse content length
						char * len_str = getenv("CONTENT_LENGTH");
						if( !len_str ) goto err400;
						char * first_invalid = NULL;
						long len = strtol( len_str, &first_invalid, 10 );
						if( *first_invalid ) goto err400;

						if( len > MAX_ENTITY_LENGTH ) goto err413;

						char * content_type = getenv("CONTENT_TYPE");
						if( !content_type 
							|| strcmp(content_type,"application/x-www-form-urlencoded")) 
								goto err415;

						// Read input
						char input[ len + 1 ];
						input[ len ] = '\0';
						fread( input, 1, len, stdin );
						char * inputp = input;

						char * pair, * key, * value;
						while((pair = strtok_r( inputp, "&", &inputp ))) {
							key = strtok_r( pair, "=", &pair );
							value = strtok_r( pair, "=", &pair );

							// url-decode the data ... the new values must be freed
							key = url_decode( key );
							value = url_decode( value );
							if( !key || !value ) goto err400;

							if( !strcmp( "data", key ) ) {
								ensure_redis_connection( &rh );

								// The while loop implements optimistic concurrency
								// guarding against a case where the requested id is
								// reserved by another process after locate_unique_slug
								// and before credis_sadd
								char * id;
								while(1) {
									id = locate_unique_slug( value, &is_slug_unique, rh );
									if(credis_sadd( rh, "ids", id ) != -1) break;
								}
								
								char redis_key[ 3 + strlen(id) + 5 + 1];
								sprintf( redis_key, "id:%s:text", id );
								// TODO: this is cop-out error handling
								if( credis_set( rh, redis_key, value )) goto err500;

								int resp_len = strlen( POST_RESULT_PREFIX ) +
									strlen( id ) + strlen( POST_RESULT_SUFFIX );

								printf( ok_response, resp_len, POST_RESULT_PREFIX,
									id, POST_RESULT_SUFFIX );

								if( id ) {
									free(id);
									id = NULL;
								}

							}
							
							free( key );
							key = NULL;
							free( value );
							value = NULL;

						}
					} else if(method && !strcmp("GET",method)) {
						// Implement GET /todos collection

						size_t out_len = 16;
						char * body = malloc( out_len );
						memset( body, 0, out_len );

#define APPEND(dest,str,lenvar) \
						while( strlen(dest) + strlen( str ) > lenvar ) \
							dest = realloc( dest, (lenvar *= 2 ) ); \
						sprintf( dest+strlen(dest), "%s", str );

						APPEND( body, XHTML_PREFIX, out_len );
						APPEND( body, "<ul>", out_len );

						char ** ids = NULL;
						ensure_redis_connection( &rh );
						int count = credis_smembers( rh, "ids", &ids );

						int i;
						char * value = NULL;
						for(i=0; i<count; i++) {
							// strdup sucks here, but credis bulk calls
							// seem to be reentrant
							char * one_id = strdup(*(ids+i));

							char redis_key[ 3 + strlen(one_id) + 5 + 1];
							sprintf( redis_key, "id:%s:text", one_id );

							if( credis_get( rh, redis_key, &value ) == -1) goto err500;
							
							APPEND( body, "<li><a href=\"/todos/", out_len );
							APPEND( body, one_id, out_len );
							APPEND( body, "\">", out_len );
							APPEND( body, value, out_len );
							APPEND( body, "</a></li>", out_len );
							/*
							*/
							free( one_id );
							
						}

						APPEND( body, "</ul>", out_len );
						APPEND( body, XHTML_SUFFIX, out_len );

						printf( ok_response, strlen(body), body, "", "" );

						free( body );

					} else goto err405;

				}

			} else goto err404;
		}

		if(is_root) {
			// Handle request for root path /
		}
	}
	


	ensure_redis_closed( &rh );
	return 0;

	err400:
		ensure_redis_closed( &rh );
		printf(err_format,400,"Bad Request");
		return 1;

	err404:
		ensure_redis_closed( &rh );
		printf(err_format,404,"File Not Found");
		return 1;

	err413:
		ensure_redis_closed( &rh );
		printf(err_format,413,"Request Entity Too Large");
		return 1;

	err415:
		ensure_redis_closed( &rh );
		printf(err_format,415,"Unsupported Media Type");
		return 1;

	err405:
		ensure_redis_closed( &rh );
		printf(err_format,405,"Method Not Allowed");
		return 1;

	err500:
		ensure_redis_closed( &rh );
		printf(err_format,500,"Server Error");
		return 1;
}
