/*
 * context_test.h
 *
 *  Created on: Nov 9, 2016
 *      Author: natefleming
 */

#ifndef TESTING_INCLUDE_MESSAGE_SENDER_TEST_H_
#define TESTING_INCLUDE_MESSAGE_SENDER_TEST_H_

#include <memory>
#include <gtest/gtest.h>

#include "message_sender.h"
#include "multicast_sender.h"
#include "roper.pb.h"

using namespace moserit::roper;

class MessageSenderTest : public ::testing::Test {

protected:

	virtual void SetUp() override {
	}

	virtual void TearDown() override {}


};

TEST_F(MessageSenderTest, should_send_message) {
	auto sender = std::make_shared<MulticastSender>("127.0.0.1", 10000);
	MessageSender<Endpoint,MulticastSender> message_sender(sender);
	Endpoint endpoint;
	endpoint.set_hostname("myhostname");
	endpoint.set_port(3456);
	message_sender.send(endpoint);
}


#endif 
