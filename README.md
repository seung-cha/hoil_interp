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
Multi-variable declaration and assignment is prohibited.
```
int a, b, c;
a = b = c;
```
The equivalence of these expressions doesn't exist in HOIL.

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
or, and, is, not, equals

```

## Identifier
Identifiers are defined with alphanumerics. Identifiers must start with an alphabet.

## Logical Expression
Logical (boolean) works as you would expect. A few exceptions:
* 'is' is equivalent to `==`
* `not` is negation. Prefix `not` is `!` and `is not` is `!=`. 
* `and` and `or` for `&&` and `||`

* Equality operation on the `Number` type is interpreted as equality within a small interval. This is because `Number` suppers decimals.

## Loop
HOIL supports while-like loops only.
```
repeat 
{

}

repeat until {expr}
{

}
```

The former is equivalent to `while(1)` and the latter `while(expr)`.

## Function
Functions are defined with the `define` keyword. 

```
define HelloWorld 
{

}
```

Note that unlike other languages, if a function takes no parameters, you can omit the parenthesis.
Type hinting (var: type) for parameter is not required. However, if provided, the type of that parameter cannot be changed later.
```
define TypedFunc(param1, param2: Number)
{
     # param1 accepts any type but param2 only accepts Number
}
```

If a function returns a value, the return type must be specified.
```
define ReturnFunc -> Number
{

}
```
This function above returns `Number`.

Function can be called as an expression or statement.
When called as a statement, it must be preceeded by the `call` keyword (This is because variable declaration and function call cannot be distinguished in LL(1)).

```
call ReturnFunc
```
Again, if a function takes no arguments, the parenthesis can be omitted.

If used as an expression, the call keyword is not needed but parenthesis is required even without arguments.

```
a is FuncCall() + 32
```

Above defines `a` with the value of 32 + the return value (Number) of the function `FuncCall`.

 
## Comments
HOIL uses `#` to indicate the beginning of a comment.  
A comment may appear at the start or end of a line. The effect of comment persists to the end of the same line.

# Intermediate Representation
TODO

# Context Free Grammar
Non terminals are represented with a capital letter.
```
                  program -> (stmt)*

       # Variable declaration
                 var_decl -> identifier is Expr
                           | identifier is Type (":" Expr)?


       # Function declaration, params and args
                func_decl -> define identifier ( "(" param_list ")" )? ("->" type)? compound_stmt
               param_list -> param ("," param)*
                    param -> Identifier (: type)?

                 arg_list -> arg ("," arg)*
                      arg -> expr

       # Expressions
                     expr -> logical_or_expr
          logical_or_expr -> logical_or_expr "||" logical_and_expr
                           | logical_or_expr "or" logical_and_expr
                           | logical_and_expr
         logical_and_expr -> logical_and_expr "&&" equality_expr
                           | logical_and_expr "and" equality_expr
                           | equality_expr
            equality_expr -> equality_expr "==" relation_expr
                           | equality_expr "is" relation_expr
                           | equality_expr "equals" relation_expr
                           | equality_expr "!=" relation_expr
                           | equality_expr "is not" relation_expr
                           | equality_expr "not equals" relation_expr
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
                           | "not" unary_expr
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
                           | compound_stmt
                           | instruct_stmt

                expr_stmt -> var_decl | func_decl
                  if_stmt -> If expr "\n" stmt (Elif expr "\n" stmt )* ( Else "\n" stmt )?
                loop_stmt -> Repeat "\n" stmt
                           | Repeat Until expr "\n" stmt
                jump_stmt -> Continue
                           | Break
              return_stmt -> Return expr_stmt
            compound_stmt -> "{" item_list? "}"
            instruct_stmt -> > STRINGLITERAL
                call_stmt -> call identifier "(" arg_list ")"

               item_list -> item (item_list)*
                    item -> stmt

                assign_op -> "=" | "+=" | "-=" | "/=" | "*="

                     Type -> Number | Logic | Sentence | Object
```