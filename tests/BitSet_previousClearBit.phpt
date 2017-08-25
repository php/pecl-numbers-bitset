--TEST--
BitSet BitSet::previousClearBit() - Verifies the previous clear bit is valid based on the provided index
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(20);
$b->set(18);
try {
    var_dump($b->previousClearBit(0));
} catch (Exception $e) {
    var_dump(get_class($e).': '.$e->getMessage());
}
var_dump($b->previousClearBit(20));
var_dump($b->previousClearBit(18));
var_dump($b->previousClearBit(5));
try {
    var_dump($b->previousClearBit(65));
} catch (Exception $e) {
    var_dump(get_class($e).': '.$e->getMessage());
}
?>
--EXPECT--
string(75) "InvalidArgumentException: There are no bits smaller than the index provided"
int(19)
int(17)
int(4)
string(93) "OutOfRangeException: The specified index parameter exceeds the total number of bits available"
