set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")  # Make it easier to target test files

add_test(NAME lexer_lexemes COMMAND "${EXEC}" "${DIR}/test0.tl" "--lexer-verbose" "--lexer-no-err")
add_test(NAME lexer_values COMMAND "${EXEC}" "${DIR}/test1.tl" "--lexer-verbose" "--lexer-no-err")