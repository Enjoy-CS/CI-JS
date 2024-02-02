#include <gtest/gtest.h>

import Hello;

class TestThread : public ::testing::Test {
protected:
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(TestThread, test1) {
   
}