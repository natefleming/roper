/*
 * context_test.h
 *
 *  Created on: Nov 9, 2016
 *      Author: natefleming
 */

#include <gtest/gtest.h>

#include "../../include/configuration.h"

#ifndef TESTING_INCLUDE_CONFIGURATION_TEST_H_
#define TESTING_INCLUDE_CONFIGURATION_TEST_H_


using namespace moserit::roper;


class ConfigurationTest : public ::testing::Test {

protected:

	virtual void SetUp() override {
	}

	virtual void TearDown() override {}


};

TEST_F(ConfigurationTest, should_load_from_command_line) {
}


#endif 
