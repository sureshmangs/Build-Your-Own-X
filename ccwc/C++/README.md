# ccwc

ccwc counts various statistics of a text file, such as the number of lines, words, characters, and bytes. It takes command-line arguments to specify the operation and the file to be analyzed.

It supports four different options:

1. `-l`: Count the number of lines in the input file.
2. `-w`: Count the number of words in the input file.
3. `-c`: Count the number of bytes in the input file.
4. `-m`: Count the number of characters in the input file (same as `-c` if the current locale does not support multibyte characters).

It also handles input from standard input (stdin) if no fileName is specified.


## How to Run

To compile and run this C++ program, follow these steps:

1. Make sure you have a C++ compiler installed on your system (e.g., g++ for Unix-like systems or Visual C++ for Windows).

2. Save the code to a file with a `.cpp` extension, such as `ccwc.cpp`.

3. Open a terminal or command prompt and navigate to the directory where you saved the code.

4. Compile the code using the C++ compiler. For example, if you are using g++, you can compile the code with the following command:

   ```bash
   g++ -o ccwc ccwc.cpp
   ```
   This command compiles the code and generates an executable file named `ccwc`.

5. After successful compilation, you can run the program using one of the following formats:

   - To count lines, words, or bytes in a file:

     ```bash
     ./ccwc -l/-w/-c/-m fileName
     ```

     Replace `-l`, `-w`, `-c`, or `-m` with the desired option, and `fileName` with the path to the text file you want to analyze.

   - To read input from stdin and count lines, words, or bytes:

     ```bash
     cat fileName.txt | ./ccwc -l/-w/-c/-m
     ```

     Replace `-l`, `-w`, `-c`, or `-m` with the desired option and provide input through stdin.

6. The program will execute the selected operation and display the result on the terminal.


## Example Usage:

- To count the number of lines in a file named `inputFile.txt`:

  ```bash
  ./ccwc -l inputFile.txt
  ```

- To count the number of words in a file named `inputFile.txt`:

  ```bash
  ./ccwc -w inputFile.txt
  ```

- To count the number of bytes in a file named `inputFile.txt`:

  ```bash
  ./ccwc -c inputFile.txt
  ```

- To count the number of characters in a file named `inputFile.txt`:

  ```bash
  ./ccwc -m inputFile.txt
  ```

- To read input from stdin and count the number of lines:

  ```bash
  cat inputFile.txt | ./ccwc -l
  ```

- To read input from stdin and count the number of words:

  ```bash
  cat inputFile.txt | ./ccwc -w
  ```

- To read input from stdin and count the number of bytes:

  ```bash
  cat inputFile.txt | ./ccwc -c
  ```

- To read input from stdin and count the number of characters:

  ```bash
  cat inputFile.txt | ./ccwc -m
  ```

## How to run command directly from terminal

To run the `ccwc -c fileName.txt` command directly from the terminal (i.e. if you want to run it as `ccwc -c fileName.txt` instead of `./ccwc -c fileName.txt`), you need to make your C++ program executable and ensure it's available in your system's PATH.

Here's how you can do it:

  1. Save the C++ code into a file, for example, `ccwc.cpp`.

  2. Compile the program using `g++` and create an executable file. You can do this in the terminal:
  
      ```shell
      g++ ccwc.cpp -o ccwc
      ```

		This command will compile your C++ code into an executable named `ccwc`.

  3. Move the `ccwc` executable to a directory that is in your system's PATH. You can determine your PATH by running:

      ```shell
      echo $PATH
      ```

      Common directories for user binaries include `/usr/local/bin`, `/usr/bin`, or `~/bin`. Choose one and move the `ccwc` executable there. For example:

      ```shell
      sudo mv ccwc /usr/local/bin/
      ```

      Replace `/usr/local/bin/` with your preferred directory if necessary, and use `sudo` if you need administrative privileges.

  4. After moving the executable, you should be able to run the `ccwc -c fileName.txt` command directly from the terminal:

      ```shell
      ccwc -c fileName.txt
      ```

      Now, the `ccwc` command should be available in your terminal.


## Write your own wc tool

This challenge is to build your own version of the Unix command line tool wc!

This challenge corresponds to the "Write Your Own wc Tool" [Coding Challenges series by John Crickett](https://codingchallenges.fyi/challenges/challenge-wc).