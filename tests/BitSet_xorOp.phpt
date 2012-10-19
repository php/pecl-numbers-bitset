--TEST--
BitSet BitSet::xorOp() - Test that logical XOR operations actually work
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$c = new BitSet();
$b->set(2);
$b->set(6);
$c->set(2);
$b->xorOp($c);
var_dump($b->__toString());
?>
--EXPECT--
string(64) "0000001000000000000000000000000000000000000000000000000000000000"
