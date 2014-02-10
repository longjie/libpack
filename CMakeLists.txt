cmake_minimum_required(VERSION 2.8)
project (libpack)
set(GTEST_ROOT $ENV{HOME}/Codes/gtest-1.7.0)
#set (GTEST_ROOT /usr/src/gtest)
include_directories (${GTEST_ROOT}/include)

ADD_LIBRARY (pack src/pack.c)

ADD_EXECUTABLE (test_pack src/test_pack.cc src/pack.c)
TARGET_LINK_LIBRARIES (test_pack ${GTEST_ROOT}/build/libgtest.a  ${GTEST_ROOT}/build/libgtest_main.a -lpthread)
ADD_TEST(pack test_pack)

