/*
	+----------------------------------------------------------------------+
	| PHP Version 5														   |
	+----------------------------------------------------------------------+
	| Copyright (c) 1997-2012 The PHP Group								   |
	+----------------------------------------------------------------------+
	| This source file is subject to version 3.01 of the PHP license,	   |
	| that is bundled with this package in the file LICENSE, and is		   |
	| available through the world-wide-web at the following url:		   |
	| http://www.php.net/license/3_01.txt								   |
	| If you did not receive a copy of the PHP license and are unable to   |
	| obtain it through the world-wide-web, please send a note to		   |
	| license@php.net so we can mail you a copy immediately.			   |
	+----------------------------------------------------------------------+
	| Authors: Will Fitch <willfitch@php.net>							   |
	|		   Alexander Veremyev <cawa@csa.ru>							   |
	+----------------------------------------------------------------------+

	$Id$
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
#include "ext/standard/info.h"
#include "php_bitset.h"
#include <limits.h>

/* For PHP < 5.3.7 */
#ifndef PHP_FE_END
#define PHP_FE_END { NULL, NULL, NULL }
#endif
#ifndef ZEND_MOD_END
#define ZEND_MOD_END { NULL, NULL, NULL }
#endif

#define BITSET_DEPRECATED_MESSAGE "The bitset_* functions are deprecated and will be removed in 3.0. Please update to the BitSet class API"

zend_class_entry *bitset_class_entry = NULL;
static zend_object_handlers bitset_object_handlers;

static zend_object_value bitset_objects_new(zend_class_entry *ce TSRMLS_DC);
static zend_object_value php_bitset_register_object(php_bitset_object *intern TSRMLS_DC);
static php_bitset_object *bitset_get_intern_object(zval *object TSRMLS_DC);
static php_bitset_object *php_bitset_objects_new(zend_class_entry *ce TSRMLS_DC);
static long bitset_get_highest_value_from_array(zval *arr TSRMLS_DC);
static void bitset_initialize_object(php_bitset_object *intern, long bits TSRMLS_DC);

/* {{{ function arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset_empty, 0, 0, 0)
	ZEND_ARG_INFO(0, bitcount)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset_incl, 0, 0, 2)
	ZEND_ARG_INFO(1, bitset)
	ZEND_ARG_INFO(0, bit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset_excl, 0, 0, 2)
	ZEND_ARG_INFO(1, bitset)
	ZEND_ARG_INFO(0, bit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_in, 0)
	ZEND_ARG_INFO(0, bitset)
	ZEND_ARG_INFO(0, bit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_fill, 0)
	ZEND_ARG_INFO(0, bitcount)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_intersection, 0)
	ZEND_ARG_INFO(0, bitset1)
	ZEND_ARG_INFO(0, bitset2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_union, 0)
	ZEND_ARG_INFO(0, bitset1)
	ZEND_ARG_INFO(0, bitset2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_invert, 0)
	ZEND_ARG_INFO(0, bitset)
	ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_subset, 0)
	ZEND_ARG_INFO(0, bitset1)
	ZEND_ARG_INFO(0, bitset2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_equal, 0)
	ZEND_ARG_INFO(0, bitset1)
	ZEND_ARG_INFO(0, bitset2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_to_string, 0)
	ZEND_ARG_INFO(0, bitset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_from_string, 0)
	ZEND_ARG_INFO(0, source_str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_to_hash, 0)
	ZEND_ARG_INFO(0, bitset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_from_hash, 0)
	ZEND_ARG_INFO(0, bit_array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_to_array, 0)
	ZEND_ARG_INFO(0, bitset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_from_array, 0)
	ZEND_ARG_INFO(0, bit_array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_is_empty, 0)
	ZEND_ARG_INFO(0, bitset)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ Arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_andop, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_andnotop, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_cardinality, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_clear, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset_fromarray, 0, 0, 1)
	ZEND_ARG_INFO(0, arr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset_fromstring, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset_fromrawvalue, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_bitset_get, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
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

ZEND_BEGIN_ARG_INFO(arginfo_bitset_size, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_toarray, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_xorop, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset___tostring, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_bitset_getrawvalue, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ bitset_functions[]
 */
const zend_function_entry bitset_functions[] = {
	PHP_FE(bitset_empty, arginfo_bitset_empty)
	PHP_FE(bitset_incl, arginfo_bitset_incl)
	PHP_FE(bitset_excl, arginfo_bitset_excl)
	PHP_FE(bitset_in, arginfo_bitset_in)
	PHP_FE(bitset_fill, arginfo_bitset_fill)
	PHP_FE(bitset_intersection, arginfo_bitset_intersection)
	PHP_FE(bitset_union, arginfo_bitset_union)
	PHP_FE(bitset_invert, arginfo_bitset_invert)
	PHP_FE(bitset_subset, arginfo_bitset_subset)
	PHP_FE(bitset_equal, arginfo_bitset_equal)
	PHP_FE(bitset_to_string, arginfo_bitset_to_string)
	PHP_FE(bitset_from_string, arginfo_bitset_from_string)
	PHP_FE(bitset_to_hash, arginfo_bitset_to_hash)
	PHP_FE(bitset_from_hash, arginfo_bitset_from_hash)
	PHP_FE(bitset_to_array, arginfo_bitset_to_array)
	PHP_FE(bitset_from_array, arginfo_bitset_from_array)
	PHP_FE(bitset_is_empty, arginfo_bitset_is_empty)
	PHP_FE_END
};
/* }}} */

/* {{{ zend_module_dep zend_module_entry ZEND_GET_MODULE
 */
static const zend_module_dep bitset_deps[] = {
	ZEND_MOD_END
};

zend_module_entry bitset_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	NULL,
	"bitset",
	bitset_functions,
	PHP_MINIT(bitset),
	PHP_MSHUTDOWN(bitset),
	NULL,
	NULL,
	PHP_MINFO(bitset),
	PHP_BITSET_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BITSET
ZEND_GET_MODULE(bitset)
#endif
/* }}} */

/* {{{ proto void BitSet::__construct(int value)
   Class constructor */
