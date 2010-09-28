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

#ifndef UTILITY_H_
#define UTILITY_H_

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

char * url_decode( const char * raw );

typedef int (UniqueTestFunc)( char * test, void * context_data );

char * locate_unique_slug( const char * raw, 
	UniqueTestFunc * is_unique, void * context_data );

#endif // UTILITY_H_

