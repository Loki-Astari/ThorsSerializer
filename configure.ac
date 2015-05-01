
AC_INIT([ThorsAnvil], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

# Set up the build system
AC_CONFIG_MACRO_DIR([build/autotools/m4])
AX_THOR_FUNC_BUILD
AC_CONFIG_AUX_DIR([build/autotools/build])


AC_CONFIG_SRCDIR([src/Serialize/JsonParser.cpp])
AC_PROG_CXX
AX_THOR_PROG_COV
AX_THOR_PROG_LEX
LT_INIT

AC_SUBST([SERIALIZATION_EXTERN_LIBS], [])
AC_SUBST([SERIALIZATION_EXTERN_LOC], [])

AX_THOR_FUNC_USE_YAML
AX_THOR_FUNC_USE_BINARY

AC_SUBST([SERIALIZATION_EXTERN_LIBS], ["$with_yamllib  $SERIALIZATION_EXTERN_LIBS"])
AC_SUBST([SERIALIZATION_EXTERN_LOC],  ["$with_yamlroot $SERIALIZATION_EXTERN_LOC"])

AX_CHECK_COMPILE_FLAG([-ansi], [AC_SUBST([CXXFLAGS], ["$CXXFLAGS -ansi"])])

AX_THOR_FUNC_LANG_FLAG(14)
AX_THOR_FUNC_TEST_COMP([
#include <utility>
int main() {
    std::index_sequence<1,2,3,4>    seq;
}])



AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([ src/Serialize/SerializeConfig.h src/BinaryRep/BinaryRepConfig.h ])
AC_CONFIG_FILES([Makefile.extra Makefile.config])
AC_OUTPUT
