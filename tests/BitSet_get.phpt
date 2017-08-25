--TEST--
BitSet BitSet::get() - Verifies integrity of bit index retrieval
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(); // 64 bits is fine
$b->set(5);
var_dump($b->get(0));
var_dump($b->get(5));
var_dump($b->get(20));
$b->set(20);
var_dump($b->get(20));
try {
    var_dump($b->get(64));
} catch (Exception $e) {
    echo get_class($e).'-'.$e->getMessage()."\n";
}
?>
--EXPECT--
bool(false)
bool(true)
bool(false)
bool(true)
OutOfRangeException-The specified index parameter exceeds the total number of bits available
