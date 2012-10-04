--TEST--
BitSet BitSet::get() - Verifies integrity of bit index retrieval
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(5);
var_dump($b->get(5));
var_dump($b->get(20));
$b->set(20);
var_dump($b->get(20));
?>
--EXPECT--
bool(true)
bool(false)
bool(true)

