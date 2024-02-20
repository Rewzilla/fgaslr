
export CC		:= gcc
export CFLAGS	:= -fPIC -fno-jump-tables -Wall -fno-stack-protector -no-pie

# Enable debug build?
CFLAGS += -DENABLE_DEBUG

# Enable call graph?
#CFLAGS += -DENABLE_GRAPH

# Enable named memory mappings?
CFLAGS += -DENABLE_NAMED_MAPPINGS

# Enable unmapping of original binary image?
CFLAGS += -DENABLE_UNMAP_IMAGE

.PHONY: all toy toy_orig md5sum md5sum_orig nc nc_orig clean

help:
	@echo "Usage:"
	@egrep -h '\s##\s' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m  %-16s\033[0m %s\n", $$1, $$2}'

all: toy toy_orig md5sum md5sum_orig nc nc_orig		## Build all programs

toy:			## Build toy program
	$(MAKE) -C toy

toy_orig:		## Build original toy program (NO FGASLR)
	$(MAKE) -C toy_orig

md5sum:			## Build md5sum program
	$(MAKE) -C md5sum

md5sum_orig:	## Build original md5sum program (NO FGASLR)
	$(MAKE) -C md5sum_orig

nc:				## Build nc program
	$(MAKE) -C nc

nc_orig:		## Build original netcat (NO FGASLR)
	$(MAKE)	-C nc_orig linux

clean:			## Clean up all build files
	$(MAKE) -C toy clean
	$(MAKE) -C toy_orig clean
	$(MAKE) -C md5sum clean
	$(MAKE) -C md5sum_orig clean
	$(MAKE)	-C nc clean
	$(MAKE) -C nc_orig clean

check:			## Run sanity checks to assist with debugging
	./src/check_missing.sh toy md5sum nc
