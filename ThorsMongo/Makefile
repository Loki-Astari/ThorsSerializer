THORSANVIL_ROOT             ?= $(realpath ../../)

TARGET = ThorsMongo.head

LDLIBS_EXTERN_BUILD			= MagicEnum snappy crypto ThorSerialize

UNITTEST_LDLIBS				+= $(LDLIBS_$(PLATFORM))
LDLIBS						+= $(LDLIBS_$(PLATFORM))

FILE_WARNING_FLAGS			+= -Wno-dollar-in-identifier-extension -Wno-deprecated-declarations -Wno-missing-braces

include $(THORSANVIL_ROOT)/build/tools/Makefile
