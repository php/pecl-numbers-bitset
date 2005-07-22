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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bitset.h"


#if COMPILE_DL_BITSET
/* {{{ content from zend_arg_defs.c:
 * since it is a .c file, it won't be installed for use by PECL extensions, so we include it here. */
ZEND_BEGIN_ARG_INFO(first_arg_force_ref, 0)
	ZEND_ARG_PASS_INFO(1)
ZEND_END_ARG_INFO();
/* }}} */
#endif


/* True global resources - no need for thread safety here */
static int le_bitset;

static short  big_endian_byte_oder;
/* indicates that bytes order is big endian (highest byte comes first)
   should be used for optimized shift operations
   should be initialized on module load                    .
   that's better to have this information on a compile time, but I don't know a way to do this
   (commeted by Alexander Veremyev cawa@csa.ru)
*/


/* {{{ bitset_functions[]
 */
function_entry bitset_functions[] = {
	PHP_FE(bitset_empty, NULL)
	PHP_FE(bitset_incl, first_arg_force_ref)
	PHP_FE(bitset_excl, first_arg_force_ref)
	PHP_FE(bitset_in, NULL)
	PHP_FE(bitset_fill, NULL)
	PHP_FE(bitset_intersection, NULL)
	PHP_FE(bitset_union, NULL)
	PHP_FE(bitset_invert, NULL)
	PHP_FE(bitset_subset, NULL)
	PHP_FE(bitset_equal, NULL)
	PHP_FE(bitset_to_string, NULL)
	PHP_FE(bitset_from_string, NULL)
	PHP_FE(bitset_to_hash, NULL)
	PHP_FE(bitset_from_hash, NULL)
	PHP_FE(bitset_to_array, NULL)
	PHP_FE(bitset_from_array, NULL)
	PHP_FE(bitset_is_empty, NULL)
	{NULL, NULL, NULL}	/* Must be the last line in bitset_functions[] */
};
/* }}} */

/* {{{ bitset_module_entry
 */
zend_module_entry bitset_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
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
	"1.0", /* Extension version number */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BITSET
ZEND_GET_MODULE(bitset)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(bitset)
{
	unsigned long long_value;

	long_value = 1;
	big_endian_byte_oder = (((unsigned char *)&long_value)[ 0 ] == 0);
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(bitset)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(bitset)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "bitset support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* {{{ proto string bitset_empty(integer bitcount)
   Return an empty bitset represented in a binary string. Optional parameter bitcount preallocates memory for bitset */
PHP_FUNCTION(bitset_empty)
{
	long len, bits = 0;
	unsigned char *bitset_data;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &bits) == FAILURE) {
		return;
	}

	if( bits < 0 ) {
		zend_error(E_WARNING, "First argument is not non-negative integer.");
		return;
	}

	if( bits == 0 ) {
		RETURN_EMPTY_STRING();
	} else {
		len = (bits+CHAR_BIT-1)/CHAR_BIT;
		bitset_data = emalloc( len+1 );
		memset( bitset_data, 0, len+1 );

		RETURN_STRINGL(bitset_data, len, 0);
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
	
	if( bit < 0 ) {
		zend_error(E_WARNING, "Second argument is not non-negative integer.");
		return;
	}

	if( Z_TYPE_P(param) == IS_STRING ) {
		bitset_data = Z_STRVAL_P( param );
		
		if( bit >= (Z_STRLEN_P( param ))*CHAR_BIT ) {
			old_len = Z_STRLEN_P( param );
			new_len = (old_len*2*CHAR_BIT > bit) ? old_len*2 : bit/CHAR_BIT + 1;

			if( old_len ) {
				Z_STRVAL_P( param ) = bitset_data = erealloc(bitset_data, new_len+1);
				Z_STRLEN_P( param ) = new_len;

				memset( bitset_data + old_len, 0, new_len - old_len + 1 );
			} else {
				zval_dtor(param);
				bitset_data = emalloc( new_len+1 ) ;
				memset( bitset_data, 0, new_len+1 );

				ZVAL_STRINGL(param, bitset_data, new_len, 0);
			}
		}
		bitset_data[ bit/CHAR_BIT ]  |=  1 << (bit % CHAR_BIT);
	} else {
		zend_error(E_WARNING, "The first argument is not a bitset");
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
	
	if( bit < 0 ) {
		zend_error(E_WARNING, "Second argument is not non-negative integer.");
		return;
	}

	if( Z_TYPE_P(param) == IS_STRING ) {
		bitset_data = Z_STRVAL_P( param );
		
		if( bit < Z_STRLEN_P( param )*CHAR_BIT )
			bitset_data[ bit/CHAR_BIT ]  &=  ~(1 << (bit % CHAR_BIT));
	} else {
		zend_error(E_WARNING, "The first argument is not a bitset");
	}
}
/* }}} */

/* {{{ proto bool bitset_in(string bitset, integer bit)
   Checks if bit in bitset */
PHP_FUNCTION(bitset_in)
{
	long len, bit;
	unsigned char *bitset_data;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &bitset_data, &len, &bit) == FAILURE) {
		return;
	}

	if( bit < 0 ) {
		RETURN_FALSE;  /*  All bits with a negative index should be treated as 0 */
	}

	if( len == 0 ) {
		RETURN_FALSE;
	} else if( bit >= len*CHAR_BIT ) {
		RETURN_FALSE;
	} else if( bitset_data[ bit/CHAR_BIT ] & (1 << (bit % CHAR_BIT) ) ) {
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

	if( bits < 0 ) {
		zend_error(E_WARNING, "First argument is not non-negative integer.");
		RETURN_EMPTY_STRING();
	} else if( bits == 0 ) {
		RETURN_EMPTY_STRING();
	} else {
		len = (bits+CHAR_BIT-1)/CHAR_BIT;
		bitset_data = emalloc( len+1 );
		memset( bitset_data, ~0, len );
		bitset_data[ len ] = '\0';
		if( bits % CHAR_BIT )
			bitset_data[ len-1 ] >>= (CHAR_BIT - (bits % CHAR_BIT));

		RETURN_STRINGL(bitset_data, len, 0);
	}
}
/* }}} */

