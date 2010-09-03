#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([todoservice], [0.1], [erikmack@gmail.com])
AC_CONFIG_SRCDIR([src/todoservice.c])
AC_CONFIG_HEADERS([config.h])
AC_DEFINE(API_VERSION_MAJOR,1,[API Major version number, changes when API changes])
AC_DEFINE(API_VERSION_MINOR,0,[API Minor version number, changes when API doesn't])
AC_DEFINE(API_VERSION_AGE,0,[API age, changes when API changes in a backward-compatible way])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([credis], [credis_save])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
