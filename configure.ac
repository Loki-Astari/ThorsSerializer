
AC_INIT([ThorsAnvil], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])


AC_CONFIG_MACRO_DIR([build/autotools/m4])
AX_FUNC_THORBUILD

AC_CONFIG_SRCDIR([src/Serialize/JsonParser.cpp])
AC_CONFIG_AUX_DIR([build/autotools/build])
AC_PROG_CXX
AC_PROG_LEX
LT_INIT

AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile.config])
AC_OUTPUT
