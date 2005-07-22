--TEST--
bitset_empty
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 if( bitset_to_string( bitset_empty() ) == "" )
      echo "empty input - ok\n";

 if( bitset_to_string( bitset_empty(0) ) == "" )
      echo "zero input - ok\n";

 if( bitset_to_string( bitset_empty(3) ) == "00000000" )
      echo "nonaligned small input - ok\n";

 if( bitset_to_string( bitset_empty(8) ) == "00000000" )
      echo "aligned small input1 - ok\n";

 if( bitset_to_string( bitset_empty(9) ) == "0000000000000000" )
      echo "aligned small input2 - ok\n";

 if( bitset_to_string( bitset_empty(34) ) == "0000000000000000000000000000000000000000" )
      echo "nonaligned large input - ok\n";

 if( bitset_to_string( bitset_empty(32) ) == "00000000000000000000000000000000" )
      echo "aligned large input1 - ok\n";
 if( bitset_to_string( bitset_empty(33) ) == "0000000000000000000000000000000000000000" )
      echo "aligned large input1 - ok\n";
?>
--EXPECT--
empty input - ok
zero input - ok
nonaligned small input - ok
aligned small input1 - ok
aligned small input2 - ok
nonaligned large input - ok
aligned large input1 - ok
aligned large input2 - ok
