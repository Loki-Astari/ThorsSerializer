
AC_INIT([ThorsSerialize], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

# Set up the build system
if [[ ! -e build/Notes ]]; then
    git submodule init
    git submodule update
fi
AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])
AX_THOR_FUNC_BUILD


AC_CONFIG_SRCDIR([src/Serialize/JsonParser.cpp])
AC_PROG_CXX
AX_THOR_PROG_COV

AC_SUBST([SERIALIZATION_EXTERN_LIBS], [])

AX_THOR_FUNC_USE_YAML
AX_THOR_FUNC_USE_BINARY
AS_IF(
      [test "x$enable_binary" != "xno"],
      [
        AC_SUBST([BINARY_REP], [BinaryRep])
      ]
)
AX_THOR_LIB_SELECT

AC_SUBST([SERIALIZATION_EXTERN_LIBS], ["$with_yamllib  $SERIALIZATION_EXTERN_LIBS"])

AX_CHECK_COMPILE_FLAG([-ansi], [AC_SUBST([CXXFLAGS], ["$CXXFLAGS -ansi"])])

AX_THOR_FUNC_LANG_FLAG(17)
AX_THOR_FUNC_TEST_COMP([
#include <utility>
int main() {
    std::index_sequence<1,2,3,4>    seq;
}])
LT_INIT

export cwd=`pwd`
pushd third/ThorsIOUtil
./configure --with-hostbuild=${cwd}/build
popd



AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([ src/Serialize/SerializeConfig.h src/BinaryRep/BinaryRepConfig.h ])
AC_CONFIG_FILES([Makefile.extra Makefile.config:build/autotools/build/Makefile.config.in:Makefile.config.in])
AC_OUTPUT
