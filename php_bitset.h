/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Will Fitch <willfitch@php.net>                              |
  |          Alexander Veremyev <cawa@csa.ru>                            |
  +----------------------------------------------------------------------+

  $Id$
*/

#ifndef PHP_BITSET_H
#define PHP_BITSET_H

#define phpext_bitset_ptr &bitset_module_entry
extern zend_module_entry bitset_module_entry;

#define PHP_BITSET_VERSION "3.0.1"

#ifdef PHP_WIN32
#define PHP_BITSET_API __declspec(dllexport)
#else
#define PHP_BITSET_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define BITSET_DEFAULT_BITS 64

typedef struct {
	unsigned char *bitset_val;
	unsigned long bitset_len;
	zend_object zo;
} php_bitset_object;

PHP_MINIT_FUNCTION(bitset);
PHP_MSHUTDOWN_FUNCTION(bitset);
PHP_MINFO_FUNCTION(bitset);

static inline php_bitset_object *php_bitset_fetch_object(zend_object *obj)
{
	return (php_bitset_object *)((char *)(obj) - XtOffsetOf(php_bitset_object, zo));
}

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
