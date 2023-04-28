/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 7e7bc0842cd6f3adb32ecd9dd1f031c47a0988a9 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_BitSet___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, value, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_andOp, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, set, BitSet, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BitSet_andNotOp arginfo_class_BitSet_andOp

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_cardinality, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_clear, 0, 0, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, from, IS_LONG, 0, "-1")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, to, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BitSet_fromArray, 0, 1, BitSet, 0)
	ZEND_ARG_TYPE_INFO(0, arr, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_BitSet_fromString, 0, 1, BitSet, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BitSet_fromRawValue arginfo_class_BitSet_fromString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_get, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_getRawValue, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_intersects, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, set, BitSet, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_isEmpty, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BitSet_length arginfo_class_BitSet_cardinality

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_class_BitSet_nextClearBit, 0, 1, MAY_BE_BOOL|MAY_BE_LONG)
	ZEND_ARG_TYPE_INFO(0, start, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BitSet_nextSetBit arginfo_class_BitSet_nextClearBit

#define arginfo_class_BitSet_orOp arginfo_class_BitSet_andOp

#define arginfo_class_BitSet_previousClearBit arginfo_class_BitSet_nextClearBit

#define arginfo_class_BitSet_previousSetBit arginfo_class_BitSet_nextClearBit

#define arginfo_class_BitSet_set arginfo_class_BitSet_clear

#define arginfo_class_BitSet_size arginfo_class_BitSet_cardinality

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BitSet_toArray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BitSet_xorOp arginfo_class_BitSet_andOp

#define arginfo_class_BitSet___toString arginfo_class_BitSet_getRawValue


ZEND_METHOD(BitSet, __construct);
ZEND_METHOD(BitSet, andOp);
ZEND_METHOD(BitSet, andNotOp);
ZEND_METHOD(BitSet, cardinality);
ZEND_METHOD(BitSet, clear);
ZEND_METHOD(BitSet, fromArray);
ZEND_METHOD(BitSet, fromString);
ZEND_METHOD(BitSet, fromRawValue);
ZEND_METHOD(BitSet, get);
ZEND_METHOD(BitSet, getRawValue);
ZEND_METHOD(BitSet, intersects);
ZEND_METHOD(BitSet, isEmpty);
ZEND_METHOD(BitSet, length);
ZEND_METHOD(BitSet, nextClearBit);
ZEND_METHOD(BitSet, nextSetBit);
ZEND_METHOD(BitSet, orOp);
ZEND_METHOD(BitSet, previousClearBit);
ZEND_METHOD(BitSet, previousSetBit);
ZEND_METHOD(BitSet, set);
ZEND_METHOD(BitSet, size);
ZEND_METHOD(BitSet, toArray);
ZEND_METHOD(BitSet, xorOp);
ZEND_METHOD(BitSet, __toString);


static const zend_function_entry class_BitSet_methods[] = {
	ZEND_ME(BitSet, __construct, arginfo_class_BitSet___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, andOp, arginfo_class_BitSet_andOp, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, andNotOp, arginfo_class_BitSet_andNotOp, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, cardinality, arginfo_class_BitSet_cardinality, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, clear, arginfo_class_BitSet_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, fromArray, arginfo_class_BitSet_fromArray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(BitSet, fromString, arginfo_class_BitSet_fromString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(BitSet, fromRawValue, arginfo_class_BitSet_fromRawValue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(BitSet, get, arginfo_class_BitSet_get, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, getRawValue, arginfo_class_BitSet_getRawValue, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, intersects, arginfo_class_BitSet_intersects, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, isEmpty, arginfo_class_BitSet_isEmpty, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, length, arginfo_class_BitSet_length, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, nextClearBit, arginfo_class_BitSet_nextClearBit, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, nextSetBit, arginfo_class_BitSet_nextSetBit, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, orOp, arginfo_class_BitSet_orOp, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, previousClearBit, arginfo_class_BitSet_previousClearBit, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, previousSetBit, arginfo_class_BitSet_previousSetBit, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, set, arginfo_class_BitSet_set, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, size, arginfo_class_BitSet_size, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, toArray, arginfo_class_BitSet_toArray, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, xorOp, arginfo_class_BitSet_xorOp, ZEND_ACC_PUBLIC)
	ZEND_ME(BitSet, __toString, arginfo_class_BitSet___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_BitSet(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "BitSet", class_BitSet_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	return class_entry;
}
