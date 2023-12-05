
export CC		:= gcc
export CFLAGS	:= -fPIC -fno-jump-tables -Wall

.PHONY: all toy md5sum clean

help:
	@echo "Usage:"
	@egrep -h '\s##\s' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m  %-16s\033[0m %s\n", $$1, $$2}'

all: toy md5sum		## Build all programs

toy:		## Build toy program
	$(MAKE) -C toy

md5sum:		## Build md5sum program
	$(MAKE) -C md5sum

clean:		## Clean up all build files
	$(MAKE) -C toy clean
	$(MAKE) -C md5sum clean