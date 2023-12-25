cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

# Main executable
add_executable(supersearch main.cpp)

# Test executable for AVL Tree
add_executable(tests_AVL_Tree test_AVLTree.cpp AVLTree.h)
add_test(NAME TestAVLTree COMMAND test_avlTree)

# Test executable for Index
add_executable(testIndex test_Index.cpp Index.h Index.cpp )
add_test(NAME TestIndex COMMAND testIndex)

# Test executable for Query
add_executable(testQuery test_Query.cpp porter2_stemmer.cpp DocumentParser.cpp Query.cpp UserInterface.cpp Index.cpp)
add_test(NAME TestQuery COMMAND testQuery)

# this makes sure we also link rapidjson

set(CMAKE_VERBOSE_MAKEFILE OFF)
