--TEST--
BitSet BitSet::nextSetBit() - Verifies the next set bit is valid based on the provided index
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(20);
$b->set(18);
var_dump($b->nextSetBit(20));
var_dump($b->nextSetBit(18));
var_dump($b->nextSetBit(5));
?>
--EXPECT--
bool(false)
int(20)
int(18)

