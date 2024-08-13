set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")  # Make it easier to target test files

add_test(NAME run COMMAND "${EXEC}")
add_test(NAME test0 COMMAND "${EXEC}" "${DIR}/test0.tl")