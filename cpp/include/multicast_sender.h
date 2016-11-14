/*
 * multicast_sender.h
 *
 *  Created on: Nov 11, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MULTICAST_SENDER_H_
#define INCLUDE_MULTICAST_SENDER_H_

namespace moserit {
namespace roper {

class MulticastSender {

	using Buffer_t = std::vector<char>;

public:

	MulticastSender(const std::string& multicast_address, short port);
	virtual ~MulticastSender();

	virtual void send(Buffer_t message);

private:

	class Impl;
	std::unique_ptr<Impl> impl_;

};

}
}

#endif /* INCLUDE_MULTICAST_SENDER_H_ */
