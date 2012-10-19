--TEST--
bitset_invert
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
 if( bitset_to_string(  bitset_invert(bitset_empty(), 0)   ) == ""  )
      echo "empty input, zero base invert - ok\n";


 if( bitset_to_string(  bitset_invert(bitset_from_string("00110110111001"), 0)   ) == ""  )
      echo "non-empty input, zero base invert - ok\n";


 if( bitset_to_string(  bitset_invert(bitset_empty(), 3)   ) == "11100000"  )
      echo "empty input, non-zero base invert - ok\n";


 if( bitset_to_string(  bitset_invert(bitset_empty(), 8)   ) == "11111111"  )
      echo "empty input, non-zero aligned base invert 1 - ok\n";
 

 if( bitset_to_string(  bitset_invert(bitset_empty(), 9)   ) == "1111111110000000"  )
      echo "empty input, non-zero aligned base invert 2 - ok\n";


 
 if( bitset_to_string(  bitset_invert(bitset_from_string("0011011011100010"), 42)   ) == "110010010001110111111111111111111111111111000000"  )
      echo "non-empty input (less then size), non-zero base invert - ok\n";


 if( bitset_to_string(  bitset_invert(bitset_from_string("0011011011100010"), 40)   ) == "1100100100011101111111111111111111111111"  )
      echo "non-empty input (less then size), non-zero aligned base invert 1 - ok\n";
 

 if( bitset_to_string(  bitset_invert(bitset_from_string("0011011011100010"), 41)   ) == "110010010001110111111111111111111111111110000000"  )
      echo "non-empty input (less then size), non-zero aligned base invert 2 - ok\n";



 if( bitset_to_string(  bitset_invert(bitset_from_string("0011011011100"), 13)   ) == "1100100100011000"  )
      echo "non-empty input (exact size), non-zero base invert - ok\n";


 if( bitset_to_string(  bitset_invert(bitset_from_string("0011011011100010"), 16)   ) == "1100100100011101"  )
      echo "non-empty input (exact size), non-zero aligned base invert 1 - ok\n";
 

 if( bitset_to_string(  bitset_invert(bitset_from_string("00110110111000100"), 17)   ) == "110010010001110110000000"  )
      echo "non-empty input (exact size), non-zero aligned base invert 2 - ok\n";



 if( bitset_to_string(  bitset_invert(bitset_from_string("0011011011100010"), 7)   )  == "11001000"  )
      echo "non-empty input (greater then size), non-zero base invert - ok\n";


 if( bitset_to_string(  bitset_invert(bitset_from_string("0011011011100010"), 8)   )  == "11001001"  )
      echo "non-empty input (greater then size), non-zero aligned base invert 1 - ok\n";
 

 if( bitset_to_string(  bitset_invert(bitset_from_string("00110110011000100"), 9)   ) == "1100100110000000"  )
      echo "non-empty input (greater then size), non-zero aligned base invert 2 - ok\n";

?>
--EXPECT--
empty input, zero base invert - ok
non-empty input, zero base invert - ok
empty input, non-zero base invert - ok
empty input, non-zero aligned base invert 1 - ok
empty input, non-zero aligned base invert 2 - ok
non-empty input (less then size), non-zero base invert - ok
non-empty input (less then size), non-zero aligned base invert 1 - ok
non-empty input (less then size), non-zero aligned base invert 2 - ok
non-empty input (exact size), non-zero base invert - ok
non-empty input (exact size), non-zero aligned base invert 1 - ok
non-empty input (exact size), non-zero aligned base invert 2 - ok
non-empty input (greater then size), non-zero base invert - ok
non-empty input (greater then size), non-zero aligned base invert 1 - ok
non-empty input (greater then size), non-zero aligned base invert 2 - ok
