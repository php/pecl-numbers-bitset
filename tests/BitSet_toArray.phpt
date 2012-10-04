--TEST--
BitSet BitSet::toArray() - Verifies set bits are correctly returned in the array
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine. tired of seeing this comment yet?
$b->set(5);
$b->set(22);
var_dump($b->toArray());

$b->clear(22);
$b->set(36);
var_dump($b->toArray());
?>
--EXPECT--
array(2) {
  [0]=>
  int(5)
  [1]=>
  int(22)
}
array(2) {
  [0]=>
  int(5)
  [1]=>
  int(36)
}