PHP_METHOD(BitSet, __construct)
{
	php_bitset_object *intern = NULL;
	long bits = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &bits) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);

	/* Default the bit count to 64 bits */
	if (bits == 0) {
		bits = BITSET_DEFAULT_BITS;
	} else if (bits < 0) {
		/* Bits can't be negative */
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"The total bits to allocate must be 0 or greater");
		return;
	}

	bitset_initialize_object(intern, bits TSRMLS_CC);

	if (bits % CHAR_BIT) {
		intern->bitset_val[intern->bitset_len - 1] >>= (CHAR_BIT - (bits % CHAR_BIT));
	}
}
/* }}} */

/* {{{ proto void BitSet::andOp(BitSet set)
   Performs a logical AND of target bit set with provided object */
PHP_METHOD(BitSet, andOp)
{
	php_bitset_object *intern, *param;
	zval *param_id;
	long bitset_len1 = 0, bitset_len2 = 0, i = 0, to_bits = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &param_id, bitset_class_entry) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	param = bitset_get_intern_object(param_id TSRMLS_CC);
	bitset_len1 = intern->bitset_len * CHAR_BIT;
	bitset_len2 = param->bitset_len * CHAR_BIT;
	to_bits = bitset_len1 > bitset_len2 ? bitset_len2 : bitset_len1;

	for (; i < to_bits; i++) {
		intern->bitset_val[i / CHAR_BIT] &= param->bitset_val[i / CHAR_BIT];
	}
}
/* }}} */

/* {{{ proto void BitSet::andNotOp(BitSet set)
   Clears all bits in this object whose bit is set in the provided object */
PHP_METHOD(BitSet, andNotOp)
{
	php_bitset_object *intern, *param;
	zval *param_id;
	long bitset_len1 = 0, bitset_len2 = 0, i = 0, to_bits = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &param_id, bitset_class_entry) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	param = bitset_get_intern_object(param_id TSRMLS_CC);
	bitset_len1 = intern->bitset_len * CHAR_BIT;
	bitset_len2 = param->bitset_len * CHAR_BIT;
	to_bits = bitset_len1 > bitset_len2 ? bitset_len2 : bitset_len1;

	for (; i < to_bits; i++) {
		/* If the incoming bit is set, clear on this object */
		if (param->bitset_val[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) {
			intern->bitset_val[i / CHAR_BIT] &= ~(1 << (i % CHAR_BIT));
		}
	}
}
/* }}} */

/* {{{ proto int BitSet::cardinality(void)
   Returns the number of true bits */
PHP_METHOD(BitSet, cardinality)
{
	php_bitset_object *intern;
	long i = 0, total_bits = 0, true_bits = 0;

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);

	total_bits = intern->bitset_len * CHAR_BIT;

	for (; i < total_bits; i++) {
		if (intern->bitset_val[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) {
			true_bits++;
		}
	}

	RETURN_LONG(true_bits);
}
/* }}} */

/* {{{ proto void BitSet::clear([int indexOrFromIndex[, int toIndex]])
   Sets all bits to false */
PHP_METHOD(BitSet, clear)
{
	php_bitset_object *intern;
	long index_from = 0, index_to = 0, usable_index = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|ll", &index_from, &index_to) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);

	/* Verify the start index is not greater than total bits */
	if (index_from > intern->bitset_len * CHAR_BIT) {
		zend_throw_exception_ex(spl_ce_OutOfRangeException, 0 TSRMLS_CC,
								"The requested start index is greater than the total number of bits");
		return;
	}

	/* Clear all bits and reset */
	if (index_from == 0 && index_to == 0) {
		memset(intern->bitset_val, 0, intern->bitset_len);
		intern->bitset_val[intern->bitset_len] = '\0';
	} else {
		if (index_to == 0) {
			usable_index = index_from;
		} else {
			usable_index = index_to > intern->bitset_len * CHAR_BIT ? intern->bitset_len * CHAR_BIT : index_to;
		}

		for (; index_from <= usable_index; index_from++) {
			intern->bitset_val[index_from / CHAR_BIT] &= ~(1 << (index_from % CHAR_BIT));
		}
	}
}
/* }}} */

/* {{{ proto bool BitSet::get(int index)
   Returns the bool value of the bit at the specified index */
PHP_METHOD(BitSet, get)
{
	php_bitset_object *intern;
	long bit;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &bit) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);

	/* The bit requested is larger than all bits in this set */
	if (bit > intern->bitset_len * CHAR_BIT) {
		zend_throw_exception_ex(spl_ce_OutOfRangeException, 0 TSRMLS_CC,
								"The specified index parameter exceeds the total number of bits available");
		return;
	}

	if (intern->bitset_val[bit / CHAR_BIT] & (1 << (bit % CHAR_BIT))) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto string BitSet::getRawValue(void)
 */
PHP_METHOD(BitSet, getRawValue)
{
	php_bitset_object *intern;

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);

	if (intern->bitset_val) {
		RETURN_STRINGL((char *) intern->bitset_val, intern->bitset_len, 1);
	} else {
		RETURN_EMPTY_STRING();
	}
}
/* }}} */

/* {{{ proto string BitSet::fromRawValue(void)
 */
PHP_METHOD(BitSet, fromRawValue)
{
	php_bitset_object *newobj;
	zend_class_entry *ce = bitset_class_entry;
	char *str = NULL;
	int string_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &string_len) == FAILURE) {
		return;
	}

	newobj = php_bitset_objects_new(ce TSRMLS_CC);
	return_value->type = IS_OBJECT;

	if (string_len == 0) {
		bitset_initialize_object(newobj, BITSET_DEFAULT_BITS TSRMLS_CC);
		return_value->value.obj = php_bitset_register_object(newobj TSRMLS_CC);
		return;
	}

	bitset_initialize_object(newobj, (string_len * CHAR_BIT) TSRMLS_CC);
	memcpy(newobj->bitset_val, str, strlen(str));
	
	return_value->value.obj = php_bitset_register_object(newobj TSRMLS_CC);
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
	php_bitset_object *intern;
	long total_bits = 0, i = 0;
	short has_true_bits = 0;

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	total_bits = intern->bitset_len * CHAR_BIT;

	/* Loop through all bits and determine if there is a true bit. */
	for (; i < total_bits; i++) {
		if (intern->bitset_val[i / CHAR_BIT] & (1 << i % CHAR_BIT)) {
			has_true_bits = 1;
			break;
		}
	}

	if (has_true_bits) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}
