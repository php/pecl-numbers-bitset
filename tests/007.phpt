--TEST--
bitset_intersection
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 if( bitset_to_string(   bitset_intersection( bitset_empty(),
                                              bitset_empty()
                                            )
                     ) == ""
   )
      echo "empty input - ok\n";


 
 if( bitset_equal(   bitset_intersection( bitset_from_string( "000100110010110010101110011001110111" ),
                                          bitset_from_string( "001100000110101100110011100101100101" )
                                        ),
                     bitset_from_string (                     "000100000010100000100010000001100101"   )
                 )
   )
      echo "same length - ok\n";


 if( bitset_equal(   bitset_intersection( bitset_from_string( "0001001100101100101011100110011101110011010110000011101001" ),
                                          bitset_from_string( "001100000110101100110011100101100101" )
                                        ),
                     bitset_from_string (                     "000100000010100000100010000001100101"   )
                 )
   )
      echo "first is greater - ok\n";

 if( bitset_equal(   bitset_intersection( bitset_from_string( "000100110010110010101110011001110111" ),
                                          bitset_from_string( "001100000110101100110011100101100101000110101110010101011011001" )
                                        ),
                     bitset_from_string (                     "000100000010100000100010000001100101"   )
                 )
   )
      echo "second is greater - ok\n";
?>
--EXPECT--
empty input - ok
same length - ok
first is greater - ok
second is greater - ok
