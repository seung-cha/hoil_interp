set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME parser_var_decl COMMAND "${EXEC}" "${DIR}/test0.tl" "--parser-no-err")
add_test(NAME parser_multi_var_decl COMMAND "${EXEC}" "${DIR}/test1.tl" "--parser-no-err")
add_test(NAME parser_var_decl_assign COMMAND "${EXEC}" "${DIR}/test2.tl" "--parser-no-err")
add_test(NAME parser_func_decl COMMAND "${EXEC}" "${DIR}/test3.tl" "--parser-no-err")

add_test(NAME parser_wrong_func_decl COMMAND "${EXEC}" "${DIR}/test4.tl" "--parser-no-err")
set_property(TEST parser_wrong_func_decl PROPERTY WILL_FAIL True)

add_test(NAME parser_1 COMMAND "${EXEC}" "${DIR}/test5.tl" "--parser-no-err")
add_test(NAME parser_2 COMMAND "${EXEC}" "${DIR}/test6.tl" "--parser-no-err")


