--TEST--
bitset_in
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 if( !bitset_in( bitset_empty(), 4 ) )
      echo "test in an empty bitset - ok\n";

 $bitset = bitset_fill( 1024 );
 if( !bitset_in( $bitset, 10240 ) )
      echo "test in a bitset after boundary - ok\n";
 
 bitset_excl( $bitset, 67 );
 if( !bitset_in( $bitset, 67 ) )
      echo "test 0 in a bitset - ok\n";

 bitset_excl( $bitset, 127 );
 if( !bitset_in( $bitset, 127 ) )
      echo "test 0 in a bitset aligned1 - ok\n";

 bitset_excl( $bitset, 512 );
 if( !bitset_in( $bitset, 512 ) )
      echo "test 0 in a bitset aligned2 - ok\n";
 

 $bitset = bitset_fill( 1024 );

 bitset_incl( $bitset, 67 );
 if( bitset_in( $bitset, 67 ) )
      echo "test 1 in a bitset - ok\n";

 bitset_incl( $bitset, 127 );
 if( bitset_in( $bitset, 127 ) )
      echo "test 1 in a bitset aligned1 - ok\n";

 bitset_incl( $bitset, 512 );
 if( bitset_in( $bitset, 521 ) )
      echo "test 1 in a bitset aligned2 - ok\n";

?>
--EXPECT--
test in an empty bitset - ok
test in a bitset after boundary - ok
test 0 in a bitset - ok
test 0 in a bitset aligned1 - ok
test 0 in a bitset aligned2 - ok
test 1 in a bitset - ok
test 1 in a bitset aligned1 - ok
test 1 in a bitset aligned2 - ok
