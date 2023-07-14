
THORSANVIL_ROOT				?= $(realpath ../../)
COVERAGE_REQUIRED			= 70

TARGET						= ThorSerialize.lib
NAMESPACE					= ThorsAnvil::Serialize

MAGIC_ENUM_FLAGS			= $(if $(magicenum_ROOT_DIR), -I $(magicenum_ROOT_DIR)/include)
CXXFLAGS					+= $(MAGIC_ENUM_FLAGS)
CXXFLAGS					+= -DSCGRROT_SHARED_PTR_SUPPRT=1
LDLIBS_EXTERN_BUILD			+= $(yaml_ROOT_LIB)
LINK_LIBS					= ThorsLogging
UNITTEST_LINK_LIBS			= ThorsLogging
UNITTEST_LDLIBS				= -ldl

include $(THORSANVIL_ROOT)/build/tools/Makefile



