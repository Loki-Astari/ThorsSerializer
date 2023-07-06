
THORSANVIL_ROOT				?= $(realpath ../../)
COVERAGE_REQUIRED			= 70

TARGET						= ThorSerialize.lib
NAMESPACE					= ThorsAnvil::Serialize
LINK_LIBS					= ThorsLogging
UNITTEST_LINK_LIBS			= ThorsLogging
UNITTEST_LDLIBS				= -ldl
# There is no executable code in this header. Just an enum declaration.
TEST_IGNORE					+= JsonLexemes.h

#
# Note: SERIALIZATION_EXTERN_LIBS
#▸  ▸   Is set up in the config for any external libraries that we need.
#

CXXFLAGS					+= -I$(magic_enum_ROOT_DIR)/include
CXXFLAGS					+= -DSCGRROT_SHARED_PTR_SUPPRT=1
LDLIBS_EXTERN_BUILD			+= $(yaml_ROOT_LIB)
FILE_WARNING_FLAGS			+= -Wno-unused-parameter
%/JsonLexer.lex.o:			FILE_WARNING_FLAGS	+= -Wno-sign-compare -Wno-register
%/JsonLexer1.lex.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-register
%/DeprecatedTest.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-declarations
%/PolyMorphicSerializerUniquePointerTest.o:		FILE_WARNING_FLAGS	+= -Wno-inconsistent-missing-override
%/SerArrayTest.o:			FILE_WARNING_FLAGS	+= -Wno-missing-braces
VERA_PROFILE_Traits.h		= thor_Traits.h

include $(THORSANVIL_ROOT)/build/tools/Makefile



