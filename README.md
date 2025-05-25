# Library Management System

A **C-based application** designed to manage book loans in a library context. This system helps librarians track books, borrowers, and loan transactions with **priority-based handling**.

---

## 🚀 Features

### 📚 Book Management
- Add new books with title, author, and copies
- Remove books by ID or title
- Search books by ID or title
- Display all available books

### 👤 Borrower Management
- Add new borrower records
- Remove borrowers by ID or name
- Search borrowers by ID or name
- Display all registered borrowers

### 🔄 Loan Management
- Process new book loans
- Handle book returns
- View active loans
- Display overdue books
- View return history

### 🏷️ Priority-Based Loan Handling
- **Overdue loans** (highest priority)
- **High priority** (due within 7 days)
- **Medium priority** (due within 14 days)
- **Low priority** (all other active loans)

### 📂 Data Import/Export
- Load books from `books.txt`
- Load borrowers from `borrowers.txt`
- Import loan transactions from `loans.txt`

---

## 🛠️ System Requirements

- C compiler (**GCC** recommended)
- Standard C libraries

---

## ⚙️ Compilation

Compile the program using GCC:

```bash
gcc -Wall -Wextra -std=c99 main.c library.c libtime.c -o library_system
```
# 📊 Data Model

This system uses structured linked list data models to represent books, borrowers, and loan transactions.

## 📖 Book Records

Each book record includes:
- **Book ID**: Unique identifier for the book
- **Title**: Up to 64 characters
- **Author**: Up to 32 characters
- **Available Copies Count**: Tracks current inventory
- **Linked List Pointers**: For managing book records in a list

## 👥 Borrower Records

Each borrower record includes:
- **Borrower ID**: Unique identifier for the borrower
- **Name**: Up to 32 characters
- **Linked List Pointers**: For managing borrower records

## 🔁 Loan Transactions

Each loan transaction record includes:
- **Book ID Reference**: Links to the borrowed book
- **Borrower ID Reference**: Links to the borrower
- **Due Date**: Format `YYYY-MM-DD`
- **Priority Level**:
  - `O`: Overdue
  - `H`: High (due within 7 days)
  - `M`: Medium (due within 14 days)
  - `L`: Low (more than 14 days left)
- **Queue Pointers**: For managing loans in a priority queue

---

# 🔄 Workflow

This system is designed for daily operations and data management within a library setting.

## 📅 Daily Operations

- **Process New Book Loans**: Assign books to borrowers, update availability
- **Handle Book Returns**: Mark books as returned, update inventory
- **Check for Overdue Books**: Identify and prioritize overdue returns
- **Update Inventory Counts**: Reflect real-time availability of books

## 📈 Reporting

- **Generate Real-Time Statistics**: Number of active loans, overdue books, etc.
- **Create Visual Reports**: Generate SVG format charts for analysis
- **View Current Loan Statuses**: Track all ongoing transactions with priority

## 📦 Data Management

- **Import/Export Book and Borrower Records**: Load from or save to text files
- **Load/Save Loan Transactions**: Persist loan data across sessions
- **Maintain Sorted Data Structures**: For efficient search and retrieval


## Contributors

 by **SidAli BEGGAR** and **Souhail EL FRAIHI**  

- We worked collaboratively on designing, implementing, and testing a library loan management system in C using linked lists, modular file structure, and terminal-based user interaction.
- This project was developed as part of **Practical Work N°1: Linked List Implementation (ALSDD)** in the context of a university course (Algorithms and Advanced Data Structures)
- This project was submitted as part of an academic practical lab exercise and is intended for educational use only.

