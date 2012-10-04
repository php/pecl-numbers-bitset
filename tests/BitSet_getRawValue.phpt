--TEST--
BitSet BitSet::getRawValue() - Verifies the binary string returned is as expected and integrity is maintained
--SKIPIF--
<?php if (!extension_loaded('bitset')) die('skipping missing extension'); ?>
--FILE--
<?php
$b = new BitSet(8);
var_dump(base64_encode($b->getRawValue()));

$b->set(5);
var_dump(base64_encode($b->getRawValue()));
var_dump(bin2hex($b->getRawValue()));
?>
--EXPECT--
string(4) "AA=="
string(4) "IA=="
string(2) "20"