/* }}} */

/* {{{ proto int BitSet::length(void)
   Returns the highest set bit plus one
 */
PHP_METHOD(BitSet, length)
{
	php_bitset_object *intern;
	long highest_bit = -1, i = 0;

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	i = intern->bitset_len * CHAR_BIT;

	while (i > 0) {
		i--;

		if (intern->bitset_val[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) {
			highest_bit = i;
			break;
		}
	}

	RETURN_LONG(highest_bit + 1);
}
/* }}} */

/* {{{ proto int BitSet::nextClearBit(int index)
   Returns the index of the next bit after the provided index that is set to false */
PHP_METHOD(BitSet, nextClearBit)
{
	php_bitset_object *intern;
	long start_bit = 0, bit_diff = 0, next_bit = 0;
	short found = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &start_bit) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	bit_diff = intern->bitset_len * CHAR_BIT;

	if (start_bit >= bit_diff) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"There are no bits larger than the index provided");
		return;
	}

	start_bit++;

	while (start_bit <= bit_diff) {
		if (!(intern->bitset_val[start_bit / CHAR_BIT] & (1 << (start_bit % CHAR_BIT)))) {
			next_bit = start_bit;
			found = 1;
			break;
		}

		start_bit++;
	}

	if (found) {
		RETURN_LONG(next_bit);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto int BitSet::nextSetBit(int index)
   Returns the index of the next bit after the provided index that is set to true */
PHP_METHOD(BitSet, nextSetBit)
{
	php_bitset_object *intern;
	long start_bit = 0, bit_diff = 0, next_bit = 0;
	short found = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &start_bit) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	bit_diff = intern->bitset_len * CHAR_BIT;

	if (start_bit >= bit_diff) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"There are no bits larger than the index provided");
		return;
	}

	start_bit++;

	while (start_bit <= bit_diff) {
		if (intern->bitset_val[start_bit / CHAR_BIT] & (1 << (start_bit % CHAR_BIT))) {
			next_bit = start_bit;
			found = 1;
			break;
		}

		start_bit++;
	}

	if (found) {
		RETURN_LONG(next_bit);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto void BitSet::orOp(BitSet set)
   Performs a logical OR of this object with the provided argument object */
PHP_METHOD(BitSet, orOp)
{
	php_bitset_object *intern, *param;
	zval *param_id;
	long bitset_len1 = 0, bitset_len2 = 0, i = 0, to_bits = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &param_id, bitset_class_entry) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	param = bitset_get_intern_object(param_id TSRMLS_CC);
	bitset_len1 = intern->bitset_len * CHAR_BIT;
	bitset_len2 = param->bitset_len * CHAR_BIT;
	to_bits = bitset_len1 > bitset_len2 ? bitset_len2 : bitset_len1;

	for (; i < to_bits; i++) {
		intern->bitset_val[i / CHAR_BIT] |= (param->bitset_val[i / CHAR_BIT] & (1 << (i % CHAR_BIT)));
	}
}
/* }}} */

/* {{{ proto int BitSet::previousClearBit(int index)
   Returns the index of the previous bit before the provided index that is set to false */
PHP_METHOD(BitSet, previousClearBit)
{
	php_bitset_object *intern;
	long start_bit = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &start_bit) == FAILURE) {
		return;
	}

	if (start_bit < 1) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"There are no bits smaller than the index provided (zero)");
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	start_bit--;

	while (start_bit >= 0) {
		if (!(intern->bitset_val[start_bit / CHAR_BIT] &  (1 << (start_bit % CHAR_BIT)))) {
			break;
		}

		start_bit--;
	}

	if (start_bit < 0) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(start_bit);
	}
}
/* }}} */

/* {{{ proto int BitSet::previousSetBit(int index)
   Returns the index of the previous bit before the provided index that is set to true */
PHP_METHOD(BitSet, previousSetBit)
{
	php_bitset_object *intern;
	long start_bit = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &start_bit) == FAILURE) {
		return;
	}

	if (start_bit < 1) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"There are no bits smaller than the index provided (zero)");
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	start_bit--;

	while (start_bit >= 0) {
		if (intern->bitset_val[start_bit / CHAR_BIT] & (1 << (start_bit % CHAR_BIT))) {
			break;
		}

		start_bit--;
	}

	if (start_bit < 0) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(start_bit);
	}
}
/* }}} */

/* {{{ proto void BitSet::set([int indexOrFromIndex[, toIndex]])
   Sets the bits from the specified index or range to true
 */
PHP_METHOD(BitSet, set)
{
	php_bitset_object *intern;
	long index_from = -1, index_to = 0, usable_index = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|ll", &index_from, &index_to) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);

	/* Set all bits */
	if (index_from == -1 && index_to == 0) {
		for (; usable_index < intern->bitset_len * CHAR_BIT; usable_index++)
		{
			intern->bitset_val[usable_index / CHAR_BIT] |= (1 << (usable_index % CHAR_BIT));
		}

		intern->bitset_val[intern->bitset_len] = '\0';
	} else {
		/* Verify the start index is not greater than total bits */
		if (index_from > (intern->bitset_len * CHAR_BIT - 1)) {
			zend_throw_exception_ex(spl_ce_OutOfRangeException, 0 TSRMLS_CC,
									"The requested start index is greater than the total number of bits");
			return;
		}

		if (index_to == 0) {
			usable_index = index_from;
		} else {
			usable_index = index_to > intern->bitset_len * CHAR_BIT ? intern->bitset_len * CHAR_BIT : index_to;
		}

		for (; index_from <= usable_index; index_from++) {
			intern->bitset_val[index_from / CHAR_BIT] |= (1 << (index_from % CHAR_BIT));
		}
	}
}
/* }}} */

/* {{{ proto int BitSet::size(void)
   Returns the number of bits of space in use */
PHP_METHOD(BitSet, size)
{
	php_bitset_object *intern;
	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	RETURN_LONG(intern->bitset_len * CHAR_BIT);
}
/* }}} */

/* {{{ proto BitSet BitSet::fromString(string)
 * Returns a new instance of BitSet based on the provided string
 */
