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
int,    real,   bool,   void,   string,   true,   false,  if,     elif,   else,    
for,    while,  do,     break,  continue, return, loop,   until
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
Non terminals are represented with a capital letter.
```
                  program -> (func_decl)*

       # Variable declaration
                 var_decl -> type var_decl_list ";"
            var_decl_list -> var_decl_expr ("," var_decl_list)*
            var_decl_expr -> Identifier ("=" expr)?

       # Function declaration, params and args
                func_decl -> type Identifier "(" param_list? ")" compound_stmt
               param_list -> param ("," param)*
                    param -> type Identifier

                 arg_list -> arg ("," arg)*
                      arg -> expr


       # Expressions
                     expr -> assignment_expr
          assignment_expr -> logical_or_expr
                           | assignment_expr assign_op logical_or_expr
          logical_or_expr -> logical_or_expr "||" logical_and_expr
                           | logical_and_expr
         logical_and_expr -> logical_and_expr "&&" equality_expr
                           | equality_expr
            equality_expr -> equality_expr "==" additive_expr
                           | equality_expr "!=" additive_expr
                           | additive_expr
            additive_expr -> additive_expr "+" multiplicative_expr
                           | additive_expr "-" multiplicative_expr
                           | multiplicative_expr
      multiplicative_epxr -> multiplicative_expr "*" unary_expr
                           | multiplicative_expr "/" unary_expr
                           | multiplicative_expr "%" unary_expr
                           | unary_expr
               unary_expr -> "+" unary_expr
                           | "-" unary_expr
                           | "++" unary_expr
                           | "--" unary_expr
                           | "!" unary_expr
                           | primary_expr
             primary_expr -> Identifier
                           | Identifier "(" arg_list? ")"
                           | Identifier "++"
                           | Identifier "--"
                           | IntVal
                           | RealVal
                           | BoolVal
                           | StringVal
                           | "(" expr ")"


       # Statements
                     stmt -> expr_stmt
                           | if_stmt
                           | loop_stmt
                           | jump_stmt
                           | return_stmt
                           | compound_stmt

                expr_stmt -> ";"
                           | expr ";"
                  if_stmt -> If "(" expr" )" stmt ( Elif "(" expr ")" stmt )* ( Else stmt )?
                loop_stmt -> Loop "(" expr ")" stmt
                           | Loop "(" var_decl expr_stmt expr ")" stmt
                           | Loop stmt Until "(" expr ")" ";"
                jump_stmt -> Continue ";"
                           | Break ";"
              return_stmt -> Return expr_stmt
            compound_stmt -> "{" item_list? "}"

               item_list -> item (item_list)*
                     item -> var_decl | stmt

                assign_op -> "=" | "+=" | "-=" | "/=" | "*="
                     type -> Int | Real | String | Bool | Void
```