ROOT = .
DIRS = 

include $(ROOT)/common.mk

docs: docs/html
	
docs/html: docs/doxyfile
	doxygen docs/doxyfile

test:
	@$(MAKE) -C $(TESTS_DIR) test
