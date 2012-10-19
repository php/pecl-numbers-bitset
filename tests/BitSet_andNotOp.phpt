--TEST--
BitSet BitSet::andNotOp() - Test that switching set bits to off with input BitSet
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$c = new BitSet();
$b->set(2);
$b->set(6);
$c->set(2);
$b->andNotOp($c);
var_dump($b->__toString());
?>
--EXPECT--
string(64) "0000001000000000000000000000000000000000000000000000000000000000"
