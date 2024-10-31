set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME analyser_HelloWorld COMMAND "${EXEC}" "${DIR}/test0.tl" "--test-analyser")
add_test(NAME analyser_variable_declaration COMMAND "${EXEC}" "${DIR}/test1.tl" "--test-analyser")

add_test(NAME analyser_duplicate_variables COMMAND "${EXEC}" "${DIR}/test2.tl" "--test-analyser")
set_property(TEST analyser_duplicate_variables PROPERTY WILL_FAIL True)

add_test(NAME analyser_type_mismatch COMMAND "${EXEC}" "${DIR}/test3.tl" "--test-analyser")
set_property(TEST analyser_type_mismatch PROPERTY WILL_FAIL True)

add_test(NAME analyser_multi_expr COMMAND "${EXEC}" "${DIR}/test4.tl" "--test-analyser")

add_test(NAME analyser_multi_expr_invalid_type COMMAND "${EXEC}" "${DIR}/test4.tl" "--test-analyser")
set_property(TEST analyser_multi_expr_invalid_type PROPERTY WILL_FAIL True)


