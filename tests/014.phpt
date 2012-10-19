--TEST--
bitset_to_hash
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
 if( count(bitset_to_hash( bitset_empty() )) == 0 )
      echo "empty input - ok\n";

  $bit_array = bitset_to_hash( bitset_from_string("01101101") );
  if( (count( $bit_array ) == 5)&&( ( $bit_array[ 1 ] === 1 )&&( $bit_array[ 2 ] === 1 )&&( $bit_array[ 4 ] === 1 )&&
                                    ( $bit_array[ 5 ] === 1 )&&( $bit_array[ 7 ] === 1 ) )
    )
      echo "non-trivial input - ok\n";
?>
--EXPECT--
empty input - ok
non-trivial input - ok
