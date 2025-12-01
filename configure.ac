AC_INIT([ThorsSerialize], [0.1], [Loki.Astari+ThorsSerializer@gmail.com])
AC_PREREQ([2.65])

AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])

AX_THOR_FUNC_INIT_BUILD([ThorsSerializer], [src/Serialize/JsonParser.cpp], [20])

AX_THOR_ENABLE_CONAN

AX_THOR_CHECK_USE_MAGIC_ENUM
AX_THOR_CHECK_USE_YAML
AX_THOR_CHECK_USE_THORS_SERIALIZE([ThorsLogging])
AX_THOR_CHECK_FOR_DOUBLE_SCAN_SUPPORT

AX_THOR_FUNC_TEST_COMP([
#include <utility>
int main() {
    std::index_sequence<1,2,3,4>    seq;
}])


LT_INIT

subconfigure="${subconfigure} --with-thorserialize-root=$(pwd)/build "

AX_THOR_FEATURE_HEADER_ONLY_VARIANT([THORS_SERIALIZER])
AX_THOR_FUNC_TERM_BUILD([SERIALIZER], [src/Serialize/SerializeConfig.h:config.h.in])

#
# Must be done after AX_THOR_FUNC_TERM_BUILD
# This is becuase the AX_THOR_FUNC_TERM_BUILD makes sure that
# windows sym links are correctly set up.
#
cat - << 'MAKEDOC' > src/fast_float/Makefile

THORSANVIL_ROOT				?= $(realpath ../../)

TARGET						= fast_float.head
VERA                        = echo

include $(THORSANVIL_ROOT)/build/tools/Makefile

MAKEDOC


AC_OUTPUT
