--TEST--
BitSet BitSet::intersects() - if the provided value has any bits set to true that are also true in this object
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(16);
$c = new BitSet(16);
var_dump($b->intersects($c)); // false
var_dump($c->intersects($b)); // false
$b->set(2);
$c->set(10);
var_dump($b->intersects($c)); // false
var_dump($c->intersects($b)); // false
$b->set(10);
var_dump($b->intersects($c)); // true
var_dump($c->intersects($b)); // true
?>
--EXPECT--
bool(false)
bool(false)
bool(false)
bool(false)
bool(true)
bool(true)
