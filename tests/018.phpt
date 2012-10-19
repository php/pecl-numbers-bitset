--TEST--
bitset_from_string
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
 if( bitset_is_empty( bitset_empty() ) )
      echo "empty input - ok\n";

 if( bitset_is_empty( bitset_empty(1024) ) )
      echo "set of zero - ok\n";

 $bitset = bitset_empty(1024);
 bitset_incl( $bitset, 1006 );
 if( !bitset_is_empty( $bitset ) )
      echo "non-trivial input - ok\n";

 $bitset = bitset_empty(1024);
 bitset_incl( $bitset, 1023 );
 if( !bitset_is_empty( $bitset ) )
      echo "non-trivial aligned input1 - ok\n";

 $bitset = bitset_empty(1024);
 bitset_incl( $bitset, 1024 );
 if( !bitset_is_empty( $bitset ) )
      echo "non-trivial aligned input2 - ok\n";
?>
--EXPECT--
empty input - ok
set of zero - ok
non-trivial input - ok
non-trivial aligned input1 - ok
non-trivial aligned input2 - ok
