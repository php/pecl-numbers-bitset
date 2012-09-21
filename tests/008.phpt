--TEST--
bitset_union
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
 if( bitset_to_string(   bitset_union( bitset_empty(),
                                       bitset_empty()
                                     )
                     ) == ""
   )
      echo "empty input - ok\n";



 if( bitset_equal(   bitset_union( bitset_empty(),
                                   bitset_from_string( "001100000110101100110011100101100101" )
                                 ),
                     bitset_from_string(               "001100000110101100110011100101100101"   )
                 )
   )
      echo "first is empty - ok\n";



 if( bitset_equal(   bitset_union( bitset_from_string( "000100110010110010101110011001110111" ),
                                   bitset_empty()
                                 ),
                     bitset_from_string(               "000100110010110010101110011001110111"   )
                 )
   )
      echo "second is empty - ok\n";



 if( bitset_equal(   bitset_union( bitset_from_string( "000100110010110010101110011001110111" ),
                                   bitset_from_string( "001100000110101100110011100101100101" )
                                 ),
                     bitset_from_string(               "001100110110111110111111111101110111"   )
                 )
   )
      echo "same length - ok\n";



 if( bitset_equal(   bitset_union( bitset_from_string( "0001001100101100101011100110011101110011010110000011101001" ),
                                   bitset_from_string( "001100000110101100110011100101100101" )
                                        ),
                     bitset_from_string (              "0011001101101111101111111111011101110011010110000011101001"   )
                 )
   )
      echo "first is greater - ok\n";

 if( bitset_equal(   bitset_union( bitset_from_string( "000100110010110010101110011001110111" ),
                                   bitset_from_string( "001100000110101100110011100101100101000110101110010101011011001" )
                                        ),
                     bitset_from_string (              "001100110110111110111111111101110111000110101110010101011011001"   )
                 )
   )
      echo "second is greater - ok\n";
?>
--EXPECT--
empty input - ok
first is empty - ok
second is empty - ok
same length - ok
first is greater - ok
second is greater - ok
