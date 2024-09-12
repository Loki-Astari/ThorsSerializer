AC_INIT([ThorsSerialize], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])

AX_THOR_FUNC_INIT_BUILD([ThorsSerializer], [src/Serialize/JsonParser.cpp], [20])

AX_THOR_ENABLE_CONAN

AX_THOR_CHECK_USE_MAGIC_ENUM
AX_THOR_CHECK_USE_YAML
AX_THOR_CHECK_USE_THORS_SERIALIZE([Serialize])

AX_THOR_FUNC_TEST_COMP([
#include <utility>
int main() {
    std::index_sequence<1,2,3,4>    seq;
}])

AC_ARG_WITH(
    [homebrewCLT],
    AS_HELP_STRING([--with-homebrewCLT=<CLT Version>], [Define what version of the CLT is being used])
)
AS_IF(
    [test "x${with_homebrewCLT}" != "x"],
    [
        AC_MSG_NOTICE([Have with_homebrewCLT in Mongo => ${with_homebrewCLT}])
        AS_IF(
            [test ${with_homebrewCLT} -lt 153],
            [
                AC_MSG_NOTICE([Setting HOMEBREW_OLD_VERSION_OF_MAC])
                AC_DEFINE([HOMEBREW_OLD_VERSION_OF_MAC], [1], [Check for older build tools and use simpler code with old tools])
                subconfigure="${subconfigure} --with-homebrewCLT=${with_homebrewCLT}"
            ]
        )
    ]
)


LT_INIT

subconfigure="${subconfigure} --with-thorserialize-root=$(pwd)/build "

AX_THOR_FEATURE_HEADER_ONLY_VARIANT([THORS_SERIALIZER])
AX_THOR_FUNC_TERM_BUILD([SERIALIZER], [src/Serialize/SerializeConfig.h:config.h.in])

AC_OUTPUT
