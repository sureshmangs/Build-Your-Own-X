# JSON Parser

The JSON Parser does the parsing and validation of data in a format resembling JSON. It starts by breaking down the input data into individual tokens through lexical analysis. Then, it proceeds to parse and validate the data structure, ensuring that it conforms to the expected JSON-like format. It ultimately determines whether the input data is "VALID JSON" or "INVALID JSON" based on the correctness of its structure.


## How to Run

**Step 1: Compilation**
   
Open the terminal and navigate to the root directory containing the code files (driver.cpp, lexer.cpp, parser.cpp etc.).

Use a C++ compiler such as g++ to compile the code. Here's the compilation command:

```bash
g++ -o json_parser common.cpp driver.cpp lexer.cpp parser.cpp
```

This command compiles the code files into an executable named "json_parser".

**Step 2: Execution**

After successful compilation, you can run the executable by providing a JSON-like data file as input. The code also allows for an optional flag to display tokenization and parsing data. Here's the command to run the code:

```bash
./json_parser <fileName> [displayData]
```

- `<fileName>`: Replace this with the name of the JSON-like data file you want to parse. Make sure the file is in the same directory as the executable or provide the full path to the file.

- `[displayData]`: This is an optional argument. If you include it, the code will display tokenization and parsing data as it processes the file. You can use any numeric value (e.g., 1) as an argument to enable data display. If you omit this argument, no data will be displayed except for the JSON validation result.

**Step 3: Interpret the Output**

   - If the code successfully parses and validates the JSON-like data in the input file, it will display "VALID JSON" on the terminal.

   - If the JSON-like data is invalid (e.g., it doesn't adhere to the expected JSON structure), the code will display "INVALID JSON."

   - If you included the optional argument for data display, the code will also provide tokenization and parsing details, making it easier to understand how the data was processed.


## Example Usage:

The input file `inputFile.txt` has the following data:

```plain
{
    "JSON Test Pattern pass3": {
        "The outermost value": "must be an object or array.",
        "In this test": 123       
    }
}
```

To check whether the `inputFile.txt` has valid or invalid JSON, run the command:
```bash
./json_parser inputFile.txt 1
```

The output will be:

```plain
Tokenization:
-------------------------------
LEFTCURLYBRACKET : {
STRINGVALUE : "JSON Test Pattern pass3"
COLON : :
LEFTCURLYBRACKET : {
STRINGVALUE : "The outermost value"
COLON : :
STRINGVALUE : "must be an object or array."
COMMA : ,
STRINGVALUE : "In this test"
COLON : :
NUMBER : 123
RIGHTCURLYBRACKET : }
RIGHTCURLYBRACKET : }
-------------------------------

Parsing:
-------------------------------
{
"JSON Test Pattern pass3"
:
{
"The outermost value"
:
"must be an object or array."
,
"In this test"
:
123
}
}
-------------------------------

VALID JSON
```


# How to run tests

Open the terminal and navigate to the root directory containing the code files (driver.cpp, lexer.cpp, parser.cpp etc.). Run the following command:

```bash
./runtests.bash
```

The ouput will be:

```plain
Processing file: ./tests//fail01.json
INVALID JSON
Processing file: ./tests//fail02.json
INVALID JSON
Processing file: ./tests//fail03.json
INVALID JSON
Processing file: ./tests//fail04.json
INVALID JSON
Processing file: ./tests//fail05.json
INVALID JSON
Processing file: ./tests//fail06.json
INVALID JSON
Processing file: ./tests//fail07.json
INVALID JSON
Processing file: ./tests//fail08.json
INVALID JSON
Processing file: ./tests//fail09.json
INVALID JSON
Processing file: ./tests//fail10.json
INVALID JSON
Processing file: ./tests//fail11.json
INVALID JSON
Processing file: ./tests//fail12.json
INVALID JSON
Processing file: ./tests//fail13.json
INVALID JSON
Processing file: ./tests//fail14.json
INVALID JSON
Processing file: ./tests//fail15.json
INVALID JSON
Processing file: ./tests//fail16.json
INVALID JSON
Processing file: ./tests//fail17.json
INVALID JSON
Processing file: ./tests//fail18.json
INVALID JSON
Processing file: ./tests//fail19.json
INVALID JSON
Processing file: ./tests//fail20.json
INVALID JSON
Processing file: ./tests//fail21.json
INVALID JSON
Processing file: ./tests//fail22.json
INVALID JSON
Processing file: ./tests//fail23.json
INVALID JSON
Processing file: ./tests//fail24.json
INVALID JSON
Processing file: ./tests//fail25.json
INVALID JSON
Processing file: ./tests//fail26.json
INVALID JSON
Processing file: ./tests//fail27.json
INVALID JSON
Processing file: ./tests//fail28.json
INVALID JSON
Processing file: ./tests//fail29.json
INVALID JSON
Processing file: ./tests//fail30.json
INVALID JSON
Processing file: ./tests//fail31.json
INVALID JSON
Processing file: ./tests//fail32.json
INVALID JSON
Processing file: ./tests//fail33.json
INVALID JSON
Processing file: ./tests//fail34.json
INVALID JSON
Processing file: ./tests//pass1.json
VALID JSON
Processing file: ./tests//pass2.json
VALID JSON
Processing file: ./tests//pass3.json
VALID JSON
*************************************
Number of test cases        : 37
Number of test cases passed : 37
Number of test cases failed : 0
```


## Code flow:

```plain
main() in driver.cpp
				--> lexer() in lexer.cpp
                --> parser() in parse.cpp
```


## Write Your Own JSON Parser

This challenge is to build your own JSON parser.

This challenge corresponds to the "Write Your Own JSON Parser" [Coding Challenges series by John Crickett](https://codingchallenges.fyi/challenges/challenge-json-parser).