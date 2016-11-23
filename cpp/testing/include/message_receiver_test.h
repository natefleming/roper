/*
 * message_receiver_test.h
 *
 *  Created on: Nov 16, 2016
 *      Author: natefleming
 */

#ifndef TESTING_INCLUDE_MESSAGE_RECEIVER_TEST_H_
#define TESTING_INCLUDE_MESSAGE_RECEIVER_TEST_H_

#include <memory>
#include <gtest/gtest.h>
#include <boost/asio.hpp>

#include "message_receiver.h"
#include "multicast_receiver.h"
#include "roper.pb.h"

using namespace moserit::roper;

class MessageReceiverTest : public ::testing::Test {

protected:

	virtual void SetUp() override {
	}

	virtual void TearDown() override {}


};

TEST_F(MessageReceiverTest, should_receive_message) {
	boost::asio::io_service io_service;
	auto receiver = std::make_shared<MulticastReceiver>(io_service, "0.0.0.0", "225.2.215.254", 15981);
	MessageReceiver<Endpoint,MulticastReceiver> message_receiver(receiver);
	message_receiver.on_receive([](const Endpoint& endpoint) {
		std::cout << "recieved endpoint: " << endpoint.DebugString() << std::endl;
	});

}




#endif /* TESTING_INCLUDE_MESSAGE_RECEIVER_TEST_H_ */
