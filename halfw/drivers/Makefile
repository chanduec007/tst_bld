.PHONY: lcov

include properties.mk 

DIRS=gpio i2c spi #add more driver directories s and when needed: kiran

ALL=$(foreach dir,$(DIRS),$(dir)-all)
CLEAN=$(foreach dir,$(DIRS),$(dir)-clean)
DISTCLEAN=$(foreach dir,$(DIRS),$(dir)-distclean)
INSTALL=$(foreach dir,$(DIRS),$(dir)-install)

install: $(ALL)
	@mkdir -p _install
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir install || exit $?; \
		cp -a $$dir/_install/* _install; \
	done
	@du -h _install --max-depth=0

all: $(ALL)

clean: $(CLEAN)

distclean: clean 
	rm -rf _install
	
include common.mk
