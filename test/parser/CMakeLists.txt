set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME parser_var_decl COMMAND "${EXEC}" "${DIR}/test0.tl" "--test-parser")
add_test(NAME parser_multi_var_decl COMMAND "${EXEC}" "${DIR}/test1.tl" "--test-parser")
add_test(NAME parser_var_decl_assign COMMAND "${EXEC}" "${DIR}/test2.tl" "--test-parser")
add_test(NAME parser_multi_func_decl COMMAND "${EXEC}" "${DIR}/test3.tl" "--test-parser")

add_test(NAME parser_wrong_func_decl COMMAND "${EXEC}" "${DIR}/test4.tl" "--test-parser")
set_property(TEST parser_wrong_func_decl PROPERTY WILL_FAIL True)

add_test(NAME parser_if_stmt COMMAND "${EXEC}" "${DIR}/test5.tl" "--test-parser")
add_test(NAME parser_if_else_stmt COMMAND "${EXEC}" "${DIR}/test6.tl" "--test-parser")
add_test(NAME parser_if_elif_else_stmt COMMAND "${EXEC}" "${DIR}/test7.tl" "--test-parser")

add_test(NAME parser_boolean_expr COMMAND "${EXEC}" "${DIR}/test8.tl" "--test-parser")
add_test(NAME parser_boolean_expr_2 COMMAND "${EXEC}" "${DIR}/test9.tl" "--test-parser")

# add_test(NAME parser_nested_func_decl COMMAND "${EXEC}" "${DIR}/test10.tl" "--test-parser")
# set_property(TEST parser_nested_func_decl PROPERTY WILL_FAIL True)

# add_test(NAME parser_func_decl COMMAND "${EXEC}" "${DIR}/test11.tl" "--test-parser")
# add_test(NAME parser_func_with_one_param_decl COMMAND "${EXEC}" "${DIR}/test12.tl" "--test-parser")
# add_test(NAME parser_func_with_multi_params_decl COMMAND "${EXEC}" "${DIR}/test13.tl" "--test-parser")
# add_test(NAME parser_multi_func_decl_2 COMMAND "${EXEC}" "${DIR}/test14.tl" "--test-parser")

# add_test(NAME parser_func_call COMMAND "${EXEC}" "${DIR}/test15.tl" "--test-parser")
# add_test(NAME parser_func_with_one_arg_call COMMAND "${EXEC}" "${DIR}/test16.tl" "--test-parser")
# add_test(NAME parser_func_with_multi_args_call COMMAND "${EXEC}" "${DIR}/test17.tl" "--test-parser")
# add_test(NAME parser_multi_func_call COMMAND "${EXEC}" "${DIR}/test18.tl" "--test-parser")

# add_test(NAME parser_break_stmt COMMAND "${EXEC}" "${DIR}/test19.tl" "--test-parser")
# add_test(NAME parser_continue_stmt COMMAND "${EXEC}" "${DIR}/test20.tl" "--test-parser")
# add_test(NAME parser_return_stmt COMMAND "${EXEC}" "${DIR}/test21.tl" "--test-parser")

# add_test(NAME parser_while_like_loop_stmt COMMAND "${EXEC}" "${DIR}/test22.tl" "--test-parser")
# add_test(NAME parser_for_like_loop_stmt COMMAND "${EXEC}" "${DIR}/test23.tl" "--test-parser")
# add_test(NAME parser_do_while_like_loop_stmt COMMAND "${EXEC}" "${DIR}/test24.tl" "--test-parser")

# add_test(NAME parser_hello_world_example COMMAND "${EXEC}" "${DIR}/test25.tl" "--test-parser")
# add_test(NAME parser_hello_world_example2 COMMAND "${EXEC}" "${DIR}/test26.tl" "--test-parser")
# add_test(NAME parser_hello_world_example3 COMMAND "${EXEC}" "${DIR}/test27.tl" "--test-parser")

# add_test(NAME parser_addition COMMAND "${EXEC}" "${DIR}/test28.tl" "--test-parser")
# add_test(NAME parser_subtraction COMMAND "${EXEC}" "${DIR}/test29.tl" "--test-parser")
# add_test(NAME parser_multiplication COMMAND "${EXEC}" "${DIR}/test30.tl" "--test-parser")
# add_test(NAME parser_division COMMAND "${EXEC}" "${DIR}/test31.tl" "--test-parser")
# add_test(NAME parser_modulo COMMAND "${EXEC}" "${DIR}/test46.tl" "--test-parser")

# add_test(NAME parser_unary_addition COMMAND "${EXEC}" "${DIR}/test32.tl" "--test-parser")
# add_test(NAME parser_unary_subtraction COMMAND "${EXEC}" "${DIR}/test33.tl" "--test-parser")
# add_test(NAME parser_prefix_unary_addition COMMAND "${EXEC}" "${DIR}/test34.tl" "--test-parser")
# add_test(NAME parser_prefix_unary_subtraction COMMAND "${EXEC}" "${DIR}/test35.tl" "--test-parser")
# add_test(NAME parser_unary_negation COMMAND "${EXEC}" "${DIR}/test36.tl" "--test-parser")

# add_test(NAME parser_equality COMMAND "${EXEC}" "${DIR}/test37.tl" "--test-parser")
# add_test(NAME parser_inequality COMMAND "${EXEC}" "${DIR}/test38.tl" "--test-parser")
# add_test(NAME parser_less_than COMMAND "${EXEC}" "${DIR}/test39.tl" "--test-parser")
# add_test(NAME parser_greater_than COMMAND "${EXEC}" "${DIR}/test40.tl" "--test-parser")
# add_test(NAME parser_less_or_equal COMMAND "${EXEC}" "${DIR}/test41.tl" "--test-parser")
# add_test(NAME parser_greater_or_equal COMMAND "${EXEC}" "${DIR}/test42.tl" "--test-parser")
# add_test(NAME parser_not_equal COMMAND "${EXEC}" "${DIR}/test43.tl" "--test-parser")

# add_test(NAME parser_nested_expr COMMAND "${EXEC}" "${DIR}/test44.tl" "--test-parser")
# add_test(NAME parser_multi_nested_expr COMMAND "${EXEC}" "${DIR}/test45.tl" "--test-parser")