PHP_METHOD(BitSet, fromString)
{
	php_bitset_object *newobj;
	zend_class_entry *ce = bitset_class_entry;
	char *str = NULL;
	int string_len = 0, i = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &string_len) == FAILURE) {
		return;
	}

	newobj = php_bitset_objects_new(ce TSRMLS_CC);
	return_value->type = IS_OBJECT;

	if (string_len == 0) {
		bitset_initialize_object(newobj, BITSET_DEFAULT_BITS TSRMLS_CC);
		return_value->value.obj = php_bitset_register_object(newobj TSRMLS_CC);
		return;
	}

	bitset_initialize_object(newobj, string_len TSRMLS_CC);

	for (; i < string_len; i++) {
		/* If the char is explicitly '1', set it as 1. Otherwise, it's 0 */
		if (str[i] == '1') {
			newobj->bitset_val[i / CHAR_BIT] |= (1 << (i % CHAR_BIT));
		}
	}

	return_value->value.obj = php_bitset_register_object(newobj TSRMLS_CC);
}
/* }}} */

/* {{{ proto BitSet BitSet::fromArray(array inputArray)
 * Returns a new Bitset instance based on the input array. All positive integers
 * within the array values are considered positions of set bits
 */
PHP_METHOD(BitSet, fromArray)
{
	php_bitset_object *newobj;
	zval *bit_array;
	zval **entry;
	zend_class_entry *ce = bitset_class_entry;
	long array_len = 0, highest_value = 0, entry_actual = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &bit_array) == FAILURE) {
		return;
	}

	array_len = zend_hash_num_elements(Z_ARRVAL_P(bit_array));
	newobj = php_bitset_objects_new(ce TSRMLS_CC);
	return_value->type = IS_OBJECT;

	if (array_len == 0) {
		bitset_initialize_object(newobj, BITSET_DEFAULT_BITS TSRMLS_CC);
		return_value->value.obj = php_bitset_register_object(newobj TSRMLS_CC);
		return;
	}

	highest_value = bitset_get_highest_value_from_array(bit_array TSRMLS_CC);
	bitset_initialize_object(newobj, highest_value TSRMLS_CC);
	zend_hash_internal_pointer_reset(Z_ARRVAL_P(bit_array));

	while (zend_hash_get_current_data(Z_ARRVAL_P(bit_array), (void **) &entry) == SUCCESS) {
		if (Z_TYPE_PP(entry) != IS_LONG) {
			SEPARATE_ZVAL(entry);
			convert_to_long(*entry);
		}

		if (Z_LVAL_PP(entry) > 0) {
			entry_actual = Z_LVAL_PP(entry) / CHAR_BIT;
			newobj->bitset_val[entry_actual] |= (1 << (Z_LVAL_PP(entry) % CHAR_BIT));
		}

		zend_hash_move_forward(Z_ARRVAL_P(bit_array));
	}

	return_value->value.obj = php_bitset_register_object(newobj TSRMLS_CC);
}
/* }}} */

/* {{{ proto array BitSet::toArray(void)
   Returns the on bits as an array */
PHP_METHOD(BitSet, toArray)
{
	php_bitset_object *intern;
	long i = 0, total_bits = 0;

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	array_init(return_value);
	total_bits = intern->bitset_len * CHAR_BIT;

	for (; i < total_bits; i++) {
		if (intern->bitset_val[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) {
			add_next_index_long(return_value, i);
		}
	}
}
/* }}} */

/* {{{ proto void BitSet::xorOp(BitSet set)
   Performs an XOR operation against the current object bit set with the specified argument */
PHP_METHOD(BitSet, xorOp)
{
	php_bitset_object *intern, *param;
	zval *param_id;
	long bitset_len1 = 0, bitset_len2 = 0, i = 0, to_bits = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &param_id, bitset_class_entry) == FAILURE) {
		return;
	}

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);
	param = bitset_get_intern_object(param_id TSRMLS_CC);
	bitset_len1 = intern->bitset_len * CHAR_BIT;
	bitset_len2 = param->bitset_len * CHAR_BIT;
	to_bits = bitset_len1 > bitset_len2 ? bitset_len2 : bitset_len1;

	for (; i < to_bits; i++) {
		intern->bitset_val[i / CHAR_BIT] ^= (param->bitset_val[i / CHAR_BIT] & (1 << (i % CHAR_BIT)));
	}
}
/* }}} */

/* {{{ proto string BitSet::__toString(void)
   Returns a human-readable string representation of the bit set */
PHP_METHOD(BitSet, __toString)
{
	php_bitset_object *intern = NULL;
	unsigned char *retval = NULL;
	long len, i;

	intern = bitset_get_intern_object(getThis() TSRMLS_CC);

	if (intern->bitset_len == 0) {
		RETURN_EMPTY_STRING();
	} else {
		len = intern->bitset_len * CHAR_BIT;
		retval = (unsigned char *) emalloc(len + 1);
		retval[len] = '\0';

		for (i = 0; i < len; i++) {
			retval[i] = ((intern->bitset_val[i / CHAR_BIT] >> (i % CHAR_BIT)) & 1) ? '1' : '0';
		}

		RETURN_STRINGL((char *)retval, len, 0);
	}
}
/* }}} */

