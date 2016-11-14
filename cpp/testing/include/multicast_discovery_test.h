/*
 * multicast_discovery_test.h
 *
 *  Created on: Nov 9, 2016
 *      Author: natefleming
 */

#include <gtest/gtest.h>
#include "multicast_discovery.h"

#ifndef TESTING_INCLUDE_MULTICAST_DISCOVERY_TEST_H_
#define TESTING_INCLUDE_MULTICAST_DISCOVERY_TEST_H_


using namespace moserit::roper;

const std::string BIND_ADDRESS("0.0.0.0");
const std::string MULTICAST_ADDRESS("239.255.0.1");
const short PORT(30001);

class MulticastDiscoveryTest : public ::testing::Test {

protected:

	virtual void SetUp() override {
		MulticastDiscovery::Builder builder;
		discovery_ = builder
				.with_bind_endpoint(BIND_ADDRESS, PORT)
				.with_multicast_address(MULTICAST_ADDRESS)
				.build();
	}

	virtual void TearDown() override {}

	std::shared_ptr<MulticastDiscovery> discovery_;

};

TEST_F(MulticastDiscoveryTest, should_initialize) {
	discovery_->initialize();
}

TEST_F(MulticastDiscoveryTest, should_start) {
	discovery_->start();
}

TEST_F(MulticastDiscoveryTest, should_stop) {
	discovery_->stop();
}

TEST_F(MulticastDiscoveryTest, should_terminate) {
	discovery_->terminate();
}

TEST_F(MulticastDiscoveryTest, should_publish) {
	discovery_->publish();
}

TEST_F(MulticastDiscoveryTest, should_suscribe) {
	discovery_->subscribe();
}


#endif /* TESTING_INCLUDE_MULTICAST_DISCOVERY_TEST_H_ */
