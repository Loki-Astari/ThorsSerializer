
THORSANVIL_ROOT				?= $(realpath ../../)
COVERAGE_REQUIRED			= 70

TARGET						= ThorSerialize.lib
NAMESPACE					= ThorsAnvil::Serialize

CXXFLAGS					+= -DSCGRROT_SHARED_PTR_SUPPRT=1
LDLIBS_EXTERN_BUILD			+= MagicEnum yaml ThorSerialize
LINK_LIBS					= ThorsLogging
UNITTEST_LINK_LIBS			= ThorsLogging
UNITTEST_LDLIBS				= -ldl
FILE_WARNING_FLAGS			+= -Wno-type-limits -Wno-null-character

include $(THORSANVIL_ROOT)/build/tools/Makefile

%/DeprecatedTest.o:						FILE_WARNING_FLAGS += -Wno-deprecated-declarations
%/ExceptionWhilePrintingTest.o:			FILE_WARNING_FLAGS += -Wno-deprecated-declarations
%/ExceptionWhilePrintingTestString.o:	FILE_WARNING_FLAGS += -Wno-deprecated-declarations

