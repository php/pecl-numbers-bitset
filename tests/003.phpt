--TEST--
bitset_incl
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 $bitset = bitset_empty();

 bitset_incl( $bitset, 3 );
 if( bitset_to_string( $bitset ) == "00010000" )
      echo "include to empty bitset - ok\n";

 bitset_incl( $bitset, 1 );
 if( bitset_to_string( $bitset ) == "01010000" )
      echo "include to existing part of a bitset - ok\n";

 bitset_incl( $bitset, 35 );
 if( bitset_to_string( $bitset ) == "0101000000000000000000000000000000010000" )
      echo "include after boundary - ok\n";

 bitset_incl( $bitset, 47 );
 if( bitset_equal( $bitset, bitset_from_string( "010100000000000000000000000000000001000000000001") ) )
      echo "include after boundary aligned 1 - ok\n";

 bitset_incl( $bitset, 48 );
 if( bitset_equal( $bitset, bitset_from_string( "0101000000000000000000000000000000010000000000011") ) )
      echo "include after boundary aligned 2 - ok\n";
?>
--EXPECT--
include to empty bitset - ok
include to existing part of a bitset - ok
include after boundary - ok
include after boundary aligned 1 - ok
include after boundary aligned 2 - ok
