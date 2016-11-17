/*
 * multicast_receiver.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: natefleming
 */

#include <vector>
#include <memory>
#include <glog/logging.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "multicast_receiver.h"
#include "util.h"

namespace moserit {
namespace roper {

class MulticastReceiver::Impl {

	public:
		Impl(const boost::asio::ip::udp::endpoint& bind_endpoint,
				const boost::asio::ip::address& multicast_address) :
				bind_endpoint_(bind_endpoint),
				multicast_address_(multicast_address),
				io_service_(),
				socket_(nullptr),
				data_(Impl::max_length) {
		}

		void initialize() {
			LOG(INFO)<< "initialize";
			socket_ = make_socket();
		}

		void on_receive(std::function<void (const Buffer_t&)> message_handler) {
			message_handler_ = message_handler;
		}

		std::unique_ptr<boost::asio::ip::udp::socket> make_socket() {
			using boost::asio::ip::udp;
			std::unique_ptr<udp::socket> socket(
					moserit::make_unique<udp::socket>(io_service_));
			socket->open(bind_endpoint_.protocol());
			socket->set_option(udp::socket::reuse_address(true));
			socket->set_option(boost::asio::ip::multicast::enable_loopback(true));
			socket->bind(bind_endpoint_);
			socket->set_option(
					boost::asio::ip::multicast::join_group(multicast_address_));
			return socket;
		}

		void receive_from() {
			LOG(INFO) << "receive_from";
			boost::asio::ip::udp::endpoint sender_endpoint;
			socket_->async_receive_from(boost::asio::buffer(data_, max_length),
					sender_endpoint,
					boost::bind(&Impl::handle_receive_from, this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));
		}

		void handle_receive_from(
				const boost::system::error_code& error,
				size_t bytes_recvd) {
			LOG(INFO) << "handle_receive_from";
			if (!error) {
				message_handler_(data_);
				receive_from();
			}
		}

		const boost::asio::ip::udp::endpoint& bind_endpoint() const {
			return bind_endpoint_;
		}

		const boost::asio::ip::address& multicast_address() const {
			return multicast_address_;
		}

	private:

		boost::asio::ip::udp::endpoint bind_endpoint_;
		boost::asio::ip::address multicast_address_;
		boost::asio::io_service io_service_;
		std::unique_ptr<boost::asio::ip::udp::socket> socket_;
		std::function<void (const Buffer_t&)> message_handler_;

		enum {
			max_length = 1024
		};
		//char data_[max_length];
		std::vector<char> data_;
	};

}
}

moserit::roper::
MulticastReceiver::MulticastReceiver(
		const std::string& bind_address,
		const std::string& multicast_address,
		short mulitcast_port) {
	impl_ = moserit::make_unique<Impl>(
			boost::asio::ip::udp::endpoint(
					boost::asio::ip::address::from_string(bind_address),
					mulitcast_port),
			boost::asio::ip::address::from_string(multicast_address));
}

moserit::roper::
MulticastReceiver::~MulticastReceiver() {

}

void
moserit::roper::
MulticastReceiver::on_receive(std::function<void (const Buffer_t&)> message_handler) {
	impl_->on_receive(message_handler);
}



