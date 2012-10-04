--TEST--
BitSet BitSet::previousClearBit() - Verifies the previous clear bit is valid based on the provided index
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(20);
$b->set(18);
var_dump($b->previousClearBit(20));
var_dump($b->previousClearBit(18));
var_dump($b->previousClearBit(5));
?>
--EXPECT--
int(19)
int(17)
int(4)

