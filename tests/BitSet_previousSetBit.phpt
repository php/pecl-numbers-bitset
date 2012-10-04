--TEST--
BitSet BitSet::previousSetBit() - Verifies the previous set bit is valid based on the provided index
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(20);
$b->set(18);
var_dump($b->previousSetBit(20));
var_dump($b->previousSetBit(18));
$b->set(1);
var_dump($b->previousSetBit(5));
?>
--EXPECT--
int(18)
bool(false)
int(1)

