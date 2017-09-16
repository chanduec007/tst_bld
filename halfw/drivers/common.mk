.PHONY:= %-distclean %-clean %-all %-install %-uninstall

clean:
	-rm -rf target
	-rm -rf _install

uninstall:
	-rm -rf _install


target/%.o: %.c
	@[ -d target ] || mkdir -p target
	@echo "CC $*.o"
	@$(CC) $(CFLAGS) -c -o $@ $<

%: target/%.o
	@echo "LD $@"
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

target/%: %.c 
	@[ -d target ] || mkdir -p target
	@echo "LD $*"
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

#
# Directory targets
#
%-distclean:
	@echo "MAKE -C $* DISTCLEAN"
	@-$(MAKE) -C $* distclean

%-clean:
	@echo "MAKE -C $* CLEAN"
	@-$(MAKE) -C $* clean

%-all:
	@echo "MAKE -C $* ALL"
	@$(MAKE) -C $* all

%-install:
	@echo "MAKE -C $* INSTALL"
	@$(MAKE) -C $* install

%-uninstall:
	@echo "MAKE -C $* UNINSTALL"
	@$(MAKE) -C $* uninstall

