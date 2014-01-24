set (GTEST_ROOT /usr/src/gtest)
PROJECT (libpack)

INCLUDE_DIRECTORIES (${GTEST_ROOT})

ADD_LIBRARY (pack src/pack.c)

ADD_EXECUTABLE (test_pack src/test_pack.cc src/pack.c ${GTEST_ROOT}/src/gtest-all.cc)
TARGET_LINK_LIBRARIES (test_pack -lpthread)
ADD_TEST(pack test_pack)

