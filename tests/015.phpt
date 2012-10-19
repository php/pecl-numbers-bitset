--TEST--
bitset_from_hash
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
<?php die('skipping for now'); ?>
--FILE--
<?php
error_reporting(E_ALL ^ E_DEPRECATED);
  $bit_array = array();
  if( bitset_to_string( bitset_from_hash( $bit_array ) ) == "" )
      echo "empty input - ok\n";

  $bit_array = array( -11 => 1 );
  if( bitset_to_string( bitset_from_hash( $bit_array ) ) == "" )
      echo "negative input - ok\n";

  $bit_array = array(0,1,1,0,1,1,0,1,0,0,1,0, -11=> 1, "-3" => 1, -4 => 0, "-3" => 1, "-3000000" => 1);
  var_dump(bitset_to_string(bitset_from_hash($bit_array)));

  $bit_array = array(0,1,1,0,1,1,0,1,0,0,1,0,1,0,1,1,);
  var_dump(bitset_to_string(bitset_from_hash($bit_array)));

  $bit_array = array(0,1,1,0,1,1,0,1,0,0,1,0,1,0,1,1,1);
  var_dump(bitset_to_string(bitset_from_hash($bit_array)));

  $bit_array = array(  1 => 1,
                       3 => 1,
                       8 => 1,
                       4   => 1,
                      "7"  => 1,
                       12  => 1,
                      "13" => 1,
                      "16" => 1,
                      "11" => 1,
                       10  => 0    );
  var_dump(bitset_to_string(bitset_from_hash($bit_array)));
?>
--EXPECT--
empty input - ok
negative input - ok
string(16) "0110110100100000"
string(16) "0110110100101011"
string(24) "011011010010101110000000"
string(24) "010110011001110010000000"
