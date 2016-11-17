/*
 * multicast_sender.h
 *
 *  Created on: Nov 11, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MULTICAST_SENDER_H_
#define INCLUDE_MULTICAST_SENDER_H_

#include "types.h"

namespace moserit {
namespace roper {

class MulticastSender {


public:

	MulticastSender(const std::string& multicast_address, short port);
	virtual ~MulticastSender();

	virtual void send(const Buffer_t& message);


private:

	class Impl;
	std::unique_ptr<Impl> impl_;

};

}
}

#endif /* INCLUDE_MULTICAST_SENDER_H_ */
