/*
 * context_test.h
 *
 *  Created on: Nov 9, 2016
 *      Author: natefleming
 */

#ifndef TESTING_INCLUDE_MESSAGE_SENDER_TEST_H_
#define TESTING_INCLUDE_MESSAGE_SENDER_TEST_H_

#include <thread>
#include <chrono>
#include <iostream>
#include <memory>
#include <gtest/gtest.h>

#include "message_sender.h"
#include "message_receiver.h"
#include "multicast_sender.h"
#include "multicast_receiver.h"
#include "roper.pb.h"

using namespace moserit::roper;

class MessageSenderTest : public ::testing::Test {

protected:

	virtual void SetUp() override {
	}

	virtual void TearDown() override {}


};

TEST_F(MessageSenderTest, should_send_message) {

	auto receiver = std::make_shared<MulticastReceiver>("0.0.0.0", "225.2.215.254", 10000);
	MessageReceiver<Endpoint,MulticastReceiver> message_receiver(receiver);
	message_receiver.on_receive([](const Endpoint& endpoint) {
		std::cout << endpoint.DebugString() << std::endl;
	});

	std::this_thread::sleep_for(std::chrono::seconds(3));

	auto sender = std::make_shared<MulticastSender>("225.2.215.254", 10000);
	MessageSender<Endpoint,MulticastSender> message_sender(sender);
	Endpoint endpoint;
	endpoint.set_hostname("myhostname");
	endpoint.set_port(3456);
	message_sender.send(endpoint);


	std::this_thread::sleep_for(std::chrono::seconds(5));
}


#endif 
