--TEST--
bitset_from_string
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
 if( bitset_equal(bitset_from_string(""), bitset_empty()) )
      echo "empty input - ok\n";

 if( bitset_equal(bitset_from_string("000000000"), bitset_empty(46)) )
      echo "set of zero - ok\n";


 if( bitset_equal(bitset_from_string("11111111111110"), bitset_fill(13)) )
      echo "non-trivial input - ok\n";

 if( bitset_equal(bitset_from_string("11111111"), bitset_fill(8)) )
      echo "non-trivial aligned input1 - ok\n";

 if( bitset_equal(bitset_from_string("111111111"), bitset_fill(9)) )
      echo "non-trivial aligned input2 - ok\n";
?>
--EXPECT--
empty input - ok
set of zero - ok
non-trivial input - ok
non-trivial aligned input1 - ok
non-trivial aligned input2 - ok
