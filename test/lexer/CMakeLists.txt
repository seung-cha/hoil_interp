set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")  # Make it easier to target test files
set(EXE "${PROJECT_NAME}")  # Make it easier to run

add_test(NAME run COMMAND "${EXE}")
add_test(NAME fail COMMAND "${EXE}" WILL_FAIL True)
add_test(NAME test0 COMMAND "${EXE}" "${DIR}/test0.tl")