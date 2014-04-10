--TEST--
BitSet BitSet::set() - Tests for setting bits or a range of bits on
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(8);
var_dump($b->__toString());
$b->set(2);
var_dump($b->__toString());

$b->set(2, 4); // Set bits 2, 3 and 4 on
var_dump($b->__toString());

$b->set(); // Set all bits on
var_dump($b->__toString());

$b = new BitSet(8);
$b->set(0); // Set all bits on
var_dump($b->__toString());

$b = new BitSet(8);
$b->set(0,0); // Set just the first bit
var_dump($b->__toString());
?>
--EXPECT--
string(8) "00000000"
string(8) "00100000"
string(8) "00111000"
string(8) "11111111"
string(8) "11111111"
string(8) "10000000"