/* {{{ assignments */
static const zend_function_entry bitset_class_method_entry[] = {
	PHP_ME(BitSet, __construct, arginfo_bitset___construct, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, andOp, arginfo_bitset_andop, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, andNotOp, arginfo_bitset_andnotop, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, cardinality, arginfo_bitset_cardinality, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, clear, arginfo_bitset_clear, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, fromArray, arginfo_bitset_fromarray, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(BitSet, fromString, arginfo_bitset_fromstring, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(BitSet, fromRawValue, arginfo_bitset_fromrawvalue, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(BitSet, get, arginfo_bitset_get, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, getRawValue, arginfo_bitset_getrawvalue, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, intersects, arginfo_bitset_intersects, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, isEmpty, arginfo_bitset_isempty, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, length, arginfo_bitset_length, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, nextClearBit, arginfo_bitset_nextclearbit, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, nextSetBit, arginfo_bitset_nextsetbit, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, orOp, arginfo_bitset_orop, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, previousClearBit, arginfo_bitset_previousclearbit, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, previousSetBit, arginfo_bitset_previoussetbit, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, set, arginfo_bitset_set, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, size, arginfo_bitset_size, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, toArray, arginfo_bitset_toarray, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, xorOp, arginfo_bitset_xorop, ZEND_ACC_PUBLIC)
	PHP_ME(BitSet, __toString, arginfo_bitset___tostring, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ php_bitset_object *bitset_get_intern_object
 */
static php_bitset_object *bitset_get_intern_object(zval *object TSRMLS_DC)
{
	php_bitset_object *intern;
	intern = (php_bitset_object *) zend_object_store_get_object(object TSRMLS_CC);
	return intern;
}
/* }}} */

/* {{{ void bitset_objects_free_storage
 */
static void bitset_objects_free_storage(void *object TSRMLS_DC)
{
	php_bitset_object *intern = (php_bitset_object *) object;
	zend_object_std_dtor(&intern->zo TSRMLS_CC);

	if (intern->bitset_val) {
		efree(intern->bitset_val);
	}

	efree(object);
}
/* }}} */

/* {{{ long bitset_get_highest_value_from_array
 */
static long bitset_get_highest_value_from_array(zval *arr TSRMLS_DC)
{
	zval **entry;
	long highest_value = 0;

	zend_hash_internal_pointer_reset(Z_ARRVAL_P(arr));

	while (zend_hash_get_current_data(Z_ARRVAL_P(arr), (void **) &entry) == SUCCESS) {
		if (Z_TYPE_PP(entry) != IS_LONG) {
			SEPARATE_ZVAL(entry);
			convert_to_long_ex(entry);
		}

		if (Z_LVAL_PP(entry) > highest_value) {
			highest_value = Z_LVAL_PP(entry);
		}

		zend_hash_move_forward(Z_ARRVAL_P(arr));
	}

	return highest_value;
}
/* }}} */

/* {{{ php_bitset_object php_bitset_objects_new
 */
static php_bitset_object *php_bitset_objects_new(zend_class_entry *ce TSRMLS_DC)
{
	php_bitset_object *intern;

	intern = emalloc(sizeof(php_bitset_object));
	memset(&intern->zo, 0, sizeof(zend_object));
	intern->bitset_val = 0;

	zend_object_std_init(&intern->zo, ce TSRMLS_CC);
#if PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 4
	{
	zval *tmp;

	zend_hash_copy(intern->zo.properties, &ce->default_properties,
	    (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));
	}
#else
	object_properties_init(&intern->zo, ce);
#endif

	return intern;
}
/* }}} */

/* {{{ zend_object_value bitset_objects_new
 */
static zend_object_value bitset_objects_new(zend_class_entry *ce TSRMLS_DC)
{
	php_bitset_object *intern;

	intern = php_bitset_objects_new(ce TSRMLS_CC);
	return php_bitset_register_object(intern TSRMLS_CC);
}
/* }}} */

/* {{{ zend_object_value php_bitset_register_object
 */
static zend_object_value php_bitset_register_object(php_bitset_object *intern TSRMLS_DC)
{
	zend_object_value retval;
	retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t) zend_objects_destroy_object,  bitset_objects_free_storage, NULL TSRMLS_CC);
	intern->handle = retval.handle;
	retval.handlers = &bitset_object_handlers;
	return retval;
}
/* }}} */

/* {{{ void bitset_initialize_object */
static void bitset_initialize_object(php_bitset_object *intern, long bits TSRMLS_DC)
{
	intern->bitset_len = (bits + CHAR_BIT - 1) / CHAR_BIT;
	intern->bitset_val = (unsigned char *) emalloc(intern->bitset_len + 1);
	memset(intern->bitset_val, 0, intern->bitset_len);
	intern->bitset_val[intern->bitset_len] = '\0';
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(bitset)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "BitSet Support", "enabled");
	php_info_print_table_row(2, "BitSet Version", PHP_BITSET_VERSION);
	php_info_print_table_row(2, "64-bit Integer Support", sizeof(unsigned long long) == 8 ? "yes" : "no");
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
	ce.create_object = bitset_objects_new;
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

/* {{{ proto string bitset_empty(integer bitcount)
   Return an empty bitset represented in a binary string. Optional parameter bitcount preallocates memory for bitset */
PHP_FUNCTION(bitset_empty)
{
	int len;
	long bits = 0;
	unsigned char *bitset_data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &bits) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (bits < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "First argument must be a positive integer");
		return;
	}

	if (bits == 0) {
		RETURN_EMPTY_STRING();
	} else {
		len = (bits+CHAR_BIT-1)/CHAR_BIT;
		bitset_data = emalloc(len+1);
		memset(bitset_data, 0, len+1);

		RETURN_STRINGL((char *)bitset_data, len, 0);
	}
}
/* }}} */

/* {{{ proto void bitset_incl(string bitset, integer bit)
   Includes bit into bitset */
PHP_FUNCTION(bitset_incl)
{
	zval *param;
	long bit;
	unsigned char *bitset_data;
	long old_len, new_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &param, &bit) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (bit < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Second argument must be a positive integer");
		return;
	}

	if (Z_TYPE_P(param) == IS_STRING) {
		bitset_data = (unsigned char *) Z_STRVAL_P(param);

		if (bit >= (Z_STRLEN_P(param))*CHAR_BIT) {
			old_len = Z_STRLEN_P(param);
			new_len = (old_len*2*CHAR_BIT > bit) ? old_len*2 : bit/CHAR_BIT + 1;

			if (old_len) {
				bitset_data = (unsigned char *) erealloc(bitset_data, new_len+1);
				Z_STRVAL_P(param) = (char *) bitset_data;
				Z_STRLEN_P(param) = new_len;

				memset(bitset_data + old_len, 0, new_len - old_len + 1);
			} else {
				zval_dtor(param);
				bitset_data = emalloc(new_len+1) ;
				memset(bitset_data, 0, new_len+1);

				ZVAL_STRINGL(param, (char *) bitset_data, new_len, 0);
			}
		}
		bitset_data[bit/CHAR_BIT]  |=  1 << (bit % CHAR_BIT);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "First argument is not a bitset");
	}
}
/* }}} */

