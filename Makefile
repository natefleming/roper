DIRS = cpp
 
.PHONY: all clean clobber install 
 
all: 
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir all; \
	done

clean: 
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done

clobber: 
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir clobber; \
	done

install: 
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir install; \
	done