/* {{{ proto string bitset_intersection(string bitset1, string bitset2)
   Return an intersection of two bitsets */
PHP_FUNCTION(bitset_intersection)
{
	long len1, len2, len;
	unsigned char *bitset_data1, *bitset_data2, *bitset_datares;
	long count;
	
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		                      "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	if( (len1 == 0)||(len2 == 0) ) {
		RETURN_EMPTY_STRING();
	} else {
		len = (len1 < len2) ? len1 : len2;
		bitset_datares = emalloc( len+1 );
		bitset_datares[ len ] = '\0';

		for( count = 0; count < len/(short)sizeof(unsigned long); count++ )
			((unsigned long *)bitset_datares)[ count ] = 
				((unsigned long *)bitset_data1)[ count ] & ((unsigned long *)bitset_data2)[ count ];

		for( count = len - len % sizeof(unsigned long); count < len; count++ )
			bitset_datares[ count ] = bitset_data1[ count ] & bitset_data2[ count ];

		RETURN_STRINGL(bitset_datares, len, 0);
	}
}
/* }}} */


/* {{{ proto string bitset_union(string bitset1, string bitset2)
   Return an union of two bitsets */
PHP_FUNCTION(bitset_union)
{
	long len1, len2, len, union_len;
	unsigned char *bitset_data1, *bitset_data2, *bitset_datares;
	long count;
	
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		                      "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	if( (len1 == 0)&&(len2 == 0) ) {
		RETURN_EMPTY_STRING();
	} else {
		if( len1 == len2 ) {
			union_len = len = len1;
			bitset_datares = emalloc( len+1 );
		} else if( len1 > len2 ) {
			len = len1;
			union_len = len2;

			bitset_datares = emalloc( len+1 );
			memcpy( bitset_datares + union_len, bitset_data1 + union_len, len1-len2);
		} else {
			len = len2;
			union_len = len1;

			bitset_datares = emalloc( len+1 );
			memcpy( bitset_datares + union_len, bitset_data2 + union_len, len2-len1);
		}
		bitset_datares[ len ] = '\0';

		for( count = 0; count < union_len/(short)sizeof(unsigned long); count++ )
			((unsigned long *)bitset_datares)[ count ] = 
				((unsigned long *)bitset_data1)[ count ] | ((unsigned long *)bitset_data2)[ count ];

		for( count = union_len - union_len % sizeof(unsigned long); count < union_len; count++ )
			bitset_datares[ count ] = bitset_data1[ count ] | bitset_data2[ count ];

		RETURN_STRINGL(bitset_datares, len, 0);
	}
}
/* }}} */

/* {{{ proto void bitset_invert(string bitset, integer size)
   Invert bitset */
