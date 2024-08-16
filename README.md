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
int, real, bool, void, string, true, false
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
* `real`: Signed real numbers in 4 bytes range. (equivalent to `float`)
* `bool`: true, false. 1 byte range. (equivalent to `bool`)

## Operations
Following operations can be performed on `int` and `real`  
* `+`: Arithmetic addition.
* `-`: Arithmetic subtraction.
* `*`: Arithmetic multiplication.
* `/`: Arithmetic division.

Following operations can only be performed on `int`  
* `%`: Arithmetic modulo (remainder).

Following operations are boolean operations and the effects are obvious:
* `!` Negation
* `==` Equality
* `!=` Inequality
* `>` Strictly greater
* `<` Strictly less
* `>=` Greater or equal
* `<=` Less or equal


## Comments
Toylan uses `#` to indicate the beginning of a comment.  
A comment may appear at the start or end of a line. The effect of comment persists to the end of the same line.


# Context Free Grammar
Non terminals are represented by enclosing them with `_` or `"`. `eps` represents empty production.
```
                  program -> (var-decl)*

       # Variable declaration
                 var_decl -> type var_decl_list ";"
            var_decl_list -> var_decl_expr ("," var_decl_list)*
            var_decl_expr -> _identifier_ ("=" var_init_expr)?
            var_init_expr -> expr


                     type -> _int_ | _real_ | _string_ | _void_

           arithmetic-op0 -> arithmetic-op0 "+" arithmetic-op1
                           | arithmetic-op0 "-" arithmetic-op1
                           | arithmetic-op1

           arithmetic-op1 -> arithmetic-op1 "*" _number_
                           | arithmetic-op1 "/" _number_
                           | _number_
```