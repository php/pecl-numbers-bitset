--TEST--
bitset_excl
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 $bitset = bitset_empty();

 bitset_excl( $bitset, 2 );
 if( bitset_to_string( $bitset ) == "" )
      echo "exclude from empty bitset - ok\n";

 bitset_incl( $bitset, 1 );
 bitset_incl( $bitset, 5 );
 bitset_excl( $bitset, 1 );
 if( bitset_to_string( $bitset ) == "00000100" )
      echo "exclude from an existing part of a bitset - ok\n";

 bitset_excl( $bitset, 33 );
 if( bitset_to_string( $bitset ) == "00000100" )
      echo "exclude after boundary - ok\n";
?>
--EXPECT--
exclude from empty bitset - ok
exclude from an existing part of a bitset - ok
exclude after boundary - ok
