#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "credis.h"
#include "utility.h"

#define XML_HEADER "<?xml version=\"1.0\"?>"
#define VERSION_CONTENT XML_HEADER "<version major=\"" TOSTRING(API_VERSION_MAJOR) \
	"\" minor=\"" TOSTRING(API_VERSION_MINOR) "\" age=\"" TOSTRING(API_VERSION_AGE) "\" />"	

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

int main( int argc, char ** argv ) {

	char * err_format = 
		"HTTP/1.1 %d %s\r\n"
		"Content-Length: 0\r\n\r\n";

	char * uri = getenv("REQUEST_URI");
	char * method = getenv("REQUEST_METHOD");

	if(!uri || !method) goto err400;
	
	REDIS rh = NULL;

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
			if(!strcmp("version",slug) ) {

				if(method && !strcmp("GET",method)) {
					char * response = 
						"HTTP/1.1 200 OK\r\n"
						"Content-Type: application/xhtml+xml\r\n"
						"Content-Length: %d\r\n\r\n"
						"%s";

					printf(response, strlen( VERSION_CONTENT ), VERSION_CONTENT);
				} else goto err405;
			} else if(!strcmp("todos",slug) ) {
				
				if((slug = strtok_r( portion, "/", &portion ))) {
					// if there are slugs following "todos"

				} else { 
					// if "todos" is final slug
					if(method && !strcmp("POST",method)) {

						ensure_redis_connection( &rh );

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
		printf(err_format,400,"Bad request");
		return 1;

	err404:
		printf(err_format,404,"File not found");
		return 1;

	err405:
		printf(err_format,405,"Method not allowed");
		return 1;
}
