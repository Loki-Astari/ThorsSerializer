
AC_INIT([ThorsSerialize], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])


# Set up the build system
if [[ ! -e build/Notes ]]; then
    git submodule init
    git submodule update
fi
ln -s .build build | echo "Build Already Setup"
AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])
AX_THOR_FUNC_BUILD


AC_CONFIG_SRCDIR([src/Serialize/JsonParser.cpp])
AC_PROG_CXX
AX_THOR_PROG_COV

AC_SUBST([SERIALIZATION_EXTERN_LIBS], [])

AX_THOR_FUNC_USE_YAML
AX_THOR_LIB_SELECT

AC_SUBST([SERIALIZATION_EXTERN_LIBS], ["$with_yamllib  $SERIALIZATION_EXTERN_LIBS"])

AC_LANG_PUSH([C++])
AX_CHECK_COMPILE_FLAG([-ansi], [AC_SUBST([CXXFLAGS], ["$CXXFLAGS -ansi"])])
AX_CHECK_COMPILE_FLAG([-Wno-literal-suffix], [AC_SUBST([LITERAL_WARNING_SUFFIX], [-Wno-literal-suffix])], [], [$CXX_STD_FLAG -Werror -Wall -Wextra])
AX_CHECK_COMPILE_FLAG([-Wno-literal-range],  [AC_SUBST([LITERAL_WARNING_RANGE],  [-Wno-literal-range])],  [], [$CXX_STD_FLAG -Werror -Wall -Wextra])
AC_LANG_POP([C++])

AX_THOR_FUNC_LANG_FLAG(17)
AX_THOR_FUNC_TEST_COMP([
#include <utility>
int main() {
    std::index_sequence<1,2,3,4>    seq;
}])

LT_INIT

AX_THOR_CHECK_THIRD_PARTY_LIBS

AC_DEFINE([HEADER_ONLY], [0], [Enable to use header only libraries])
AC_DEFINE([HEADER_ONLY_INCLUDE], [], [For header only convery to inline])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([ src/Serialize/SerializeConfig.h ])
AC_CONFIG_FILES([Makefile.extra Makefile.config:build/autotools/build/Makefile.config.in:Makefile.config.in])
AC_OUTPUT
