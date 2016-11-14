/*
 * message_sender.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#include <array>
#include <google/protobuf/message.h>
#include "multicast_message_sender.h"
#include "util.h"


class moserit::roper::MulticastMessageSender::Impl {

public:
	 Impl() {

	 }

};

moserit::roper::
MulticastMessageSender::MulticastMessageSender() : impl_(moserit::make_unique<Impl>()){

}

moserit::roper::
MulticastMessageSender::~MulticastMessageSender() {

}

void
moserit::roper::
MulticastMessageSender::send(const Message_t& message) {
	std::size_t size(message.ByteSize());
	char* data = new char[size];
	message.SerializeToArray(data, size);
}

