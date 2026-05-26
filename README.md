# Database Simulator — BST + Hash Table (C++ OOP)

A mini in-memory database engine implemented in C++ using custom templated Binary Search Tree and Hash Table data structures. Supports typed entries with primitive and list fields, indexed lookups, and table-level operations including copy construction and assignment.

## Overview

This project simulates how a real database manages data internally — using index trees (BST) for range queries and hash tables for O(1) average-case lookups. The entire system is built from scratch with C++ templates, no STL containers for the core structures.

## Tech Stack

- **Language:** C++17
- **Concepts:** OOP, templates, smart pointers, operator overloading, copy semantics
- **Build:** Makefile
- **Input:** stdin (test case ID)

## Key Concepts

- **Templated BST** (`BST<K, V>`): insert, inorder traversal, range queries with upper/lower bounds, size
- **Templated Hash Table** (`HashTable<T>`): insert, exists, remove, to_vector, dynamic rehashing
- **Entry system:** typed fields — `PrimitiveField<T>` and `ListField<T>` — via polymorphic `BaseField`
- **Index trees:** `BST<string, HashTable<Entry*>>` for multi-value indexed lookups
- **Table class:** add columns (primitive/list), add entries, copy constructor, `operator=`, filter queries

## Project Structure

```
cpp-oop-database-simulator-bst-hashtable/
├── main.cpp         # 18 test cases covering all components
├── bst.h / bst.tpp          # Templated BST
├── hashtable.h / hashtable.tpp  # Templated hash table with rehashing
├── hash.h           # Hash function
├── table.h / table.tpp      # Table with column schema and entry management
├── entry.h          # Row entry with typed fields
├── basefield.h / basefield.tpp  # Polymorphic field base class
└── Makefile
```

## How to Build & Run

```bash
make
echo "1" | ./main     # Test BST inorder traversal
echo "5" | ./main     # Test HashTable constructor
echo "18" | ./main    # Test Table::Filter with operator==
```

## Test Cases

| Cases | Component |
|-------|-----------|
| 1–4   | BST — inorder, upper/lower bound queries |
| 5–9   | HashTable — insert, exists, remove, to_vector |
| 10–11 | BaseField — index tree population for PrimitiveField & ListField |
| 12–18 | Table — constructor, addColumn, addEntry, copy, assignment, filter |

## Building

Requires a C++17-compatible compiler (GCC 9+ or Clang 10+).

```bash
# Compile
g++ -std=c++17 -O2 -Wall -o main main.cpp

# Or with CMake (if CMakeLists.txt is present)
cmake -B build && cmake --build build
```

No external libraries required — standard library only.
