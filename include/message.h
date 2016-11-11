/*
 * message.h
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MESSAGE_H_
#define INCLUDE_MESSAGE_H_

namespace google {
namespace protobuf {
class Message;
}
}

namespace moserit {
namespace roper {

using Message_t = ::google::protobuf::Message;

class MessageSender {

public:

		virtual ~MessageSender() {}
		virtual void send(const Message_t& message) = 0;

};

class MessageReceiver {

public:

		virtual ~MessageReceiver() {}
		virtual void on_receive(const Message_t& message) = 0;

};

}

}

#endif /* INCLUDE_MESSAGE_H_ */
