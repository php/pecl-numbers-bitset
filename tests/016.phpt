--TEST--
bitset_to_array
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
 if( count(bitset_to_array( bitset_empty() )) == 0 )
      echo "empty input - ok\n";

  $bit_array  = bitset_to_array( bitset_from_string("01101101") );
  $test_array = array(1,2,4,5,7);
  if( count(array_diff( $bit_array, $test_array )) == 0 )
      echo "non-trivial input - ok\n";
?>
--EXPECT--
empty input - ok
non-trivial input - ok
