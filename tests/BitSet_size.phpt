--TEST--
BitSet BitSet::size() - Tests to verify the total bits are maintained and correctly represented
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet();
var_dump($b->size());

$b = new BitSet(8);
$b->set(2, 4);
$b->clear(3);
var_dump($b->size());

$b = new BitSet(2048);
var_dump($b->size());
?>
--EXPECT--
int(64)
int(8)
int(2048)
