dnl $Id$
dnl config.m4 for extension bitset

CFLAGS="${CFLAGS} -Wall"

PHP_ARG_ENABLE(bitset, whether to enable bitset support, [  --enable-bitset           Enable bitset support])

if test "$PHP_BITSET" != "no"; then
  PHP_NEW_EXTENSION(bitset, bitset.c, $ext_shared)
fi
