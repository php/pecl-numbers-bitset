--TEST--
BitSet BitSet::fromArray() - Verifies the provided input array is represented in set bits
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$arr = [1, 6, 17, 2];
$b = BitSet::fromArray($arr);
var_dump($b->__toString());
var_dump($b->toArray());

$b = BitSet::fromArray([0]);
var_dump($b->__toString());
var_dump($b->toArray());

$b = BitSet::fromArray([7]);
var_dump($b->__toString());
var_dump($b->toArray());
?>
--EXPECT--
string(24) "011000100000000001000000"
array(4) {
  [0]=>
  int(1)
  [1]=>
  int(2)
  [2]=>
  int(6)
  [3]=>
  int(17)
}
string(8) "10000000"
array(1) {
  [0]=>
  int(0)
}
string(8) "00000001"
array(1) {
  [0]=>
  int(7)
}

