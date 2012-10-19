--TEST--
BitSet BitSet::andOp() - Test that logical AND operations actually work
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(2);
$b->set(6);
$c = new BitSet();
$c->set(2);
$c->set(50);
$b->andOp($c);
var_dump($b->__toString());
?>
--EXPECT--
string(64) "0010000000000000000000000000000000000000000000000000000000000000"
