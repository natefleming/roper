/*
 * multicast_message_receiver.h
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MESSAGE_RECEIVER_H_
#define INCLUDE_MESSAGE_RECEIVER_H_

#include <functional>
#include <memory>
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
	receiver_->on_receive([this](const Buffer_t& buffer) {
		TMessage message;
		message.ParseFromArray(&buffer, buffer.size());
		message_handler_(message);
	});
}

template<class TMessage, class TReceiver>
MessageReceiver<TMessage, TReceiver>::~MessageReceiver() {

}

template<class TMessage, class TReceiver>
void
MessageReceiver<TMessage, TReceiver>::on_receive(
		std::function<void (TMessage)> message_handler) {
	message_handler_ = message_handler;
}

}
}

#endif /* MULTICAST_MESSAGE_RECEIVER_H_ */