/* {{{ proto void bitset_excl(string bitset, integer bit)
   Excludes bit into bitset */
PHP_FUNCTION(bitset_excl)
{
	zval *param;
	long bit;
	unsigned char *bitset_data;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &param, &bit) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (bit < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Second argument must be a positive integer");
		return;
	}

	if (Z_TYPE_P(param) == IS_STRING) {
		bitset_data = (unsigned char *) Z_STRVAL_P(param);

		if (bit < Z_STRLEN_P(param)*CHAR_BIT) {
			bitset_data[bit/CHAR_BIT]  &=  ~(1 << (bit % CHAR_BIT));
		}
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "First argument is not a bitset");
	}
}
/* }}} */

/* {{{ proto bool bitset_in(string bitset, integer bit)
   Checks if bit in bitset */
PHP_FUNCTION(bitset_in)
{
	int len;
	long bit;
	unsigned char *bitset_data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &bitset_data, &len, &bit) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (bit < 0) {
		RETURN_FALSE;  /*  All bits with a negative index should be treated as 0 */
	}

	if (len == 0) {
		RETURN_FALSE;
	} else if (bit >= len*CHAR_BIT) {
		RETURN_FALSE;
	} else if (bitset_data[bit/CHAR_BIT] & (1 << (bit % CHAR_BIT))) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto string bitset_fill(integer bitcount)
   Return a bitset represented in a binary string. Bitcount sets first bitcount bits */
PHP_FUNCTION(bitset_fill)
{
	long len, bits;
	unsigned char *bitset_data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &bits) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (bits < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "First argument must be a positive integer");
		RETURN_EMPTY_STRING();
	} else if (bits == 0) {
		RETURN_EMPTY_STRING();
	} else {
		len = (bits+CHAR_BIT-1)/CHAR_BIT;
		bitset_data = emalloc(len+1);
		memset(bitset_data, ~0, len);
		bitset_data[len] = '\0';
		if (bits % CHAR_BIT) {
			bitset_data[len-1] >>= (CHAR_BIT - (bits % CHAR_BIT));
		}

		RETURN_STRINGL((char *) bitset_data, len, 0);
	}
}
/* }}} */

/* {{{ proto string bitset_intersection(string bitset1, string bitset2)
   Return an intersection of two bitsets */
PHP_FUNCTION(bitset_intersection)
{
	int len1, len2, len;
	unsigned char *bitset_data1, *bitset_data2, *bitset_datares;
	long count;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
							  "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (len1 == 0 || len2 == 0) {
		RETURN_EMPTY_STRING();
	} else {
		len = (len1 < len2) ? len1 : len2;
		bitset_datares = emalloc(len+1);
		bitset_datares[len] = '\0';

		for (count = 0; count < len/(short)sizeof(unsigned long); count++) {
			((unsigned long *)bitset_datares)[count] =
				((unsigned long *)bitset_data1)[count] & ((unsigned long *)bitset_data2)[count];
		}

		for (count = len - len % sizeof(unsigned long); count < len; count++) {
			bitset_datares[count] = bitset_data1[count] & bitset_data2[count];
		}

		RETURN_STRINGL((char *) bitset_datares, len, 0);
	}
}
/* }}} */

/* {{{ proto string bitset_union(string bitset1, string bitset2)
   Return an union of two bitsets */
PHP_FUNCTION(bitset_union)
{
	int len1, len2, len, union_len;
	unsigned char *bitset_data1, *bitset_data2, *bitset_datares;
	long count;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
							  "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (len1 == 0 && len2 == 0) {
		RETURN_EMPTY_STRING();
	} else {
		if (len1 == len2) {
			union_len = len = len1;
			bitset_datares = emalloc(len+1);
		} else if (len1 > len2) {
			len = len1;
			union_len = len2;

			bitset_datares = emalloc(len+1);
			memcpy(bitset_datares + union_len, bitset_data1 + union_len, len1-len2);
		} else {
			len = len2;
			union_len = len1;

			bitset_datares = emalloc(len+1);
			memcpy(bitset_datares + union_len, bitset_data2 + union_len, len2-len1);
		}
		bitset_datares[len] = '\0';

		for (count = 0; count < union_len/(short)sizeof(unsigned long); count++) {
			((unsigned long *)bitset_datares)[count] =
				((unsigned long *)bitset_data1)[count] | ((unsigned long *)bitset_data2)[count];
		}

		for (count = union_len - union_len % sizeof(unsigned long); count < union_len; count++) {
			bitset_datares[count] = bitset_data1[count] | bitset_data2[count];
		}

		RETURN_STRINGL((char *) bitset_datares, len, 0);
	}
}
/* }}} */

/* {{{ proto void bitset_invert(string bitset, integer size)
   Invert bitset */
PHP_FUNCTION(bitset_invert)
{
	long size;
	unsigned char *bitset_data, *bitset_out;
	long invert_count, count;
	int src_len, new_len;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &bitset_data, &src_len, &size) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (size < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "First argument must be a positive integer");
		RETURN_EMPTY_STRING();
	} else if (size == 0) {
		RETURN_EMPTY_STRING();
	} else {
		new_len = (size + CHAR_BIT-1)/CHAR_BIT;
		bitset_out = emalloc(new_len+1);
		bitset_out[new_len] = '\0';

		if (new_len > src_len) {
			memset(bitset_out + src_len, ~0, new_len - src_len);
			invert_count = src_len;
		} else {
			invert_count = new_len;
		}

		for (count = 0; count < invert_count/(short)sizeof(unsigned long); count++) {
			((unsigned long *)bitset_out)[count] = ~((unsigned long *)bitset_data)[count];
		}

		for (count = invert_count - invert_count % sizeof(unsigned long); count < invert_count; count++) {
			bitset_out[count] = ~bitset_data[count];
		}

		if (size % CHAR_BIT) {   /* We should clear last bits */
			bitset_out[new_len-1] &= (0xFF >> (CHAR_BIT - size % CHAR_BIT));
		}

		RETURN_STRINGL((char *) bitset_out, new_len, 0);
	}
}
/* }}} */

/* {{{ proto bool bitset_subset(string bitset1, string bitset2)
   Return TRUE if bitset2 is a subset of bitset1 */
