/*
 * multicast_message_receiver.h
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MESSAGE_RECEIVER_H_
#define INCLUDE_MESSAGE_RECEIVER_H_

#include <glog/logging.h>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "types.h"

namespace moserit {
namespace roper {

template<class TMessage, class TReceiver>
class MessageReceiver {

public:

	MessageReceiver(const std::shared_ptr<TReceiver> receiver);
	virtual ~MessageReceiver();

	void on_receive(std::function<void (TMessage)> message_handler);

private:

	std::function<void (TMessage)> message_handler_;
	std::shared_ptr<TReceiver> receiver_;

};

template<class TMessage, class TReceiver>
MessageReceiver<TMessage, TReceiver>::MessageReceiver(
		const std::shared_ptr<TReceiver> receiver) : receiver_(receiver) {
	LOG(INFO) << "MessageReceiver::MessageReceiver";

}

template<class TMessage, class TReceiver>
MessageReceiver<TMessage, TReceiver>::~MessageReceiver() {
	LOG(INFO) << "MessageReceiver::~MessageReceiver";
}

template<class TMessage, class TReceiver>
void
MessageReceiver<TMessage, TReceiver>::on_receive(
		std::function<void (TMessage)> message_handler) {
	LOG(INFO) << "MessageReceiver::on_receive";
	message_handler_ = message_handler;
	receiver_->on_receive([this](const Buffer_t& buffer) {
		LOG(INFO) << "MessageReceiver::on_receive(buffer=[" << buffer << "], size=[" << buffer.size() << "])";
		TMessage message;
		message.ParseFromString(buffer);
		LOG(INFO) << "message=" << message.DebugString();
		message_handler_(message);
	});
}

}
}

#endif /* MULTICAST_MESSAGE_RECEIVER_H_ */
