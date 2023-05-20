
THORSANVIL_ROOT				= $(shell realpath ./)

TARGET						= src

fix: fixDump all
fixDump:
	echo "THORSANVIL_ROOT: $(THORSANVIL_ROOT)"
	pwd
	$(realpath ./)
	$(realpath ../)

include $(THORSANVIL_ROOT)/build/tools/Project.Makefile




