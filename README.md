# Library Management System

## 📌 Overview

This project is a **Library Management System** developed in C++ that simulates core library operations. It organizes books into two categories—Fiction and Non-Fiction—and allows users to efficiently manage and interact with the collection through a console-based interface.

The system demonstrates the practical use of fundamental data structures such as linked lists, stacks, and queues to manage different aspects of library functionality.

---

## 🎯 Features

* Add new books with title, author, ISBN, and category
* Remove books using ISBN
* Search for books by title or ISBN
* Borrow books and track borrowing history
* View recently added books
* Separate handling of Fiction and Non-Fiction books

---

## 🏗️ System Design

### 1. Book Classification

* A base **Book** abstraction is used to represent general book information
* Two specialized categories:

  * Fiction
  * Non-Fiction

### 2. Data Structures Used

* **Singly Linked List**

  * Used for managing Fiction books
* **Doubly Linked List**

  * Used for managing Non-Fiction books
* **Stack**

  * Stores recently added books (limited capacity)
* **Queue (Circular)**

  * Maintains borrowing history

---

## ⚙️ Functionalities

### ➤ Book Management

* Add and remove books dynamically
* Maintain categorized collections

### ➤ Search Operation

* Supports lookup by:

  * Title
  * ISBN

### ➤ Borrowing System

* Records borrowed books in a queue
* Maintains a fixed-size borrowing history

### ➤ Recent Activity Tracking

* Displays the most recently added books using stack behavior

---

## 🖥️ User Interface

The system uses a simple **menu-driven console interface** that allows users to:

* Navigate between different operations
* Input book details
* View results instantly

---

## 🚀 How to Run

1. Compile the program using a C++ compiler
2. Run the executable file
3. Use the menu options to interact with the system

---

## 🎓 Learning Outcomes

This project helps in understanding:

* Object-Oriented Programming (OOP) concepts
* Data structures and their real-world applications
* Memory management using dynamic allocation
* Implementation of stacks, queues, and linked lists

---

## 📌 Future Improvements

* Add file storage or database integration
* Implement a graphical user interface (GUI)
* Enhance search with partial matching
* Add user authentication and roles

---
