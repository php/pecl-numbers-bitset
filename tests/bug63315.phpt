--TEST--
Bug #63315 (BitSet::fromArray may modify original array value)
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$arr = array(5, 6, '7');
var_dump($arr);
BitSet::fromArray($arr);
var_dump($arr);
?>
--EXPECT--
array(3) {
  [0]=>
  int(5)
  [1]=>
  int(6)
  [2]=>
  string(1) "7"
}
array(3) {
  [0]=>
  int(5)
  [1]=>
  int(6)
  [2]=>
  string(1) "7"
}