PHP_FUNCTION(bitset_subset)
{
	int len1, len2;
	unsigned char *bitset_data1, *bitset_data2, *rest;
	long count, compare_len, zero_count;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
							  "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (len1 >= len2) { /* We should ot care about the rest of bitset1 */
		rest		= NULL;
		zero_count  = 0;
		compare_len = len2;
	} else if (len1 < len2) { /* We should check, that the rest of bitset2 is empty */

		/* first step up to the "long" boundary  should be done here */
		for (count=len1; (count % sizeof(unsigned long)) && (count < len2); count++)
			if (bitset_data2[count])
				RETURN_FALSE;

		rest = bitset_data2 + count;
		zero_count = len2 - count;

		compare_len = len1;
	}

	for (count = 0; count < compare_len/(short)sizeof(unsigned long); count++) {
		if (((unsigned long *)bitset_data2)[count] !=
				(((unsigned long *)bitset_data2)[count] &
				 ((unsigned long *)bitset_data1)[count])) {
			RETURN_FALSE;
		}
	}

	for (count = compare_len - compare_len % sizeof(unsigned long); count < compare_len; count++) {
		if (bitset_data2[count] !=  (bitset_data2[count] & bitset_data1[count])) {
			RETURN_FALSE;
		}
	}

	for (count = 0; count < zero_count/(short)sizeof(unsigned long); count++) {
		if (((unsigned long *)rest)[count]) {
			RETURN_FALSE;
		}
	}

	for (count = zero_count - zero_count % sizeof(unsigned long); count < zero_count; count++) {
		if (rest[count]) {
			RETURN_FALSE;
		}
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool bitset_equal(string bitset1, string bitset2)
   Return TRUE if bitset1 and bitset2 are equal. Please note that "01001110" and "0100111000000000" are equal */
PHP_FUNCTION(bitset_equal)
{
	int len1, len2;
	unsigned char *bitset_data1, *bitset_data2, *rest;
	long count, compare_len, zero_count;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
							  "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (len1 == len2) { /* We should ot care about the rest of bitset1 */
		rest		= NULL;
		zero_count  = 0;
		compare_len = len2;
	} else if (len1 < len2) { /* We should check, that the rest of bitset2 is empty */

		/* first step up to the "long" boundary  should be done here */
		for (count=len1; (count % sizeof(unsigned long)) && (count < len2); count++) {
			if (bitset_data2[count]) {
				RETURN_FALSE;
			}
		}

		rest = bitset_data2 + count;
		zero_count = len2 - count;

		compare_len = len1;
	} else { /* len1 > len2 */
		/* We should check, that the rest of bitset1 is empty */

		/* first step up to the "long" boundary  should be done here */
		for (count=len2; (count % sizeof(unsigned long)) && (count < len1); count++) {
			if (bitset_data1[count]) {
				RETURN_FALSE;
			}
		}

		rest = bitset_data1 + count;
		zero_count = len1 - count;

		compare_len = len2;
	}

	if (memcmp(bitset_data1, bitset_data2, compare_len) != 0) {
		RETURN_FALSE;
	}

	for (count = 0; count < zero_count/(short)sizeof(unsigned long); count++) {
		if (((unsigned long *)rest)[count]) {
			RETURN_FALSE;
		}
	}

	for (count = zero_count - zero_count % sizeof(unsigned long); count < zero_count; count++) {
		if (rest[count]) {
			RETURN_FALSE;
		}
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string bitset_to_string(string bitset)
   Return a human readable string representation of a bitset */
PHP_FUNCTION(bitset_to_string)
{
	int len = 0;
	unsigned char *bitset_data, *output_str;
	long count;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (len == 0) {
		RETURN_EMPTY_STRING();
	} else {
		len *= CHAR_BIT;
		output_str = emalloc(len+1);
		output_str[len] = '\0';
		for (count = 0; count < len; count++) {
			output_str[count] = ((bitset_data[count/CHAR_BIT] >> (count % CHAR_BIT)) & 1) ? '1' : '0';
		}

		RETURN_STRINGL((char *) output_str, len, 0);
	}
}
/* }}} */

/* {{{ proto string bitset_from_string(string source_str)
   Return a bitset, calculated from a string  */
PHP_FUNCTION(bitset_from_string)
{
	int str_len, len;
	unsigned char *str_data, *bitset_data;
	long data_index, str_index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str_data, &str_len) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	if (str_len == 0) {
		RETURN_EMPTY_STRING();
	} else {
		len = (str_len+CHAR_BIT-1)/CHAR_BIT;
		bitset_data = emalloc(len+1);
		memset(bitset_data, 0, len+1);

		for (data_index = str_index = 0; str_index < str_len; str_index++) {
			if (str_data[str_index] == '1') {
				bitset_data[data_index/CHAR_BIT]  |=  (1 << (data_index % CHAR_BIT));
				data_index++;
			} else if (str_data[str_index] == '0') {
				data_index++;
			}
		}

		RETURN_STRINGL((char *) bitset_data, len, 0);
	}
}
/* }}} */

/* {{{ proto array bitset_to_hash(string bitset)
   Return bitset mapped to an array */
PHP_FUNCTION(bitset_to_hash)
{
	int len;
	long count, count1;
	unsigned char *bitset_data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	/* Initialize return array */
	array_init(return_value);

	for (count=0; count < len; count++) {
		for (count1=0; count1 < CHAR_BIT; count1++) {
			if (bitset_data[count] & (1 << count1))
				add_index_long(return_value, count*CHAR_BIT + count1, 1);
		}
	}
}
/* }}} */

/* {{{ proto string bitset_from_hash(array bit_array)
   Maps an array of bits to a bitset  */
PHP_FUNCTION(bitset_from_hash)
{
	long len, arr_len;
	unsigned char *bitset_data;
	zval *bit_arr;
	zval **arr_val;

	char *arr_key_str;
	uint  arr_key_strlen;
	ulong  arr_key_num;
	long  max_key = -1;
	int key_type;

	HashPosition   pos;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &bit_arr) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	arr_len = zend_hash_num_elements(Z_ARRVAL_P(bit_arr));

	if (arr_len == 0) {
		RETURN_EMPTY_STRING();
	}

	/* We should walk through an array to get maximum key value */
	for (zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(bit_arr), &pos);
		(key_type = zend_hash_get_current_key_ex(Z_ARRVAL_P(bit_arr), &arr_key_str, &arr_key_strlen, &arr_key_num, 0, &pos)) != HASH_KEY_NON_EXISTANT;
		zend_hash_move_forward_ex(Z_ARRVAL_P(bit_arr), &pos)
	) {
		if (key_type == HASH_KEY_IS_STRING) {
			arr_key_num = strtol(arr_key_str, NULL, 10); /* Important: it uses base 10 conversion like convert_to_long() function */
		}

		if (max_key < arr_key_num) {
			max_key = arr_key_num;
		}
	}

	if (max_key < 0) {
		RETURN_EMPTY_STRING();
	}

	len = (max_key+1 + CHAR_BIT-1)/CHAR_BIT;
	bitset_data = emalloc(len+1);
	memset(bitset_data, 0, len+1);

	for (zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(bit_arr), &pos);
		zend_hash_get_current_data_ex(Z_ARRVAL_P(bit_arr), (void **) &arr_val, &pos) == SUCCESS;
		zend_hash_move_forward_ex(Z_ARRVAL_P(bit_arr), &pos)
	) {
		if (zend_is_true(*arr_val)) {
			if (zend_hash_get_current_key_ex(Z_ARRVAL_P(bit_arr), &arr_key_str, &arr_key_strlen, &arr_key_num, 0, &pos) == HASH_KEY_IS_STRING) {
				arr_key_num = strtol(arr_key_str, NULL, 10); /* Important: it uses base 10 conversion like convert_to_long() function */
			}

			if (arr_key_num >= 0) {
				bitset_data[arr_key_num/CHAR_BIT] |= 1 << (arr_key_num % CHAR_BIT);
			}
		}
	}

	RETURN_STRINGL((char *) bitset_data, len, 0);
}
/* }}} */

