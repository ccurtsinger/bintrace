ROOT = .
DIRS = src

include $(ROOT)/common.mk

test:
	@$(MAKE) -C $(TESTS_DIR) test
