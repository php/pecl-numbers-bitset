--TEST--
bitset_from_array
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php
error_reporting(E_ALL ^ E_DEPRECATED);
  $bit_array = array();
  if( bitset_to_string( bitset_from_array( $bit_array ) ) == "" )
      echo "empty input - ok\n";

  $bit_array = array( -11 );
  if( bitset_to_string( bitset_from_array( $bit_array ) ) == "" )
      echo "negative input - ok\n";

  $bit_array = array(  1, 3, 8, 4, "7", 12, "13", "16", "11", -11, "-3", -4 );
  if( bitset_to_string( bitset_from_array( $bit_array ) ) == "010110011001110010000000" )
      echo "non-trivial input - ok\n";

  $bit_array = array(2,7);
  if( bitset_to_string( bitset_from_array( $bit_array ) ) == "00100001" )
      echo "non-trivial aligned input1 - ok\n";
 
  $bit_array = array(2,8);
  if( bitset_to_string( bitset_from_array( $bit_array ) ) == "0010000010000000" )
      echo "non-trivial aligned input2 - ok\n";
?>
--EXPECT--
empty input - ok
negative input - ok
non-trivial input - ok
non-trivial aligned input1 - ok
non-trivial aligned input2 - ok