PHP_FUNCTION(bitset_invert)
{
	long size;
	unsigned char *bitset_data, *bitset_out;
	long invert_count, src_len, new_len, count;
	
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &bitset_data, &src_len, &size) == FAILURE) {
		return;
	}
	
	if( size < 0 ) {
		zend_error(E_WARNING, "First argument is not non-negative integer.");
		RETURN_EMPTY_STRING();
	} else if( size == 0 ) {
		RETURN_EMPTY_STRING();
	} else {
		new_len = (size + CHAR_BIT-1)/CHAR_BIT;
		bitset_out = emalloc( new_len+1  );
		bitset_out[ new_len ] = '\0';

		if( new_len > src_len ) {
			memset(bitset_out + src_len, ~0, new_len - src_len);
			invert_count = src_len;
		} else {
			invert_count = new_len;
		}

		for( count = 0; count < invert_count/(short)sizeof(unsigned long); count++ )
			((unsigned long *)bitset_out)[ count ] = ~((unsigned long *)bitset_data)[ count ];

		for( count = invert_count - invert_count % sizeof(unsigned long); count < invert_count; count++ )
			bitset_out[ count ] = ~bitset_data[ count ];


		if( size % CHAR_BIT ) {   /* We should clear last bits */
			bitset_out[ new_len-1 ] &= ( 0xFF >> ( CHAR_BIT - size % CHAR_BIT ) );
		}

		RETURN_STRINGL(bitset_out, new_len, 0);
	}
}
/* }}} */


/* {{{ proto bool bitset_subset(string bitset1, string bitset2)
   Return TRUE if bitset2 is a subset of bitset1 */
PHP_FUNCTION(bitset_subset)
{
	long len1, len2;
	unsigned char *bitset_data1, *bitset_data2, *rest;
	long count, compare_len, zero_count;
	
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		                      "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	if(len1 >= len2) { /* We should ot care about the rest of bitset1 */
		rest        = NULL;
		zero_count  = 0;
		compare_len = len2;
	} else if(len1 < len2) { /* We should check, that the rest of bitset2 is empty */

		/* first step up to the "long" boundary  should be done here */
		for( count=len1; (count % sizeof(unsigned long))&&( count < len2 ); count++ )
			if( bitset_data2[ count ]  )
				RETURN_FALSE;

		rest = bitset_data2 + count;
		zero_count = len2 - count;

		compare_len = len1;
	}


	for( count = 0; count < compare_len/(short)sizeof(unsigned long); count++ )
		if( ((unsigned long *)bitset_data2)[ count ] !=
				(((unsigned long *)bitset_data2)[ count ] &
				 ((unsigned long *)bitset_data1)[ count ]   )  )
			RETURN_FALSE;

	for( count = compare_len - compare_len % sizeof(unsigned long); count < compare_len; count++ )
		if( bitset_data2[ count ] !=  (bitset_data2[ count ] & bitset_data1[ count ]) )
			RETURN_FALSE;

	for( count = 0; count < zero_count/(short)sizeof(unsigned long); count++ )
		if( ((unsigned long *)rest)[ count ] )
			RETURN_FALSE;

	for( count = zero_count - zero_count % sizeof(unsigned long); count < zero_count; count++ )
		if( rest[ count ] )
			RETURN_FALSE;
	
	RETURN_TRUE;
}
/* }}} */


/* {{{ proto bool bitset_equal(string bitset1, string bitset2)
   Return TRUE if bitset1 and bitset2 are equal. Please note that "01001110" and "0100111000000000" are equal */
PHP_FUNCTION(bitset_equal)
{
	long len1, len2;
	unsigned char *bitset_data1, *bitset_data2, *rest;
	long count, compare_len, zero_count;
	
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		                      "ss", &bitset_data1, &len1, &bitset_data2, &len2) == FAILURE) {
		return;
	}

	if(len1 == len2) { /* We should ot care about the rest of bitset1 */
		rest        = NULL;
		zero_count  = 0;
		compare_len = len2;
	} else if(len1 < len2) { /* We should check, that the rest of bitset2 is empty */

		/* first step up to the "long" boundary  should be done here */
		for( count=len1; (count % sizeof(unsigned long))&&( count < len2 ); count++ )
			if( bitset_data2[ count ]  )
				RETURN_FALSE;

		rest = bitset_data2 + count;
		zero_count = len2 - count;

		compare_len = len1;
	} else { /* len1 > len2 */
		/* We should check, that the rest of bitset1 is empty */

		/* first step up to the "long" boundary  should be done here */
		for( count=len2; (count % sizeof(unsigned long))&&( count < len1 ); count++ )
			if( bitset_data1[ count ]  )
				RETURN_FALSE;

		rest = bitset_data1 + count;
		zero_count = len1 - count;

		compare_len = len2;
	}


	if( memcmp( bitset_data1, bitset_data2, compare_len ) != 0 )
			RETURN_FALSE;


	for( count = 0; count < zero_count/(short)sizeof(unsigned long); count++ )
		if( ((unsigned long *)rest)[ count ] )
			RETURN_FALSE;

	for( count = zero_count - zero_count % sizeof(unsigned long); count < zero_count; count++ )
		if( rest[ count ] )
			RETURN_FALSE;
	
	RETURN_TRUE;
}
/* }}} */


