--TEST--
bitset_fill
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 if( bitset_to_string( bitset_fill(0) ) == "" )
      echo "zero input - ok\n";

 if( bitset_to_string( bitset_fill(3) ) == "11100000" )
      echo "nonaligned small input - ok\n";

 if( bitset_to_string( bitset_fill(8) ) == "11111111" )
      echo "aligned small input1 - ok\n";

 if( bitset_to_string( bitset_fill(9) ) == "1111111110000000" )
      echo "aligned small input2 - ok\n";

 if( bitset_to_string( bitset_fill(34) ) == "1111111111111111111111111111111111000000" )
      echo "nonaligned large input - ok\n";

 if( bitset_to_string( bitset_fill(32) ) == "11111111111111111111111111111111" )
      echo "aligned large input1 - ok\n";
 if( bitset_to_string( bitset_fill(33) ) == "1111111111111111111111111111111110000000" )
      echo "aligned large input1 - ok\n";
?>
--EXPECT--
zero input - ok
nonaligned small input - ok
aligned small input1 - ok
aligned small input2 - ok
nonaligned large input - ok
aligned large input1 - ok
aligned large input2 - ok
