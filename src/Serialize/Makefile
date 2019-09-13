
THORSANVIL_ROOT				?= $(realpath ../../)

TARGET						= ThorSerialize.lib
# There is no executable code in this header. Just an enum declaration.
TEST_IGNORE					+= JsonLexemes.h

# There is no executable code in these files.
# All the code is in BinaryTHash.tpp that is tested thoroughly
TEST_IGNORE					+= BinaryTHash.cpp BinaryTHash.h

# This is experimental code.
# Need a better definition of what it does before we add tests
TEST_IGNORE					+= BinaryParser.cpp BinaryParser.tpp BinaryParser.h BinaryPrinter.h BinaryThor.h



#
# Note: SERIALIZATION_EXTERN_LIBS
#▸  ▸   Is set up in the config for any external libraries that we need.
#

FILE_WARNING_FLAGS			+= $(NO_DEPRECATED_REGISTER_TEST) -Wno-unknown-pragmas $(LITERAL_WARNING)
LDLIBS_EXTERN_BUILD			+= $(yaml_ROOT_LIB)
%/JsonLexer.lex.o:			FILE_WARNING_FLAGS	+= -Wno-sign-compare -Wno-register
%/JsonLexer1.lex.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-register

CXXFLAGS					+= -DHEADER_ONLY_INCLUDE=$(HEADER_ONLY_INCLUDE)

include $(THORSANVIL_ROOT)/build/tools/Makefile




