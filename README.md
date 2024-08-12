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

## Identifier
Identifiers are defined with alphanumerics and underscore. Identifiers must start with an alphabet or an underscore. 

Examples of well-formed identifiers

```
correctId
_
_3124
Valid
correct_1_Identifier
```
Examples of ill-formed identifiers
```
1invalid
invalid_+identifier
_not-valid
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

Following operations can only be performed on `int`  
* `%`: Arithmetic modulo (remainder).

## Comments
Toylan uses @ to indicate the beginning of a comment.  
A comment may appear at the start or end of a line. The effect of comment persists to the end of the same line.


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