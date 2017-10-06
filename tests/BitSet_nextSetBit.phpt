--TEST--
BitSet BitSet::nextSetBit() - Verifies the next set bit is valid based on the provided index
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(20);
$b->set(18);
var_dump($b->nextSetBit(0));
var_dump($b->nextSetBit(20));
var_dump($b->nextSetBit(18));
var_dump($b->nextSetBit(5));
try {
    var_dump($b->nextSetBit(63));
} catch (Exception $e) {
    echo get_class($e).': '.$e->getMessage()."\n";
}

?>
--EXPECT--
int(18)
bool(false)
int(20)
int(18)
InvalidArgumentException: There are no bits larger than the index provided
