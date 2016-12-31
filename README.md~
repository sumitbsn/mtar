# mtar
mtar is a sort implementation of GNU tar. It's a Unix/Linux Utility to compress and decompress a Directory containing subdirectories and or files.

Compression using “mtar” :
The mtar utility should support the 2 compression techniques described below -

1. Run-length compression Expands on the null compression technique by compressing any series of four or more repeating characters. The characters are replaced with a compression code, one of the characters, and a value that represents the number of characters to repeat.
To invoke the program –
$mtar –rl <input folder path>
“rl” option to run-length compression
Example 1:
Input File Content –
WWWWEEaaaabrrrrrrrrrrxxabcdeeee
Output/Compressed File Content –
4W2E4ab10r2xabcd4e
Example 2–
Input File Content –
aaaaaaBB     xZZZZqqqeVVVVVV
Output/Compressed File Content –
6a2B5 x4Z3q3e6V
Note – Here “5 “ is used to represent 5 spaces

2. Keyword encoding Creates a table with values that represent common sets of characters. Frequently occurring words like for and the or character pairs like sh or th are represented with tokens used to store or represent the characters.
To invoke the program –
$mtar –ke <input folder path>
“ke” option to run key word encoding
Example –
Key words table (dummy table created only for example) –
Key words		Unique Value
the 				 $1
and 				 $2
for 				 $3
will 				 $4
this 				 $5
from 				 $6
that 				 $7
with 				 $8
them 				 $9
which  				 $10
does 				 $11

Input File Content –
This example does a couple of things that haven't been met before. The Read() function is used as an alternative to the line-by-line input done with the diamond operator. It will read a specified number of bytes from the input file and assign them to a buffer variable. The fourth parameter specifies an offset at which to start reading. In this example, we started at the beginning of the file.
Output/Compressed File Content –
$5 example $11 a couple of things $7 haven't been met before. The Read() function is used as an alternative to $1 line-by-line input done $8 $1 diamond operator. It $4 read a specified number of bytes $6 the input file and assign $9 to a buffer variable. $1 fourth parameter specifies an offset at $10 to start reading. In $5 example, we started at the beginning of $1 file. Note – For all three compression techniques if there are numeric values in the file to be compressed then a “\” character has to be placed before each numeric character.
Example –
Input File Content –
123WWWW
Output/Compressed File Content –
\1\2\34W

The compressed files are placed in a folder created with the name as the input folder suffixed with mtar.
For example - $mtar –ke /home/test/project
Here the compressed files are placed under /home/test/projectmtar

UnCompression using “mtar”:
The user should be able to uncompress/retrieve the original files by using the mtar utility.
To invoke the program –
$mtar <compressed folder path>
Ex – $ mtar /home/test/projectmtar
Here the mtar utility should check which compression technique was used for compression and then uncompress files accordingly.













