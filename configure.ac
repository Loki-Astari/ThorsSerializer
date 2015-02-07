
AC_INIT([ThorsAnvil], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

# Set up the build system
AC_CONFIG_MACRO_DIR([build/autotools/m4])
AX_FUNC_THORBUILD
AC_CONFIG_AUX_DIR([build/autotools/build])


AC_CONFIG_SRCDIR([src/Serialize/JsonParser.cpp])
AC_PROG_CXX
AC_PROG_LEX
LT_INIT

AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile.extra])
AC_OUTPUT
