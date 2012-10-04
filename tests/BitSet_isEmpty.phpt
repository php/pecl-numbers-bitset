--TEST--
BitSet BitSet::isEmpty() - Verifies that isEmpty truly checks for all off bits
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
var_dump($b->isEmpty()); 

$b->set(32);
var_dump($b->isEmpty());

$b->clear(32);
$b->set(40);
$b->clear(40);
var_dump($b->isEmpty());
?>
--EXPECT--
bool(true)
bool(false)
bool(true)

