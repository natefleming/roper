/*
 * multicast_message_sender.h
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MESSAGE_SENDER_H_
#define INCLUDE_MESSAGE_SENDER_H_

#include <glog/logging.h>
#include <sstream>
#include "types.h"

namespace moserit {
namespace roper {

template<class TSender>
class MessageSender {

public:

	MessageSender(const std::shared_ptr<TSender> sender);
	virtual ~MessageSender();

	template<class TMessage>
	void send(const TMessage& message);

private:

	std::shared_ptr<TSender> sender_;

};

template<class TSender>
MessageSender<TSender>::MessageSender(
		const std::shared_ptr<TSender> sender) :
		sender_(sender) {
	LOG(INFO)<< "MessageSender::MessageSender";
}

template<class TSender>
MessageSender<TSender>::~MessageSender() {
	LOG(INFO)<< "MessageSender::~MessageSender";
}

template<typename TSender>
template<typename TMessage>
void MessageSender<TSender>::send(const TMessage& message) {
	LOG(INFO)<< "MessageSender::send(message=" << message.DebugString() << ")";
	std::string bytes;
	message.SerializeToString(&bytes);
	LOG(INFO)<< "MessageSender::send(bytes=[" << bytes << "], size=[" << bytes.size() << "])";
	//Buffer_t buffer(bytes.begin(), bytes.end());
	sender_->send(bytes);
}

}
}

#endif /* INCLUDE_MESSAGE_SENDER_H_ */
