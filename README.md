# Bank Management System

A console-based **Bank Management System** developed in C++ as part of my learning journey in Algorithms & Problem Solving.

The project provides a simple system for managing bank clients and their account information using file-based data storage.

## Features

* Display all clients
* Add new clients
* Delete existing clients
* Update client information
* Search for a client by account number
* Prevent duplicate account numbers
* Store and load client data using files
* Persist changes between program runs
* Interactive console-based menu

## Client Information

Each client record contains:

* Account Number
* PIN Code
* Name
* Phone Number
* Account Balance

## Technologies & Concepts

* C++
* Structures (`struct`)
* Vectors (`vector`)
* File Handling
* String Manipulation
* Functions
* Enumerations (`enum`)
* Input/Output Streams
* Data Serialization & Deserialization
* Searching and Updating Records

## Data Storage

Client information is stored in a text file named:

`ClientData.txt`

Records are converted between structured data and text using a custom separator:

`#//#`

This allows the program to save structured client information to the file and reconstruct it when the program starts.

## Main Menu

The system provides the following options:

1. Show Client List
2. Add New Client
3. Delete Client
4. Update Client Information
5. Find Client
6. Exit

## Project Goal

The main goal of this project was to practice building a complete console application while strengthening my understanding of **data structures, functions, file handling, searching, updating records, and organizing a larger C++ program into reusable components**.

This project represents another step in my journey toward becoming a professional software developer.
