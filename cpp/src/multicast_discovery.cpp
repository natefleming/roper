/*
 * multicast_discovery.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: natefleming
 */

#include <iostream>
#include <future>
#include <glog/logging.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "multicast_discovery.h"
#include "discovery.pb.h"
#include "util.h"

class moserit::roper::MulticastDiscovery::Impl {

public:
	Impl(const boost::asio::ip::udp::endpoint& bind_endpoint,
			const boost::asio::ip::address& multicast_address) :
			bind_endpoint_(bind_endpoint), multicast_address_(
					multicast_address), io_service_(), socket_(nullptr), is_running_(
					false) {
	}

	void initialize() {
		LOG(INFO)<< "initialize";
		socket_ = make_socket();
	}

	void start() {
		LOG(INFO) << "start";
		if (is_running_) return;
		is_running_ = true;
		receive_from();
		future_  = std::async([this]()->int{
			return io_service_.run();
		});
	}

	void stop() {
		LOG(INFO) << "stop";
		if (!is_running_) return;
		is_running_ = false;
		io_service_.stop();
	}

	void terminate() {
		LOG(INFO) << "terminate";
		io_service_.stop();
	}

	void await_termination() {
		LOG(INFO) << "terminate";
		future_.get();
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
			std::cout.write(data_, bytes_recvd) << std::endl;
			DiscoveryEvent discovery_event;
			discovery_event.ParseFromArray(data_, bytes_recvd);
			receive_from();
		}
	}

	const boost::asio::ip::udp::endpoint& bind_endpoint() const {
		return bind_endpoint_;
	}

	const boost::asio::ip::address& multicast_address() const {
		return multicast_address_;
	}

	const bool is_running() const {
		return is_running_;
	}

private:

	std::future<int> future_;
	boost::asio::ip::udp::endpoint bind_endpoint_;
	boost::asio::ip::address multicast_address_;
	boost::asio::io_service io_service_;
	std::unique_ptr<boost::asio::ip::udp::socket> socket_;
	bool is_running_;

	enum {
		max_length = 1024
	};
	char data_[max_length];
};

moserit::roper::
MulticastDiscovery::MulticastDiscovery(
		const std::string& bind_address, const std::string& multicast_address,
		short mulitcast_port) {
	impl_ = moserit::make_unique<Impl>(
			boost::asio::ip::udp::endpoint(
					boost::asio::ip::address::from_string(bind_address),
					mulitcast_port),
			boost::asio::ip::address::from_string(multicast_address));
}

moserit::roper::
MulticastDiscovery::MulticastDiscovery(
		const std::string& multicast_address, short mulitcast_port) {
}

moserit::roper::
MulticastDiscovery::~MulticastDiscovery() {
}

void moserit::roper::
MulticastDiscovery::initialize() {
	impl_->initialize();
}

void moserit::roper::
MulticastDiscovery::start() {
	impl_->start();
}

void moserit::roper::
MulticastDiscovery::stop() {
	impl_->stop();
}

void moserit::roper::
MulticastDiscovery::terminate() {
	impl_->terminate();
}

void moserit::roper::
MulticastDiscovery::await_termination() {
	impl_->await_termination();
}

void moserit::roper::
MulticastDiscovery::publish() {

}

void moserit::roper::
MulticastDiscovery::subscribe() {

}
