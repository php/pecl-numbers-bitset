--TEST--
BitSet BitSet::fromArray() - Verifies the provided input array is represented in set bits
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$arr = array(1, 6, 17, 2);
$b = BitSet::fromArray($arr);
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


