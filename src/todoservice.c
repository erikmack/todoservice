#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "credis.h"
#include "utility.h"

#define XML_HEADER "<?xml version=\"1.0\"?>"
#define VERSION_CONTENT XML_HEADER "<version major=\"" TOSTRING(API_VERSION_MAJOR) \
	"\" minor=\"" TOSTRING(API_VERSION_MINOR) "\" age=\"" TOSTRING(API_VERSION_AGE) "\" />"	

int main() {

	char * err_format = 
		"HTTP/1.1 %d %s\r\n"
		"Content-Length: 0\r\n\r\n";

	char * uri = getenv("REQUEST_URI");
	char * method = getenv("REQUEST_METHOD");

	if(!uri || !method) goto err400;
	
	REDIS rh;

	rh = credis_connect("localhost", 6379, 2000);





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
			//} else if(uri && !strcmp("/version",uri) ) {
			} else goto err404;
		}

		if(is_root) {
			// Handle request for root path /
		}
	}
	



	credis_close(rh);

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
