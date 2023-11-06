# Huffman Encoder Decoder

The Huffman compression and decompression utility designed to efficiently compress and decompress text data. It performs the compression and decompression of files using the Huffman coding algorithm, a popular method for data compression.

## How to Run

**Step 1: Compilation**

Open the terminal and navigate to the root directory containing the code files (driver.cpp, etc.).

Use a C++ compiler such as g++ to compile the code. Here's the compilation command:

```bash
g++ common.cpp compress.cpp decompress.cpp driver.cpp -o huffman
```

This command compiles all the source files into an executable named "huffman."

**Step 2: Execution**

After successful compilation, you can run the program by executing the following command:

- For compression:

  ```bash
  ./huffman -c <sourceFileName> <destinationFileName> [displayData]
  ```

- For decompression:

  ```bash
  ./huffman -d <sourceFileName> <destinationFileName> [displayData]
  ```

- Replace `sourceFileName` with the name of the file you want to compress or decompress.
- Replace `destinationFileName` with the name of the file where you want to store the compressed or decompressed data.
- The optional `displayData` argument can be added to display information about the compression or decompression process. You can choose to include it or leave it out.


## Example Usage:

The input file `inputFile.txt` has the following data:

```plain
The Project Gutenberg eBook of Les Misérables, by Victor Hugo

This eBook is for the use of anyone anywhere in the United States and
most other parts of the world at no cost and with almost no restrictions
whatsoever. You may copy it, give it away or re-use it under the terms
of the Project Gutenberg License included with this eBook or online at
www.gutenberg.org. If you are not located in the United States, you
will have to check the laws of the country where you are located before
using this eBook.

Title: Les Misérables
Complete in Five Volumes
```

To compress the `inputFile.txt` to `compressedFile.bin`, run the command:
```bash
./huffman -c inputFile.txt compressedFile.bin 1
```

The output will be (a new file `compressedFile.bin` will be generated):

```plain
Perform compression
Display frequency of characters:
Total unique characters: 44
  : 89
, : 3
- : 1
. : 5
: : 1
B : 4
C : 1
EOL : 12
F : 1
G : 2
H : 1
I : 1
L : 3
M : 2
P : 2
S : 2
T : 3
U : 2
V : 2
Y : 1
a : 22
b : 7
c : 13
d : 10
e : 61
f : 8
g : 8
h : 20
i : 27
j : 2
k : 5
l : 14
m : 6
n : 24
o : 45
p : 3
r : 27
s : 26
t : 45
u : 15
v : 4
w : 12
y : 10
é : 2
Display huffman tree:
n  m  p  P  S  c  s  i  r  l  b  U  V  C  F  H  I  e  u  f  g  G  M  j  é  B  v  .  k  d  h  y  Y  -  :  ,  L  T  o     t  a  EOL  w 
Display binary codes for characters:
  : 110
, : 10101101
- : 1010110010
. : 1001100
: : 1010110011
B : 1001010
C : 010111100
EOL : 111110
F : 010111101
G : 10010000
H : 010111110
I : 010111111
L : 10101110
M : 10010001
P : 00010110
S : 00010111
T : 10101111
U : 01011100
V : 01011101
Y : 101011000
a : 11110
b : 010110
c : 00011
d : 100111
e : 011
f : 100010
g : 100011
h : 10100
i : 0011
j : 10010010
k : 1001101
l : 01010
m : 000100
n : 0000
o : 1011
p : 0001010
r : 0100
s : 0010
t : 1110
u : 10000
v : 1001011
w : 111111
y : 101010
é : 10010011
The length of the longest codes is:10
Compression complete
Size of inputFile.txt : 555 bytes
Size of compressedFile.bin : 472 bytes
```

To decompress the `compressedFile.bin` to `originalFile.txt`, run the command:
```bash
./huffman -d compressedFile.bin originalFile.txt 1
```

The output will be (a new file `originalFile.txt` will be generated):

```plain
Perform de-compression
Display frequency of characters:
Total unique characters: 44
  : 89
, : 3
- : 1
. : 5
: : 1
B : 4
C : 1
EOL : 12
F : 1
G : 2
H : 1
I : 1
L : 3
M : 2
P : 2
S : 2
T : 3
U : 2
V : 2
Y : 1
a : 22
b : 7
c : 13
d : 10
e : 61
f : 8
g : 8
h : 20
i : 27
j : 2
k : 5
l : 14
m : 6
n : 24
o : 45
p : 3
r : 27
s : 26
t : 45
u : 15
v : 4
w : 12
y : 10
é : 2
Display huffman tree:
n  m  p  P  S  c  s  i  r  l  b  U  V  C  F  H  I  e  u  f  g  G  M  j  é  B  v  .  k  d  h  y  Y  -  :  ,  L  T  o     t  a  EOL  w De-compression complete
Size of compressedFile.bin : 472 bytes
Size of originalFile.txt : 555 bytes
```


# How to run tests

Open the terminal and navigate to the root directory containing the code files (driver.cpp, etc.). Run the following command:

```bash
./runtests.bash
```

The ouput will be:

```plain
Processing file: ./tests//UT_01.txt
Size of ./tests//UT_01.txt : 3295453 bytes Size of compressed.bin : 1883549 bytes
Size of compressed.bin : 1883549 bytes Size of original.txt : 3295453 bytes

Processing file: ./tests//UT_02.txt
Size of ./tests//UT_02.txt : 49 bytes Size of compressed.bin : 118 bytes
Size of compressed.bin : 118 bytes Size of original.txt : 49 bytes

Processing file: ./tests//UT_03.txt
Size of ./tests//UT_03.txt : 287 bytes Size of compressed.bin : 215 bytes
Size of compressed.bin : 215 bytes Size of original.txt : 287 bytes

Processing file: ./tests//UT_04.txt
Size of ./tests//UT_04.txt : 1746 bytes Size of compressed.bin : 1158 bytes
Size of compressed.bin : 1158 bytes Size of original.txt : 1746 bytes

*************************************
Number of test cases        : 4
Number of test cases passed : 4
Number of test cases failed : 0
```


## Code flow:

```plain
main() in driver.cpp
	--> compress() in compress.cpp
        --> decompress() in decompress.cpp
```


**common.cpp:**

- File "common.cpp" contains essential functions and definitions used by the compression and decompression processes.
- Functions include counting the number of bytes in a file, building the Huffman tree, and displaying the Huffman tree.
- It also sets up global variables for controlling the display of compression and decompression information.

**compress.cpp:**

- File "compress.cpp" is responsible for the compression process.
- It calculates the frequency of characters in the input file, constructs a Huffman tree, generates binary codes for each character, and writes the compressed data to the destination file.


**decompress.cpp:**

- File "decompress.cpp" is dedicated to the decompression process.
- It reads the header of the compressed file to compute the character frequencies, rebuilds the Huffman tree, and decodes the compressed data to reconstruct the original file.

**driver.cpp:**

- File "driver.cpp" serves as the main driver program for the entire utility.
- It parses command-line arguments, triggers compression or decompression based on user preferences, and displays information about the size of source and destination files.
- This file acts as the user interface for the compression and decompression operations, ensuring proper execution and data display.


## Write Your Own Compression Tool

This challenge is to build your own compression tool.

This challenge corresponds to the "Write Your Own Compression Tool" [Coding Challenges series by John Crickett](https://codingchallenges.fyi/challenges/challenge-huffman).