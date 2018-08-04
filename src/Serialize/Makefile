
THORSANVIL_ROOT				?= $(realpath ../../)

TARGET						= ThorSerialize.lib

#
# Note: SERIALIZATION_EXTERN_LIBS
#▸  ▸   Is set up in the config for any external libraries that we need.
#

FILE_WARNING_FLAGS			+= $(NO_DEPRECATED_REGISTER_TEST) -Wno-unknown-pragmas
LDLIBS_EXTERN_BUILD			+= $(yaml_ROOT_LIB)
%/JsonLexer.lex.o:			FILE_WARNING_FLAGS	+= -Wno-sign-compare -Wno-register
%/JsonLexer1.lex.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-register

include $(THORSANVIL_ROOT)/build/tools/Makefile




