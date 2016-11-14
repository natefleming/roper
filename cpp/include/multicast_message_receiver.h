/*
 * multicast_message_receiver.h
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MULTICAST_MESSAGE_RECEIVER_H_
#define INCLUDE_MULTICAST_MESSAGE_RECEIVER_H_

#include "message.h"

namespace moserit {
namespace roper {

class MulticastMessageReceiver: public MessageReceiver {

public:

	MulticastMessageReceiver();
	virtual ~MulticastMessageReceiver();

	virtual void on_receive(const Message_t& message) override;

private:

	class Impl;
	std::unique_ptr<Impl> impl_;

};

}
}

#endif /* MULTICAST_MESSAGE_RECEIVER_H_ */
