--TEST--
BitSet BitSet::fromString() - Verifies BitSet correctly parses incoming strings to its binary representation
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = BitSet::fromString('0110');
var_dump($b->__toString());

$b = BitSet::fromString('0010000010');
var_dump($b->__toString());

$b = BitSet::fromString('0200100010');
var_dump($b->__toString());

$b = BitSet::fromString('');
var_dump($b->__toString());
?>
--EXPECT--
string(8) "01100000"
string(16) "0010000010000000"
string(16) "0000100010000000"
string(64) "0000000000000000000000000000000000000000000000000000000000000000"
