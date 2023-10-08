# Notes

## How to copy control characters

For copying control characters to to clipboard use: [RapidTables](https://www.rapidtables.com/convert/number/hex-to-ascii.html)

Use the following settings:

- From: Hexadecimal

- To: Text

- Character encoding : ASCII

- Add a hex number in the "Paste hex numbers or drop file" section.

- Click on convert button and then click on copy button to copy text to clipboard, i.e: Enter 0b to get a copyable representation of the Vertical Tab character.


## How to use global variables in two different files in C++?

In C++, global variables can be used across different files by using the `extern` keyword. To achieve this, you need to follow these steps:

1. Declare the global variable in one file.
2. Include a header file that contains the declaration of the global variable in other files where you want to use it.
3. Define the global variable in one source file (usually the same file where it's declared), and use the `extern` keyword to declare it as "extern" in other files.

Here's a step-by-step example:

Suppose you have two source files: `main.cpp` and `other.cpp`, and you want to use a global variable `myGlobalVar` in both of them.

1. Create a header file (e.g., `globals.h`) to declare the global variable:

```cpp
// globals.h
extern int myGlobalVar;
```

2. In the source file where you want to define the global variable (e.g., `main.cpp`), define and initialize it:

```cpp
// main.cpp
#include "globals.h"

int myGlobalVar = 42;

int main() {
    // Use myGlobalVar here
    return 0;
}
```

3. In the source file where you want to use the global variable (e.g., `other.cpp`), include the header file and use the `extern` keyword to declare it:

```cpp
// other.cpp
#include "globals.h"

void someFunction() {
    // Use myGlobalVar here
}
```

4. Compile both source files and link them together into an executable:

```bash
g++ -o myprogram main.cpp other.cpp
```

Now, you can use `myGlobalVar` in both `main.cpp` and `other.cpp`, and changes made to it in one file will affect its value in the other file.


## What are control characters?

Control characters are characters that do not represent printable symbols but instead serve to control or manipulate the appearance and behavior of text. These characters are typically not visible when rendered or printed and are used for various purposes, such as formatting, signaling, and control.

Some common escape characters include:

1. **Newline (Line Feed)** - `\n`:
   - This character is used to start a new line of text. It's commonly used to create line breaks in text files.

2. **Carriage Return** - `\r`:
   - Historically, this character was used in combination with newline to move the cursor to the beginning of a line, allowing text to be overwritten. In modern systems, it is often used to represent the end of a line.

3. **Tab** - `\t`:
   - This character is used to create horizontal tab stops in text. It's commonly used for indentation and aligning text.

4. **Backspace** - `\b`:
   - This character is used to move the cursor or text one position backward, effectively erasing the previous character.

5. **Form Feed** - `\f`:
   - Form feed is used to start a new page in documents or other text files. It's less commonly used in modern contexts.

6. **Escape** - `\e` or `\x1B`:
   - The escape character is often used as the start of control sequences in terminal and console applications, allowing for various text formatting and control operations.

7. **Null** - `\0`:
   - The null character represents the end of a string in C and C++ programming. It's not typically used for formatting but is used to terminate strings.

8. **Vertical Tab** - `\v`:
   - Vertical tab is used to create vertical tab stops. It's less commonly used in modern contexts.

9. **Alert (Bell)** - `\a`:
   - The alert character can be used to produce an audible alert, such as a beep sound, in some terminal environments.

10. **Non-Breaking Space** - `\xA0`:
    - Non-breaking space is a character used to prevent line breaks or word wrapping at that position. It's often used in word processing and typesetting.

These escape characters are essential for controlling the formatting and behavior of text in various contexts, including programming languages, text editors, and document processing systems. Depending on the context, different control characters may have different meanings and effects.


## What are escape characters?

Escape characters are special characters used in strings and text to represent characters that are difficult or impossible to represent directly. These characters typically start with a backslash `\` followed by one or more characters and are used to encode non-printable or special characters, such as newline, tab, or quotation marks, within a string. Escape characters are commonly used in programming languages, regular expressions, and markup languages like HTML and XML.

Here are some common escape characters and their meanings:

1. **\n** - Newline:
   - Represents a line break or a new line in a string.

2. **\t** - Tab:
   - Represents a horizontal tab character, used for indentation or alignment.

3. **\r** - Carriage Return:
   - Represents the return or enter key, often used in combination with `\n` to represent a newline.

4. **\b** - Backspace:
   - Represents the backspace key, used to move the cursor or text one position backward.

5. **\"** - Double Quotation Mark:
   - Represents a double quotation mark within a string when the string itself is enclosed in double quotes.

6. **\'** - Single Quotation Mark (Apostrophe):
   - Represents a single quotation mark within a string when the string itself is enclosed in single quotes.

7. **\\** - Backslash:
   - Represents a literal backslash character within a string.

8. **\x** - Hexadecimal Escape:
   - Allows you to specify a character using its hexadecimal ASCII code. For example, `\x41` represents the letter 'A'.

9. **\u** - Unicode Escape:
   - Allows you to specify a character using its Unicode code point in hexadecimal format. For example, `\u00A9` represents the copyright symbol (©).

10. **\0** - Null Character:
    - Represents the null character, often used as a string terminator in some programming languages.

Escape characters are essential for handling special characters and formatting within strings while still being able to represent them in a human-readable way. They are used to prevent ambiguity and ensure that the desired characters are correctly interpreted by a program or language parser.


## In JSON, will a single quotation marked be a valid escape character?

No, in JSON, the single quotation mark (`'`) is not a valid escape character. JSON uses a specific set of escape characters, and the single quotation mark is not one of them.

In JSON, the valid escape characters are:

1. `\"` - Represents a double quotation mark (`"`).
2. `\\` - Represents a backslash (`\`).
3. `\/` - Represents a forward slash (`/`).
4. `\b` - Represents a backspace character.
5. `\f` - Represents a form feed character.
6. `\n` - Represents a newline character.
7. `\r` - Represents a carriage return character.
8. `\t` - Represents a tab character.
9. `\uXXXX` - Represents a Unicode character where `XXXX` is a 4-digit hexadecimal code point.

Single quotation marks (`'`) are not included in this list, and they do not have special meaning as escape characters in JSON. If you want to represent a single quotation mark within a JSON string, you should simply include it without any escaping.