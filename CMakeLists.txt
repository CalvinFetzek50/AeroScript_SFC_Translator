cmake_minimum_required(VERSION 3.5)
project(AeroScript_SFC_Translator)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# some definitions
set(SOURCE_MAIN main.cpp)
set(SOURCE_TEXTREADER textReader.hpp)
set(SOURCE_TEXTREADER_TEST textReader_tests.cpp ${SOURCE_TEXTREADER})

set(SOURCE_STEP step.hpp step.tpp)
set(SOURCE_STEP_TEST step_tests.cpp ${SOURCE_STEP})

set(SOURCE_TRANSITION transition.hpp transition.tpp)
set(SOURCE_TRANSITION_TEST transition_tests.cpp ${SOURCE_TRANSITION})

set(SOURCE_NETWORK network.hpp network.tpp)
set(SOURCE_NETWORK_TEST network_tests.cpp ${SOURCE_NETWORK})

#create unittests
add_executable(test-textReader catch.hpp ${SOURCE_TEXTREADER_TEST})
add_executable(test-Step catch.hpp ${SOURCE_STEP_TEST})
add_executable(test-transition catch.hpp ${SOURCE_TRANSITION_TEST})
add_executable(test-network catch.hpp ${SOURCE_NETWORK_TEST})

enable_testing()

# unit tests
add_test(test-textReader test-textReader)
add_test(test-Step test-Step)
add_test(test-transition test-transition)
add_test(test-network test-network)

# add a main executable
add_executable(main-textReader ${SOURCE_MAIN})
