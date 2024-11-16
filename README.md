# Human-Oriented Instruction Language
My Honours project



## Specifications
* [Overview](#overview)
* [Context Free Grammar](#context-free-grammar)


# Overview
HOIL aims to loosen grammar restrictions as much as possible with the help of AI (yay, another AI product).

# Instruction
Each line contains at most one instruction. Instruction is one of `declaration` or `statement`. Instruction must terminate with a new line or EOF.

# Type
HOIL supports 5 types:
`Number`, `Logic`, `Sentence`, `Object`, `Attribute`


## Variable Declaration and Initialisation
HOIL infers type from instruction. 
```
{identifier} is 3
```
The instruction above declares `{identifier}` and assigns it a value of 3 (`Number` type).

Users can declare variables without initial value
```
{identifier} is Number
```
This instruction declares `{identifier}` but does not assign a value. Attempting to use this variable will result in compilation error.

Type is fixed. That is, once a type is determined, attempting to assign a value of different type will result in a compilation error:
```
{identifier} is Number
{identifier} is true # An attempt to assign a logic value

# ERROR!
```

## Attribute
`Attribute` qualifies `Object`. Unlike other types, `Attribute` cannot be changed later once defined.

```
small_cube is Attribute: "a cube block whose size is 10 cubic centimetres"
red_color is Attribute: "red object"
```

```
small_cube is Attribute
small_cube is "a cube block whose size is 10 cubic cemtimetres" # ERROR
```

If value is omitted, name qualifies the attribute.
```
cube is Attribute # equivalent to cube is Attribute: "cube"
```

## Object
`Object` consists of one or more `Attribute`. Multiple `Attribute` can be joined together as a logic.

```
small_red_cube is Object
small_red_cube is small_cube and red_color

# small_red_cube is a cube that is small and red
```

```
small_or_red_object is Object
small_or_red_object is small_cube or red_color

# small_or_red_object is either a small cube or anything that is red.
```
Similar to `Attribute`, once an `Object` is specified, it cannot be changed later.

TOOD: What should happen when it fails to allocate object?


## Reserved Keywords
Following keywords are reserved and cannot be used as an identifier.
```

```

## Identifier
Identifiers are defined with alphanumerics. Identifiers must start with an alphabet.

## Comments
HOIL uses `#` to indicate the beginning of a comment.  
A comment may appear at the start or end of a line. The effect of comment persists to the end of the same line.


# Context Free Grammar
Non terminals are represented with a capital letter.
```
                  program -> (func_decl)*

       # Variable declaration
      local_var_decl_list -> type var_decl_list ";"
            var_decl_list -> var_decl ("," var_decl_list)*
                 var_decl -> Identifier var_decl_expr
            var_decl_expr -> ("=" expr)?

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
            equality_expr -> equality_expr "==" relation_expr
                           | equality_expr "!=" relation_expr
                           | relation_expr
            relation_expr -> relation_expr "<"  additive_expr
                           | relation_expr "<=" additive_expr
                           | relation_expr ">"  additive_expr
                           | relation_expr "=>" additive_expr
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
                           | Loop "(" local_var_decl_list expr_stmt expr ")" stmt
                           | Loop stmt Until "(" expr ")" ";"
                jump_stmt -> Continue ";"
                           | Break ";"
              return_stmt -> Return expr_stmt
            compound_stmt -> "{" item_list? "}"

               item_list -> item (item_list)*
                    item -> local_var_decl_list | stmt

                assign_op -> "=" | "+=" | "-=" | "/=" | "*="
                     type -> Int | Real | String | Bool | Void
```