/*
 * multicast_receiver.h
 *
 *  Created on: Nov 16, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MULTICAST_RECEIVER_H_
#define INCLUDE_MULTICAST_RECEIVER_H_

#include <functional>
#include <string>
#include "types.h"

namespace moserit {
namespace roper {

class MulticastReceiver {

public:

	MulticastReceiver(
			boost::asio::io_service& io_service,
			const std::string& bind_address,
			const std::string& multicast_address,
			short mulitcast_port);

	MulticastReceiver(
			boost::asio::io_service& io_service,
			const std::string& multicast_address,
			short mulitcast_port);

	virtual ~MulticastReceiver();

	virtual void on_receive(std::function<void (const Buffer_t&)> message_handler);

private:

	class Impl;
	std::unique_ptr<Impl> impl_;

};

}
}




#endif /* INCLUDE_MULTICAST_RECEIVER_H_ */
