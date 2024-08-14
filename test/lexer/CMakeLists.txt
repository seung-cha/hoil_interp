set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")  # Make it easier to target test files

add_test(NAME lexer_lexemes COMMAND "${EXEC}" "${DIR}/test0.tl" "--lexer-verbose" "--lexer-no-err")
add_test(NAME lexer_values COMMAND "${EXEC}" "${DIR}/test1.tl" "--lexer-verbose" "--lexer-no-err")
add_test(NAME lexer_unterminated_string COMMAND "${EXEC}" "${DIR}/test2.tl" "--lexer-verbose" "--lexer-no-err" WILL_FAIL True)
add_test(NAME lexer_illegal_character COMMAND "${EXEC}" "${DIR}/test3.tl" "--lexer-verbose" "--lexer-no-err" WILL_FAIL True)
add_test(NAME lexer_empty_file COMMAND "${EXEC}" "${DIR}/test4.tl" "--lexer-verbose" "--lexer-no-err")
add_test(NAME lexer_empty_file2 COMMAND "${EXEC}" "${DIR}/test5.tl" "--lexer-verbose" "--lexer-no-err")
add_test(NAME lexer_file1 COMMAND "${EXEC}" "${DIR}/test6.tl" "--lexer-verbose" "--lexer-no-err")
add_test(NAME lexer_file2 COMMAND "${EXEC}" "${DIR}/test7.tl" "--lexer-verbose" "--lexer-no-err" WILL_FAIL True)




