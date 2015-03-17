
THORSANVIL_ROOT				= $(realpath ../../)

TARGET						= ThorSerialize.slib

CPPFLAGS					+= -I/Users/myork/Repository/TS.old/build/include/ -Wno-shift-count-overflow
LDLIBS						+= $(patsubst %,-L%/lib,$(SERIALIZATION_EXTERN_LOC))  $(SERIALIZATION_EXTERN_LIBS)
UNITTEST_RUNTIME_PATH		+= $(patsubst %,%/lib,$(SERIALIZATION_EXTERN_LOC))
%/JsonLexer.lex.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-register

include $(THORSANVIL_ROOT)/build/tools/Makefile




