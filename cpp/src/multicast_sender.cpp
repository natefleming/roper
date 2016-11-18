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

	Impl(const boost::asio::ip::udp::endpoint& endpoint) :
			io_service_(), endpoint_(endpoint), socket_(io_service_, endpoint.protocol()) {
		LOG(INFO) << "MulticastSender::Impl::Impl";
		using boost::asio::ip::udp;
		socket_.set_option(udp::socket::reuse_address(true));
		socket_.set_option(boost::asio::ip::multicast::enable_loopback(true));
	}

	void send(const Buffer_t& data) {
		socket_.async_send_to(boost::asio::buffer(data), endpoint_,
				boost::bind(&Impl::handle_send_to, this,
						boost::asio::placeholders::error));
		LOG(INFO) << "MulticastSender::Impl::send";
	}

	void handle_send_to(const boost::system::error_code& error) {
		LOG(INFO) << "MulticastSender::Impl::handle_send_to(error=" << error.message() << ")";
		if (!error) {

		}
	}

private:

	boost::asio::io_service io_service_;
	boost::asio::ip::udp::endpoint endpoint_;
	boost::asio::ip::udp::socket socket_;

};

}
}

moserit::roper::
MulticastSender::MulticastSender(
		const std::string& multicast_address, short port) {
	LOG(INFO) << "MulticastSender::MulticastSender";
	impl_ = moserit::make_unique<Impl>(
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

