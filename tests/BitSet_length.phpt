--TEST--
BitSet BitSet::length() - Verifies the highest bit + 1 is returned 
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(33);
var_dump($b->length());

$b->set(22);
var_dump($b->length());

$b->set(55);
var_dump($b->length());

$b->clear(55);
var_dump($b->length());
?>
--EXPECT--
int(34)
int(34)
int(56)
int(34)

