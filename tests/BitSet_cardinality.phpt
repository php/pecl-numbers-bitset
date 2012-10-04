--TEST--
BitSet BitSet::cardinality() - Verifies all true bits that are set are correctly counted
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(5);
$b->set(33);
$b->set(63);

var_dump($b->cardinality());

$b->clear(63);

var_dump($b->cardinality());

$b->set(32);
$b->clear(33);

var_dump($b->cardinality());
?>
--EXPECT--
int(3)
int(2)
int(2)

