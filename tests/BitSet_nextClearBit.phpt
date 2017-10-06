--TEST--
BitSet BitSet::nextClearBit() - Verifies the next clear bit is valid based on the provided index
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(20);
$b->set(18);
var_dump($b->nextClearBit(0));
var_dump($b->nextClearBit(20));
var_dump($b->nextClearBit(18));
var_dump($b->nextClearBit(5));
try {
    var_dump($b->nextClearBit(63));
} catch (Exception $e) {
    echo get_class($e).': '.$e->getMessage()."\n";
}
?>
--EXPECT--
int(1)
int(21)
int(19)
int(6)
InvalidArgumentException: There are no bits larger than the index provided
