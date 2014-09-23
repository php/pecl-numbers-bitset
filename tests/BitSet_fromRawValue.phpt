--TEST--
BitSet BitSet::fromRawValue() - Verifies the provided input raw value is represented in set bits
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = BitSet::fromRawValue(base64_decode('AA=='));
var_dump($b->__toString());
$b = BitSet::fromRawValue(base64_decode('IA=='));
var_dump($b->__toString());
var_dump(base64_encode($b->getRawValue()));
?>
--EXPECT--
string(8) "00000000"
string(8) "00000100"
string(4) "IA=="

