--TEST--
BitSet BitSet::previousSetBit() - Verifies the previous set bit is valid based on the provided index
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(20);
$b->set(18);
try {
    var_dump($b->previousSetBit(0));
} catch (Exception $e) {
    var_dump(get_class($e).': '.$e->getMessage());
}
var_dump($b->previousSetBit(20));
var_dump($b->previousSetBit(18));
$b->set(1);
var_dump($b->previousSetBit(5));
try {
    var_dump($b->previousSetBit(65));
} catch (Exception $e) {
    var_dump(get_class($e).': '.$e->getMessage());
}
?>
--EXPECT--
string(75) "InvalidArgumentException: There are no bits smaller than the index provided"
int(18)
bool(false)
int(1)
string(93) "OutOfRangeException: The specified index parameter exceeds the total number of bits available"

