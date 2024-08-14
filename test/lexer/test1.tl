# various literals: int, real, string
"this is a string" "this is another string"
"this is a string on a new line"
"this is a      string on a \n new line with \t special characters"
"This is a string with # comment symbol but lexer should include it since its inside a string"
"following lines contain number formats"
1 123 321 14125 28391 2551132 11231121 # integers
3.1 .012 0.112 .14159265358979 33.12 125. # reals
132..251 # equivalent to 132.0 0.251
