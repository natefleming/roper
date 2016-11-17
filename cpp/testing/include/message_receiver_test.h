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
	auto receiver = std::make_shared<MulticastReceiver>("0.0.0.0", "127.0.0.1", 10000);
	MessageReceiver<Endpoint,MulticastReceiver> message_receiver(receiver);
	message_receiver.on_receive([](const Endpoint& endpoint) {

	});

	//Endpoint endpoint;
//	endpoint.set_hostname("myhostname");
//	endpoint.set_port(3456);
//	message_sender.send(endpoint);
}




#endif /* TESTING_INCLUDE_MESSAGE_RECEIVER_TEST_H_ */
