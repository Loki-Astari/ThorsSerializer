
THORSANVIL_ROOT				= $(realpath ../../)

TARGET						= ThorSerialize.slib

CPPFLAGS					+= -I/Users/myork/Repository/TS.old/build/include/ -Wno-shift-count-overflow
LDLIBS						+= $(patsubst %,-L%/lib,$(SERIALIZATION_EXTERN_LOC))  $(SERIALIZATION_EXTERN_LIBS)
UNITTEST_RUNTIME_PATH		+= $(patsubst %,%/lib,$(SERIALIZATION_EXTERN_LOC))
FILE_WARNING_FLAGS			+= -Wno-gnu-zero-variadic-macro-arguments
%/JsonLexer.lex.o:			FILE_WARNING_FLAGS	+= -Wno-sign-compare
%/JsonLexer1.lex.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-register

include $(THORSANVIL_ROOT)/build/tools/Makefile




