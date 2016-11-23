/*
 * multicast_sender.cpp
 *
 *  Created on: Nov 11, 2016
 *      Author: natefleming
 */

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <glog/logging.h>
#include "multicast_sender.h"
#include "util.h"

namespace moserit {
namespace roper {

class MulticastSender::Impl {

public:

	Impl(boost::asio::io_service& io_service,
			const boost::asio::ip::udp::endpoint& endpoint) :
			endpoint_(endpoint),
			socket_(io_service, endpoint.protocol()) {
		LOG(INFO) << "MulticastSender::Impl::Impl";
	}

	void send(const Buffer_t& data) {
		LOG(INFO) << "MulticastSender::Impl::send";
		LOG(INFO) << "Sending data=[" << data << "] to endpoint=[" << endpoint_ << "]";
		socket_.async_send_to(
				boost::asio::buffer(data),
				endpoint_,
				boost::bind(&Impl::handle_send_to, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}

	void handle_send_to(const boost::system::error_code& error, std::size_t bytes_sent) {
		LOG(INFO) << "MulticastSender::Impl::handle_send_to(bytes_sent=" << bytes_sent << ")";
		if (error) {
			LOG(ERROR) << error.message();
		}
	}

private:

	boost::asio::ip::udp::endpoint endpoint_;
	boost::asio::ip::udp::socket socket_;

};

}
}

moserit::roper::
MulticastSender::MulticastSender(
		boost::asio::io_service& io_service,
		const std::string& multicast_address,
		short port) {
	LOG(INFO) << "MulticastSender::MulticastSender";
	impl_ = moserit::make_unique<Impl>(
			io_service,
			boost::asio::ip::udp::endpoint(
					boost::asio::ip::address::from_string(multicast_address),
					port));
}

moserit::roper::
MulticastSender::~MulticastSender() {
	LOG(INFO) << "MulticastSender::~MulticastSender";
}

void moserit::roper::
MulticastSender::send(const Buffer_t& buffer) {
	LOG(INFO) << "MulticastSender::send";
	impl_->send(buffer);
}

