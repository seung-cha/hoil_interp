set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME parser_var_decl COMMAND "${EXEC}" "${DIR}/test0.tl" "--parser-no-err")
add_test(NAME parser_multi_var_decl COMMAND "${EXEC}" "${DIR}/test1.tl" "--parser-no-err")
add_test(NAME parser_var_decl_assign COMMAND "${EXEC}" "${DIR}/test2.tl" "--parser-no-err")