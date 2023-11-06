#!/bin/bash

# Check if the 'huffman' executable exists
if [ ! -x ./huffman ]; then
  echo "Error: 'huffman' executable not found or not executable."
  exit 1
fi

# Check if the 'diff' command is available
if ! command -v diff &> /dev/null; then
  echo "Error: 'diff' command not found. Please install 'diff' on your system."
  exit 1
fi

# Specify the folder containing the files
folder="./tests/"

# Check if the folder exists
if [ ! -d "$folder" ]; then
  echo "Error: Folder '$folder' does not exist."
  exit 1
fi

# Initialize counters for pass and failed cases
total_cases=0
correct_result=0
incorrect_result=0

# Loop through all files in the folder and execute 'huffman' for each file
for filename in "$folder"/*; do
  if [ -f "$filename" ]; then
    echo "Processing file: $filename"
    out1=$(./huffman -c "$filename" "compressed.bin")
    echo $out1
    out2=$(./huffman -d "compressed.bin" "original.txt")
    echo $out2
    output=$(diff "$filename" "original.txt")

    # Check if the output is empty (no differences found)
    if [ -z "$output" ]; then
      ((correct_result++))
    else
      ((incorrect_result++))
    fi

    echo $output
    ((total_cases++))
  fi
done

# Print the counts
echo "*************************************"
echo "Number of test cases        : $total_cases"
echo "Number of test cases passed : $correct_result"
echo "Number of test cases failed : $incorrect_result"
