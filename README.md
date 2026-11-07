# Inverted Search in C

## Project Overview

Inverted Search is a C programming project that implements an efficient word-searching mechanism using a hash table and linked lists. It indexes words from multiple text files and stores the filenames in which each word appears, along with its frequency.

The project enables users to create, display, search, save, and update the database, making word retrieval from multiple files more efficient.

## Features

* **Create Database:** Extracts words from multiple text files and creates an indexed database.
* **Display Database:** Displays indexed words, filenames, and word frequencies.
* **Search Word:** Searches for a specific word and displays the files containing it.
* **Save Database:** Stores the indexed database in a file for future use.
* **Update Database:** Reconstructs the database from a previously saved database file.
* **File Validation:** Validates input files and avoids processing duplicate files.

## Technologies Used

* Programming Language: C
* Data Structures: Hash Table, Singly Linked Lists
* Concepts: Pointers, Dynamic Memory Allocation, String Manipulation, File Handling
* Development Environment: Linux
* Build Tool: Makefile

## Project Structure

text
inverted_index/
├── main.c
├── main.h
├── create.c
├── display.c
├── search.c
├── save.c
├── update.c
├── validaton.c
├── makefile
├── .gitignore
└── README.md

## Compilation

Clone the repository:

bash
git clone https://github.com/giri1418/invertedsearch

Navigate to the project directory:

bash
cd inverted-search

Compile the project using the Makefile:

bash
make

If your Makefile uses a different target or does not generate `a.out`, follow the build instructions defined in your Makefile.
## Execution

Run the compiled executable with the input text files:

bash
./a.out f1.txt f2.txt f3.txt

Replace the filenames with your actual input files.

The application displays a menu to perform database operations.

## Concepts Learned

* Implementation of hash tables for efficient word indexing.
* Linked-list operations for storing words and associated file information.
* Dynamic memory allocation and pointer management.
* File handling to read input files and save or restore the database.
* Input validation and duplicate-file handling.
* Modular programming using multiple C source files.

## Author

**Kancharla Giri Babu**

GitHub: https://github.com/giri1418/invertedsearch