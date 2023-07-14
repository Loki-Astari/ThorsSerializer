AC_INIT([ThorsSerialize], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])

AX_THOR_FUNC_INIT_BUILD([ThorsSerializer], [17], [src/Serialize/JsonParser.cpp])

AX_BOOST_BASE
AX_THOR_CHECK_USE_MAGIC_ENUM
AX_THOR_CHECK_USE_YAML

AX_THOR_DISABLE_TEST_REQUIREING_LOCK_FILES

AX_THOR_FUNC_TEST_COMP([
#include <utility>
int main() {
    std::index_sequence<1,2,3,4>    seq;
}])

LT_INIT

subconfigure="${subconfigure} --with-ThorsSerializeroot=$(pwd) "
AX_THOR_FUNC_TERM_BUILD([SERIALIZER], [src/Serialize/SerializeConfig.h src/GitUtility/GitUtilityConfig.h])

AC_OUTPUT
