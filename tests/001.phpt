--TEST--
Check for bitset presence
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 echo "bitset extension is available";
?>
--EXPECT--
bitset extension is available
