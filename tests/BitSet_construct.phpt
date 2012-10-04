--TEST--
BitSet BitSet::__construct() - Generic constructor tests
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
// Verify we initially get 64 bits that are off
$b = new BitSet();
var_dump($b->__toString());

// Verify we get 8 bits that are off
$b = new BitSet(8);
var_dump($b->__toString());

/* Regardless of the value specified in the constructor, it should
 * always be rounded to the nearest byte in size
 */
$b = new BitSet(12); // CHAR_BIT = 8, so we should have 16 bits
var_dump($b->__toString());
?>
--EXPECT--
string(64) "0000000000000000000000000000000000000000000000000000000000000000"
string(8) "00000000"
string(16) "0000000000000000"
