/*
 * context_test.h
 *
 *  Created on: Nov 9, 2016
 *      Author: natefleming
 */

#include <gtest/gtest.h>
#include "context.h"

#ifndef TESTING_INCLUDE_CONTEXT_TEST_H_
#define TESTING_INCLUDE_CONTEXT_TEST_H_


using namespace moserit::roper;


class ContextText : public ::testing::Test {

protected:

	virtual void SetUp() override {
	}

	virtual void TearDown() override {}


};

TEST_F(ContextText, should_load_from_command_line) {
}


#endif 
