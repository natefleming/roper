/*
 * multicast_message_sender.h
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MULTICAST_MESSAGE_SENDER_H_
#define INCLUDE_MULTICAST_MESSAGE_SENDER_H_

#include "message.h"

namespace moserit {
namespace roper {

class MulticastMessageSender: public MessageSender {

public:

	MulticastMessageSender();
	virtual ~MulticastMessageSender();

	virtual void send(const Message_t& message) override;

private:

	class Impl;
	std::unique_ptr<Impl> impl_;

};

}
}

#endif /* INCLUDE_MULTICAST_MESSAGE_SENDER_H_ */