/* {{{ proto string bitset_to_string(string bitset)
   Return a human readable string representation of a bitset */
PHP_FUNCTION(bitset_to_string)
{
	long len = 0;
	unsigned char *bitset_data, *output_str;
	long count;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	if( len == 0 ) {
		RETURN_EMPTY_STRING();
	} else {
		len *= CHAR_BIT;
		output_str = emalloc( len+1 );
		output_str[ len ] = '\0';
		for(count = 0; count < len; count++ )
		    output_str[ count ] = ( (bitset_data[ count/CHAR_BIT ] >> (count % CHAR_BIT)) & 1 ) ? '1' : '0';

		RETURN_STRINGL(output_str, len, 0);
	}
}
/* }}} */


/* {{{ proto string bitset_from_string(string source_str)
   Return a bitset, calculated from a string  */
PHP_FUNCTION(bitset_from_string)
{
	long str_len, len;
	unsigned char *str_data, *bitset_data;
	long data_index, str_index;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str_data, &str_len) == FAILURE) {
		return;
	}

	if( str_len == 0 ) {
		RETURN_EMPTY_STRING();
	} else {
		len = (str_len+CHAR_BIT-1)/CHAR_BIT;
		bitset_data = emalloc( len+1 );
		memset( bitset_data, 0, len+1 );

		for( data_index = str_index = 0; str_index < str_len; str_index++ )
			if( str_data[ str_index ] == '1' ) {
				bitset_data[ data_index/CHAR_BIT ]  |=  (1 << (data_index % CHAR_BIT) );

				data_index++;
			} else if( str_data[ str_index ] == '0' ) {
				data_index++;
			}

		RETURN_STRINGL(bitset_data, len, 0);
	}
}
/* }}} */


/* {{{ proto array bitset_to_hash(string bitset)
   Return bitset mapped to an array */
PHP_FUNCTION(bitset_to_hash)
{
	long len, count, count1;
	unsigned char *bitset_data;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	/* Initialize return array */
	array_init(return_value);

	for( count=0; count < len; count++ )
		for( count1=0; count1 < CHAR_BIT; count1++ ) {
			if( bitset_data[ count ] & (1 << count1) )
				add_index_long(return_value, count*CHAR_BIT + count1, 1 );
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
	long  arr_key_num;
	long  max_key = -1;
	int key_type;

	HashPosition   pos;

	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &bit_arr) == FAILURE) {
		return;
	}

	arr_len = zend_hash_num_elements(Z_ARRVAL_P(bit_arr));

	if( arr_len == 0 ) {
		RETURN_EMPTY_STRING();
	}

	/* We should walk through an array to get maximum key value */
	for( zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(bit_arr), &pos);
		(key_type = zend_hash_get_current_key_ex(Z_ARRVAL_P(bit_arr), &arr_key_str, &arr_key_strlen, &arr_key_num, 0, &pos)) != HASH_KEY_NON_EXISTANT;
		zend_hash_move_forward_ex(Z_ARRVAL_P(bit_arr), &pos)
	) {
		if( key_type == HASH_KEY_IS_STRING )
			arr_key_num = strtol(arr_key_str, NULL, 10); /* Important: it uses base 10 conversion like convert_to_long() function */

		if( max_key < arr_key_num )
			max_key = arr_key_num;
	}

	if( max_key < 0 ) {
		RETURN_EMPTY_STRING();
	}

	len = ( max_key+1 + CHAR_BIT-1 )/CHAR_BIT;
	bitset_data = emalloc( len+1 );
	memset( bitset_data, 0, len+1 );

	for( zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(bit_arr), &pos);
		zend_hash_get_current_data_ex(Z_ARRVAL_P(bit_arr), (void **) &arr_val, &pos) == SUCCESS;
		zend_hash_move_forward_ex(Z_ARRVAL_P(bit_arr), &pos)
	) {
		if( zend_is_true(*arr_val) ) {
			if( zend_hash_get_current_key_ex(Z_ARRVAL_P(bit_arr), &arr_key_str, &arr_key_strlen, &arr_key_num, 0, &pos) == HASH_KEY_IS_STRING )
				arr_key_num = strtol(arr_key_str, NULL, 10); /* Important: it uses base 10 conversion like convert_to_long() function */

			if( arr_key_num >= 0)
				bitset_data[ arr_key_num/CHAR_BIT] |= 1 << (arr_key_num % CHAR_BIT);
		}
	}


	RETURN_STRINGL(bitset_data, len, 0);
}
/* }}} */


