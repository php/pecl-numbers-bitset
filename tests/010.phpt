--TEST--
bitset_subset
--SKIPIF--
<?php  if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
 if( bitset_subset(bitset_empty(), bitset_empty())  )
      echo "empty input - ok\n";

 if( bitset_subset(bitset_empty(), bitset_from_string( "000000000000000000000000000000000000" ) )  )
      echo "first empty, second zero - ok\n";

 if( !bitset_subset(bitset_empty(), bitset_from_string( "001100000110101100110011100101100101" ) )  )
      echo "first empty, second non-zero - ok\n";

 if( bitset_subset(bitset_from_string( "001100000110101100110011100101100101" ), bitset_empty())  )
      echo "second empty - ok\n";

 
 if( bitset_subset( bitset_from_string( "0011011011001100" ),
                    bitset_from_string( "0001010000001100" )
                  )
   )
      echo "size equal, result true - ok\n";

 
 if( !bitset_subset( bitset_from_string( "0011011011001100" ),
                     bitset_from_string( "0001010000101100" )
                   )
   )
      echo "size equal, result false - ok\n";


 if( bitset_subset( bitset_from_string( "001101101100110000110101100" ),
                    bitset_from_string( "0001010000001100" )
                  )
   )
      echo "first greater, result true - ok\n";

 
 if( !bitset_subset( bitset_from_string( "001101101100110000110101100" ),
                     bitset_from_string( "0001010000101100" )
                   )
   )
      echo "first greater, result false - ok\n";




 if( bitset_subset( bitset_from_string( "0011011011001100" ),
                    bitset_from_string( "00010100000011000000000000000000000000000" )
                  )
   )
      echo "second greater, result true - ok\n";



 if( !bitset_subset( bitset_from_string( "0011011011001100" ),
                     bitset_from_string( "01010100000011000000000000000000000000000" )
                   )
   )
      echo "second greater, result false by the base part - ok\n";


 if( !bitset_subset( bitset_from_string( "0011011011001100" ),
                     bitset_from_string( "00010100000011000000000001000001000000000" )
                   )
   )
      echo "second greater, result false by the rest - ok\n";


      
 if( !bitset_subset( bitset_from_string( "0011011011001100" ),
                     bitset_from_string( "00010100001011000000000001000000100000000" )
                   )
   )
      echo "second greater, result false (by both parts) - ok\n";

?>
--EXPECT--
empty input - ok
first empty, second zero - ok
first empty, second non-zero - ok
second empty - ok
size equal, result true - ok
size equal, result false - ok
first greater, result true - ok
first greater, result false - ok
second greater, result true - ok
second greater, result false by the base part - ok
second greater, result false by the rest - ok
second greater, result false (by both parts) - ok
