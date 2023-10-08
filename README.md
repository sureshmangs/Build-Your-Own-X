# Build Your Own X

## [Write Your Own wc Tool](ccwc/C%2B%2B)

ccwc counts various statistics of a text file, such as the number of lines, words, characters, and bytes. It takes command-line arguments to specify the operation and the file to be analyzed.

It supports four different options:

1. `-l`: Count the number of lines in the input file.
2. `-w`: Count the number of words in the input file.
3. `-c`: Count the number of bytes in the input file.
4. `-m`: Count the number of characters in the input file (same as `-c` if the current locale does not support multibyte characters).

It also handles input from standard input (stdin) if no fileName is specified.


## [Write Your Own JSON Parser](JSON-Parser/C%2B%2B)

The JSON Parser does the parsing and validation of data in a format resembling JSON. It starts by breaking down the input data into individual tokens through lexical analysis. Then, it proceeds to parse and validate the data structure, ensuring that it conforms to the expected JSON-like format. It ultimately determines whether the input data is "VALID JSON" or "INVALID JSON" based on the correctness of its structure.

