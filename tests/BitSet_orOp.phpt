--TEST--
BitSet BitSet::orOp() - Test that logical OR operations actually work
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$c = new BitSet();
$b->set(2);
$b->set(6);
$c->set(2);
$c->set(9);
$b->orOp($c);
var_dump($b->__toString());
?>
--EXPECT--
string(64) "0010001001000000000000000000000000000000000000000000000000000000"
