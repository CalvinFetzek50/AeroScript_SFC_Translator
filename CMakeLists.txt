cmake_minimum_required(VERSION 3.5)
project(AeroScript_SFC_Translator)

# require a C++17 compiler for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# some definitions
set(SOURCE_MAIN main.cpp)

set(SOURCE_TEXTREADER ./functions/combine_text.hpp ./functions/combine_text.tpp ./functions/match_functions.hpp ./functions/match_functions.tpp 
                        ./functions/network_init.hpp ./functions/network_init.tpp  
                        ./functions/variable_init.hpp ./functions/variable_init.tpp ./functions/write_csv.tpp ./functions/any_to_String.hpp)
set(SOURCE_TEXTREADER_TEST textReader_tests.cpp ${SOURCE_TEXTREADER})

set(SOURCE_STEP ./classes/step.hpp ./classes/step.tpp)
set(SOURCE_STEP_TEST step_tests.cpp ${SOURCE_STEP})

set(SOURCE_TRANSITION ./classes/transition.hpp ./classes/transition.tpp)
set(SOURCE_TRANSITION_TEST transition_tests.cpp ${SOURCE_TRANSITION})

set(SOURCE_NETWORK ./classes/network.hpp ./classes/network.tpp)
set(SOURCE_NETWORK_TEST network_tests.cpp ${SOURCE_NETWORK})

set(SOURCE_TEXTPARSER ./functions/textParser.hpp ./functions/textParser.tpp)
set(SOURCE_TEXTPARSER_TEST textParser_tests.cpp ${TEXTPARSER})

#create unittests
add_executable(test-textReader catch.hpp ${SOURCE_TEXTREADER_TEST})
add_executable(test-Step catch.hpp ${SOURCE_STEP_TEST})
add_executable(test-transition catch.hpp ${SOURCE_TRANSITION_TEST})
add_executable(test-network catch.hpp ${SOURCE_NETWORK_TEST})
add_executable(test-textParser catch.hpp ${SOURCE_TEXTPARSER_TEST})

enable_testing()

# unit tests
add_test(test-textReader test-textReader)
add_test(test-Step test-Step)
add_test(test-transition test-transition)
add_test(test-network test-network)
add_test(test-textParser test-textParser)

# add a main executable
add_executable(main-textReader ${SOURCE_MAIN})
