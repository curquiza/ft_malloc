#!/bin/sh
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
# export FT_MALLOC_DEBUG=1
# export FT_MALLOC_NOCOLOR=1
# export SHOW_MEM_FREE=1
$@
