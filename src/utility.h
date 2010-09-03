#ifndef UTILITY_H_
#define UTILITY_H_

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

typedef int (UniqueTestFunc)( char * test, void * context_data );

char * create_unique_slug( const char * raw, 
	UniqueTestFunc * is_unique, void * context_data );

#endif // UTILITY_H_

