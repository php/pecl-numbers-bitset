--TEST--
bitset_to_string
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
 if( bitset_to_string( bitset_empty() ) == "" )
      echo "empty input - ok\n";

 if( bitset_to_string( bitset_empty(0) ) == "" )
      echo "zero input - ok\n";

 if( bitset_to_string( bitset_empty(1) ) == "00000000" )
      echo "set of zero - ok\n";


 if( bitset_to_string( bitset_fill(13) ) == "1111111111111000" )
      echo "non-trivial input - ok\n";

 if( bitset_to_string( bitset_fill(8) ) == "11111111" )
      echo "non-trivial aligned input1 - ok\n";

 if( bitset_to_string( bitset_fill(9) ) == "1111111110000000" )
      echo "non-trivial aligned input2 - ok\n";
?>
--EXPECT--
empty input - ok
zero input - ok
set of zero - ok
non-trivial input - ok
non-trivial aligned input1 - ok
non-trivial aligned input2 - ok
