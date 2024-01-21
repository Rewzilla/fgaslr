
export CC		:= gcc
export CFLAGS	:= -fPIC -fno-jump-tables -Wall -fno-stack-protector

.PHONY: all toy md5sum nc clean

help:
	@echo "Usage:"
	@egrep -h '\s##\s' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m  %-16s\033[0m %s\n", $$1, $$2}'

all: toy md5sum nc		## Build all programs

toy:		## Build toy program
	$(MAKE) -C toy

md5sum:		## Build md5sum program
	$(MAKE) -C md5sum

nc:			## Build nc program
	$(MAKE) -C nc

clean:		## Clean up all build files
	$(MAKE) -C toy clean
	$(MAKE) -C md5sum clean
	$(MAKE)	-C nc clean

check:		## Run sanity checks to assist with debugging
	./src/check_missing.sh toy md5sum nc