/* {{{ proto array bitset_to_array(string bitset)
   Return bitset represented as an array of bits */
PHP_FUNCTION(bitset_to_array)
{
	int len;
	long count, count1;
	unsigned char *bitset_data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	/* Initialize return array */
	array_init(return_value);

	for (count=0; count < len; count++) {
		for (count1=0; count1 < CHAR_BIT; count1++) {
			if (bitset_data[count] & (1 << count1)) {
				add_next_index_long(return_value, count*CHAR_BIT + count1);
			}
		}
	}
}
/* }}} */

/* {{{ int arrval_compare */
static int arrval_compare(const void *a, const void *b TSRMLS_DC)
{
	Bucket *f, *s;
	zval **fval, **sval;
	long first = 0, second = 0;

	f = *((Bucket **) a);
	s = *((Bucket **) b);
	 fval = ((zval **) f->pData);
	sval = ((zval **) s->pData);


	if (Z_TYPE_PP(fval) != IS_LONG) {
		SEPARATE_ZVAL(fval);
		convert_to_long_ex(fval);
		first = Z_LVAL_PP(fval);
	} else {
		first = Z_LVAL_PP(fval);
	}

	if (Z_TYPE_PP(sval) != IS_LONG) {
		SEPARATE_ZVAL(sval);
		convert_to_long_ex(sval);
		second = Z_LVAL_PP(sval);
	} else {
		second = Z_LVAL_PP(sval);
	}

	return first - second;
}
/* }}} */

/* {{{ proto string bitset_from_array(array bit_array)
   Converts an array of bits to a bitset  */
PHP_FUNCTION(bitset_from_array)
{
	long len, arr_len;
	unsigned char *bitset_data;
	zval *bit_arr;
	zval **arr_val;
	int need_destroy = 1;

	HashPosition   pos;
	long max_val = -1;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &bit_arr) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);
	arr_len = zend_hash_num_elements(Z_ARRVAL_P(bit_arr));

	if (arr_len == 0) {
		RETURN_EMPTY_STRING();
	}

	zend_hash_minmax(Z_ARRVAL_P(bit_arr), arrval_compare, 1, (void **) &arr_val TSRMLS_CC);

	need_destroy = 0;
	if (Z_TYPE_PP(arr_val)!=IS_LONG) {
		zval_copy_ctor(*arr_val);
		convert_to_long(*arr_val);
		need_destroy = 1;
	}

	max_val = Z_LVAL_PP(arr_val);

	if (need_destroy) {
		zval_dtor(*arr_val);
	}

	if (max_val < 0) {
		RETURN_EMPTY_STRING();
	}

	len = (max_val+1 + CHAR_BIT-1)/CHAR_BIT;
	bitset_data = emalloc(len+1);
	memset(bitset_data, 0, len+1);

	for (zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(bit_arr), &pos);
		zend_hash_get_current_data_ex(Z_ARRVAL_P(bit_arr), (void **) &arr_val, &pos) == SUCCESS;
		zend_hash_move_forward_ex(Z_ARRVAL_P(bit_arr), &pos)
	) {
		need_destroy = 0;

		if (Z_TYPE_PP(arr_val)!=IS_LONG) {
			zval_copy_ctor(*arr_val);
			convert_to_long(*arr_val);
			need_destroy = 1;
		}

		if (Z_LVAL_PP(arr_val) >= 0) {
			bitset_data[Z_LVAL_PP(arr_val)/CHAR_BIT] |= 1 << (Z_LVAL_PP(arr_val) % CHAR_BIT);
		}

		if (need_destroy) {
			zval_dtor(*arr_val);
		}
	}

	RETURN_STRINGL((char *) bitset_data, len, 0);
}
/* }}} */

/* {{{ proto bool bitset_is_empty(string bitset)
   Return TRUE if bitset is empty */
PHP_FUNCTION(bitset_is_empty)
{
	int len;
	unsigned char *bitset_data;
	long count;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, BITSET_DEPRECATED_MESSAGE);

	for (count = 0; count < len/(short)sizeof(unsigned long); count++) {
		if (((unsigned long *)bitset_data)[count]) {
			RETURN_FALSE;
		}
	}

	for (count = len - len % sizeof(unsigned long); count < len; count++) {
		if (bitset_data[count]) {
			RETURN_FALSE;
		}
	}

	RETURN_TRUE;
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
