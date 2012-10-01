/*
    +----------------------------------------------------------------------+
    | PHP Version 5                                                        |
    +----------------------------------------------------------------------+
    | Copyright (c) 1997-2012 The PHP Group                                |
    +----------------------------------------------------------------------+
    | This source file is subject to version 3.01 of the PHP license,      |
    | that is bundled with this package in the file LICENSE, and is        |
    | available through the world-wide-web at the following url:           |
    | http://www.php.net/license/3_01.txt                                  |
    | If you did not receive a copy of the PHP license and are unable to   |
    | obtain it through the world-wide-web, please send a note to          |
    | license@php.net so we can mail you a copy immediately.               |
    +----------------------------------------------------------------------+
    | Authors: Will Fitch <willfitch@php.net>                              |
    |          Alexander Veremyev <cawa@csa.ru> 		                   |
    +----------------------------------------------------------------------+

    $Id$
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bitset.h"

zend_class_entry *bitset_class_entry = NULL;
static zend_object_handlers bitset_object_handlers;

static zend_object_value php_bitset_objects_new(zend_class_entry *ce TSRMLS_DC);

const zend_function_entry bitset_functions[] = {
    PHP_FE_END
};

static const zend_module_dep bitset_deps[] = {
    ZEND_MOD_END
};

zend_module_entry bitset_module_entry = {
#if ZEND_MODULE_API_NO >= 20050617
    STANDARD_MODULE_HEADER_EX, NULL,
    NULL,
#elif ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "bitset",
    bitset_functions,
    PHP_MINIT(bitset),
    PHP_MSHUTDOWN(bitset),
    NULL,
    NULL,
    PHP_MINFO(bitset),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_BITSET_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BITSET
ZEND_GET_MODULE(bitset)
#endif
/* {{{ Arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_bitset___construct, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_andop, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_andnotop, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_cardinality, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_clear, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_fill, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_fromarray, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_get, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_hashcode, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_intersects, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_isempty, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_length, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_nextclearbit, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_nextsetbit, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_orop, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_previousclearbit, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_previoussetbit, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_set, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_setrange, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_size, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_toarray, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_xorop, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset___tostring, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ proto void BitSet::__construct(int value)
   Class constructor */
PHP_METHOD(BitSet, __construct)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto void BitSet::andOp(BitSet set)
   Performs a logical AND of target bit set with provided object */
PHP_METHOD(BitSet, andOp)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto void BitSet::andNotOp(BitSet set)
   Clears all bits in this object whose bit is set in the provided object */
PHP_METHOD(BitSet, andNotOp)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::cardinality(void)
   Returns the number of true bits */
PHP_METHOD(BitSet, cardinality)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto void BitSet::clear([int indexOrFromIndex[, int toIndex]])
   Sets all bits to false */
PHP_METHOD(BitSet, clear)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool BitSet::get(int index)
   Returns the bool value of the bit at the specified index */
PHP_METHOD(BitSet, get)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::hashCode(void)
   Returns the hash code for this bit set */
PHP_METHOD(BitSet, hashCode)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool BitSet::intersects(BitSet set)
   Determines if the provided value has any bits set to true that are also true in this object */
PHP_METHOD(BitSet, intersects)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool BitSet::isEmpty(void)
   Determines if this value contains no bits */
PHP_METHOD(BitSet, isEmpty)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::length(void)
   Returns the highest set bit plus one */
PHP_METHOD(BitSet, length)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::nextClearBit(int index)
   Returns the index of the next bit after the provided index that is set to false */
PHP_METHOD(BitSet, nextClearBit)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::nextSetBit(int index)
   Returns the index of the next bit after the provided index that is set to true */
PHP_METHOD(BitSet, nextSetBit)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto void BitSet::orOp(BitSet set)
   Performs a logical OR of this object with the provided argument object */
PHP_METHOD(BitSet, orOp)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::previousClearBit(int index)
   Returns the index of the previous bit before the provided index that is set to false */
PHP_METHOD(BitSet, previousClearBit)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::previousSetBit(int index)
   Returns the index of the previous bit before the provided index that is set to true */
PHP_METHOD(BitSet, previousSetBit)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto void BitSet::set(int index, bool value)
   Sets the bit at the provided index to the specified boolean value */
PHP_METHOD(BitSet, set)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto void BitSet::setRange(int fromIndex, int toIndex, bool value)
   Sets the bits from the fromIndex to the toIndex to the specified boolean value */
PHP_METHOD(BitSet, setRange)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto int BitSet::size(void)
   Returns the number of bits of space in use */
PHP_METHOD(BitSet, size)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ */
PHP_METHOD(BitSet, fromArray)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto array BitSet::toArray(void)
   Returns bit set mapped to an array */
PHP_METHOD(BitSet, toArray)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto void BitSet::xorOp(BitSet set)
   Performs an XOR operation against the current object bit set with the specified argument */
PHP_METHOD(BitSet, xorOp)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ proto string BitSet::__toString(void)
   Returns a human-readable string representation of the bit set */
PHP_METHOD(BitSet, __toString)
{
    RETURN_FALSE;
}
/* }}} */

/* {{{ arginfo assignments */
static const zend_function_entry bitset_class_method_entry[] = {
    PHP_ME(BitSet, andOp, arginfo_bitset_andop, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, andNotOp, arginfo_bitset_andnotop, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, cardinality, arginfo_bitset_cardinality, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, clear, arginfo_bitset_clear, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, fromArray, arginfo_bitset_fromarray, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, get, arginfo_bitset_get, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, hashCode, arginfo_bitset_hashcode, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, intersects, arginfo_bitset_intersects, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, isEmpty, arginfo_bitset_isempty, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, length, arginfo_bitset_length, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, nextClearBit, arginfo_bitset_nextclearbit, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, nextSetBit, arginfo_bitset_nextsetbit, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, orOp, arginfo_bitset_orop, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, previousClearBit, arginfo_bitset_previousclearbit, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, previousSetBit, arginfo_bitset_previoussetbit, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, set, arginfo_bitset_set, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, setRange, arginfo_bitset_setrange, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, size, arginfo_bitset_size, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, toArray, arginfo_bitset_toarray, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, xorOp, arginfo_bitset_xorop, ZEND_ACC_PUBLIC)
    PHP_ME(BitSet, __toString, arginfo_bitset___tostring, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */


void bitset_objects_free_storage(void *object TSRMLS_DC)
{
    php_bitset_object *intern = (php_bitset_object *) object;
    zend_object_std_dtor(&intern->zo TSRMLS_CC);
    efree(object);
}

static zend_object_value php_bitset_objects_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_bitset_object *intern;

    intern = emalloc(sizeof(php_bitset_object));
    intern->bitset_val = 0;

    zend_object_std_init(&intern->zo, ce TSRMLS_CC);
    retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t) bitset_objects_free_storage, NULL TSRMLS_CC);
    intern->handle = retval.handle;
    retval.handlers = &bitset_object_handlers;
    return retval;
}

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(bitset)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "BitSet Support", "enabled");
	php_info_print_table_row(2, "BitSet Version", PHP_BITSET_VERSION);
	php_info_print_table_end();
	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(bitset)
{
	zend_class_entry ce;
    memcpy(&bitset_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	INIT_CLASS_ENTRY(ce, "BitSet", bitset_class_method_entry);
    ce.create_object = php_bitset_objects_new;
	bitset_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(bitset)
{
    bitset_class_entry = NULL;
    return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
