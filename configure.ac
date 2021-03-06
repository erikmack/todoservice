#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([todoservice], [0.1], [erikmack@gmail.com])
AC_CONFIG_SRCDIR([src/todoservice.c])
AC_CONFIG_HEADERS([config.h])

# Allow configuration of live Redis parameters
AC_ARG_WITH(redis-host,
	[  --with-redis-host=host  Set the hostname for the Redis database (default=localhost)], 
	[prod_redis_host=${withval}], 
	[prod_redis_host=localhost])
AC_DEFINE_UNQUOTED(REDIS_HOST,"${prod_redis_host}",
	[host for redis database, as set with --with-redis-host])
AC_ARG_WITH(redis-port,
	[  --with-redis-port=port  Set the port for the Redis database (default=6379)], 
	[prod_redis_port=${withval}], 
	[prod_redis_port=6379])
AC_DEFINE_UNQUOTED(REDIS_PORT,${prod_redis_port},
	[port for redis database, as set with --with-redis-port])
AC_ARG_WITH(redis-db-index,
	[  --with-redis-db-index=i Set the db-index for the Redis database (default=0)], 
	[prod_redis_db_index=${withval}], 
	[prod_redis_db_index=0])
AC_DEFINE_UNQUOTED(REDIS_INDEX,${prod_redis_db_index},
	[index for redis database, as set with --with-redis-db-index])

# Allow configuration of Redis parameters for unit tests
AC_ARG_WITH(redis-tests-host,
	[  --with-redis-tests-host=host  Set the hostname for the Redis database (default=localhost)], 
	[tests_redis_host=${withval}], 
	[tests_redis_host=localhost])
AC_SUBST(tests_redis_host)
AC_DEFINE_UNQUOTED(REDIS_TESTS_HOST,"${tests_redis_host}",
	[host for redis database, as set with --with-redis-tests-host])
AC_ARG_WITH(redis-tests-port,
	[  --with-redis-tests-port=port  Set the port for the Redis database (default=6379)], 
	[tests_redis_port=${withval}], 
	[tests_redis_port=6379])
AC_SUBST(tests_redis_port)
AC_DEFINE_UNQUOTED(REDIS_TESTS_PORT,${tests_redis_port},
	[port for redis database, as set with --with-redis-tests-port])
AC_ARG_WITH(redis-tests-db-index,
	[  --with-redis-tests-db-index=i Set the db-index for the Redis database (default=13)], 
	[tests_redis_db_index=${withval}], 
	[tests_redis_db_index=13])
AC_SUBST(tests_redis_db_index)
AC_DEFINE_UNQUOTED(REDIS_TESTS_INDEX,${tests_redis_db_index},
	[index for redis database, as set with --with-redis-tests-db-index])

# Set global redis connection timeout
AC_ARG_WITH(redis-connect-timeout,
	[  --with-redis-connect-timeout=i Set the connect timeout (ms) for the Redis database (default=2000)], 
	[redis_connect_timeout=${withval}], 
	[redis_connect_timeout=2000])
AC_DEFINE_UNQUOTED(REDIS_CONNECT_TIMEOUT,${redis_connect_timeout},
	[connect timeout for redis database, as set with --with-redis-connect-timeout])

# Set max (pre-decoding) content size
AC_ARG_WITH(max-entity-length,
	[  --with-max-entity-length=i Set the max (pre-URL-decoding) content length (default=1024)], 
	[max_entity_length=${withval}], 
	[max_entity_length=1024])
AC_DEFINE_UNQUOTED(MAX_ENTITY_LENGTH,${max_entity_length},
	[max (pre-URL-decoding) content length (default=1024) from --with-max-entity-length ... note that there's nothing special about the default value, but it should help a request fit nicely inside a single packet])

# add API versioning macros to config.h
AC_DEFINE(API_VERSION_MAJOR,1,[API Major version number, changes when API changes])
AC_DEFINE(API_VERSION_MINOR,0,[API Minor version number, changes when API doesn't])
AC_DEFINE(API_VERSION_AGE,0,[API age, changes when API changes in a backward-compatible way])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_CC_C_O

# Checks for libraries.
AC_CHECK_LIB([credis], [credis_save])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile
				 example/Makefile
				 example/client/Makefile
				 example/apache_vhost/Makefile
				 ])
AC_OUTPUT
