--TEST--
BitSet BitSet::clear() - Test clearing bits individually, as sets and as a whole
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet();
$b->set(50);
$b->set(63);
var_dump($b->get(50));
$b->clear(50);
var_dump($b->get(50));
$b->clear();
var_dump($b->__toString());

$b->set(5);
$b->set(10);
$b->set(20);
$b->clear(5, 11);
var_dump($b->__toString());

$b->set(0, 1);
$b->clear(0);
var_dump($b->__toString());
try {
    var_dump($b->clear(64));
} catch (Exception $e) {
    echo get_class($e).': '.$e->getMessage()."\n";
}
?>
--EXPECT--
bool(true)
bool(false)
string(64) "0000000000000000000000000000000000000000000000000000000000000000"
string(64) "0000000000000000000010000000000000000000000000000000000000000000"
string(64) "0100000000000000000010000000000000000000000000000000000000000000"
OutOfRangeException: The requested start index is greater than the total number of bits