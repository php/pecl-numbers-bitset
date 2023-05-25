--TEST--
BitSet BitSet::fromInteger() - Verifies the provided value is represented in set bits
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = BitSet::fromInteger(0);
var_dump($b->__toString());
var_dump($b->toInteger());

$b = BitSet::fromInteger(42);
var_dump($b->__toString());
var_dump($b->toInteger());

$b = BitSet::fromInteger(0x010203);
var_dump($b->__toString());
var_dump($b->toInteger());

$b = new BitSet(80);
try {
	var_dump($b->toInteger());
} catch (InvalidArgumentException $e) {
	echo "Exception: " . $e->getMessage() . "\n";
}

?>
--EXPECT--
string(64) "0000000000000000000000000000000000000000000000000000000000000000"
int(0)
string(64) "0101010000000000000000000000000000000000000000000000000000000000"
int(42)
string(64) "1100000001000000100000000000000000000000000000000000000000000000"
int(66051)
Exception: The total bits doesn't fit in an integer

