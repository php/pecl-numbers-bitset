/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2005 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Alexander Veremyev <cawa@csa.ru>                             |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_BITSET_H
#define PHP_BITSET_H

extern zend_module_entry bitset_module_entry;
#define phpext_bitset_ptr &bitset_module_entry

#define PHP_BITSET_VERSION "1.0.1"


#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINFO_FUNCTION(bitset);

PHP_FUNCTION(bitset_empty);
PHP_FUNCTION(bitset_incl);
PHP_FUNCTION(bitset_excl);
PHP_FUNCTION(bitset_in);
PHP_FUNCTION(bitset_fill);
PHP_FUNCTION(bitset_intersection);
PHP_FUNCTION(bitset_union);
PHP_FUNCTION(bitset_invert);
PHP_FUNCTION(bitset_subset);
PHP_FUNCTION(bitset_equal);
PHP_FUNCTION(bitset_to_string);
PHP_FUNCTION(bitset_from_string);
PHP_FUNCTION(bitset_to_hash);
PHP_FUNCTION(bitset_from_hash);
PHP_FUNCTION(bitset_to_array);
PHP_FUNCTION(bitset_from_array);
PHP_FUNCTION(bitset_is_empty);

#endif	/* PHP_BITSET_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
