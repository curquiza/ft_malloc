#!/bin/bash

export DYLD_LIBRARY_PATH=`pwd`
echo "export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH"

if [ -z $HOSTTYPE ]; then
	echo "HOSTTYPE not set"
	machine=`uname -m`
	system=`uname -s`
	export DYLD_INSERT_LIBRARIES="libft_malloc_${machine}_${system}.so"
	echo "export DYLD_INSERT_LIBRARIES=$DYLD_INSERT_LIBRARIES"
else
	echo "HOSTTYPE set"
	export DYLD_INSERT_LIBRARIES="libft_malloc_$HOSTTYPE.so"
	echo "export DYLD_INSERT_LIBRARIES=$DYLD_INSERT_LIBRARIES"
fi

export DYLD_FORCE_FLAT_NAMESPACE=1
echo "export DYLD_FORCE_FLAT_NAMESPACE=$DYLD_FORCE_FLAT_NAMESPACE"
