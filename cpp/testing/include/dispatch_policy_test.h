/*
 * dispatch_policy_test.h
 *
 *  Created on: Nov 17, 2016
 *      Author: natefleming
 */

#ifndef TESTING_INCLUDE_DISPATCH_POLICY_TEST_H_
#define TESTING_INCLUDE_DISPATCH_POLICY_TEST_H_


#include <memory>
#include <gtest/gtest.h>

#include "dispatch_policy.h"

using namespace moserit::roper;

class DispatchPolicyTest : public ::testing::Test {

protected:

	virtual void SetUp() override {
	}

	virtual void TearDown() override {}


};

TEST_F(DispatchPolicyTest, should_invoke_sync_retry_policy) {
	bool was_invoked(false);
	DispatchPolicy::sync_retry_policy()->dispatch([&was_invoked]() {
		was_invoked = true;
	});
	ASSERT_TRUE(was_invoked);
}

#endif /* TESTING_INCLUDE_DISPATCH_POLICY_TEST_H_ */