/* {{{ proto array bitset_to_array(string bitset)
   Return bitset represented as an array of bits */
PHP_FUNCTION(bitset_to_array)
{
	long len, count, count1;
	unsigned char *bitset_data;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	/* Initialize return array */
	array_init(return_value);

	for( count=0; count < len; count++ )
		for( count1=0; count1 < CHAR_BIT; count1++ ) {
			if( bitset_data[ count ] & (1 << count1) )
				add_next_index_long(return_value, count*CHAR_BIT + count1 );
		}
}
/* }}} */



static int arrval_compare(const void *a, const void *b TSRMLS_DC)
{
	Bucket *f, *s;
	zval *fval, *sval;
	int result;
	unsigned char fneed_destroy = 0, sneed_destroy = 0;
 

	f = *((Bucket **) a);
	s = *((Bucket **) b);
 	fval = *((zval **) f->pData);
	sval = *((zval **) s->pData);

	if (Z_TYPE_P(fval) != IS_LONG) {
		fneed_destroy = 1;
		zval_copy_ctor(fval);
		convert_to_long(fval);
	}
	if (Z_TYPE_P(sval) != IS_LONG) {
		sneed_destroy = 1;
		zval_copy_ctor(sval);
		convert_to_long(sval);
	}

	result = Z_LVAL_P(fval) - Z_LVAL_P(sval);

	if (fneed_destroy)
		zval_dtor(sval);
	if (sneed_destroy)
		zval_dtor(sval);
	
	return result;
}


/* {{{ proto string bitset_from_array(array bit_array)
   Converts an array of bits to a bitset  */
PHP_FUNCTION(bitset_from_array)
{
	long len, arr_len;
	unsigned char *bitset_data;
	zval *bit_arr;
	zval **arr_val;
	unsigned char need_destroy;

	HashPosition   pos;
	long max_val = -1;

	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &bit_arr) == FAILURE) {
		return;
	}

	arr_len = zend_hash_num_elements(Z_ARRVAL_P(bit_arr));

	if( arr_len == 0 ) {
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
		
	if( need_destroy )
		zval_dtor(*arr_val);

	if( max_val < 0 ) {
		RETURN_EMPTY_STRING();
	}

	len = ( max_val+1 + CHAR_BIT-1 )/CHAR_BIT;
	bitset_data = emalloc( len+1 );
	memset( bitset_data, 0, len+1 );

	for( zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(bit_arr), &pos);
		zend_hash_get_current_data_ex(Z_ARRVAL_P(bit_arr), (void **) &arr_val, &pos) == SUCCESS;
		zend_hash_move_forward_ex(Z_ARRVAL_P(bit_arr), &pos)
	) {
		need_destroy = 0;

		if (Z_TYPE_PP(arr_val)!=IS_LONG) {
			zval_copy_ctor(*arr_val);
			convert_to_long(*arr_val);
			need_destroy = 1;
		}

		if( Z_LVAL_PP(arr_val) >= 0 )
			bitset_data[ Z_LVAL_PP(arr_val)/CHAR_BIT] |= 1 << (Z_LVAL_PP(arr_val) % CHAR_BIT);
		
		if( need_destroy )
				zval_dtor(*arr_val);
	}


	RETURN_STRINGL(bitset_data, len, 0);
}
/* }}} */


/* {{{ proto bool bitset_is_empty(string bitset)
   Return TRUE if bitset is empty */
PHP_FUNCTION(bitset_is_empty)
{
	long len;
	unsigned char *bitset_data;
	long count;
	
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitset_data, &len) == FAILURE) {
		return;
	}

	for( count = 0; count < len/(short)sizeof(unsigned long); count++ )
		if( ((unsigned long *)bitset_data)[ count ]  )
			RETURN_FALSE;

	for( count = len - len % sizeof(unsigned long); count < len; count++ )
		if( bitset_data[ count ] )
			RETURN_FALSE;
	
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
