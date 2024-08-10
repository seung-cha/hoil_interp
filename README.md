# Toylan
Compiler for statistically typed language Toylan(guage) written in C++.


## Specifications
* [Overview](#overview)
* [Context Free Grammar](#context-free-grammar)


# Overview
Toylan is designed to be simple to learn and easy to use.

## Data Types
Toylan features the following primitive data types - 
* `int`: Signed whole numbers in 4 bytes range.
* `real`: Signed real numbers in 4 bytes range.

## Operations
Following operations can be performed on `int` and `real`  
* `+`: Arithmetic addition.
* `-`: Arithmetic subtraction.
* `*`: Arithmetic multiplication.
* `/`: Arithmetic division.


# Context Free Grammar
```
arithmetic-op0 -> arithmetic-op0 "+" arithmetic-op1
                | arithmetic-op0 "-" arithmetic-op1
                | arithmetic-op1

arithmetic-op1 -> arithmetic-op1 "*" operand
                | arithmetic-op1 "/" operand
                | operand

       operand -> *digits*

```