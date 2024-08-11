# Toylan
Compiler for statistically typed language Toylan(guage) written in C++.


## Specifications
* [Overview](#overview)
* [Context Free Grammar](#context-free-grammar)


# Overview
Toylan is designed to be simple to learn and easy to use.

## Reserved Keywords
Following keywords are reserved and cannot be used as an identifier.
```
int, real, bool, string, true, false
if,  elif, else, 
for, while,  do, break, continue
```

## Data Types
Toylan features the following primitive data types - 
* `int`: Signed whole numbers in 4 bytes range. (equivalent to `int32_t`)
* `real`: Signed real numbers in 4 bytes range. (equivalent to `string`)
* `bool`: true, false. 1 byte range. (equivalent to `bool`)

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