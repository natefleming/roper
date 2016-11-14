#include <iostream>
#include <cstdlib>
#include <csignal>

#include <glog/logging.h>
#include <grpc++/grpc++.h>

#include <boost/program_options.hpp>

#include "multicast_discovery.h"
#include "debug.h"

const std::string DEFAULT_BIND_ADDRESS("0.0.0.0");


boost::program_options::variables_map
parse_args(int argc, char** argv) {
	namespace po = boost::program_options;
	po::variables_map vm;

	po::options_description description("Options");
	description.add_options()
			("bind-address,b", po::value<std::string>()->default_value(DEFAULT_BIND_ADDRESS), "The bind address")
			("multicast-address,m", po::value<std::string>()->required(), "The multicast address")
			("port,p", po::value<short>()->required(), "The bind port")
			("log-level", po::value<std::string>()->default_value(moserit::DEFAULT_LOG_LEVEL), "The log level [INFO,WARNING,ERROR,FATAL]")
			("log-dir", po::value<std::string>()->default_value(""), "The log directory")
			("help,h", "Print this help message");
	try {
		auto parsed_options(po::parse_command_line(argc, argv, description));
		po::store(parsed_options, vm);
		if(vm.count("help")) {
			std::cerr << description << std::endl;
			std::exit(EXIT_SUCCESS);
		}
		vm.notify();
	} catch(po::error& e) {
		LOG(ERROR) << e.what();
		std::exit(EXIT_FAILURE);
	}
	return vm;
}

using namespace moserit::roper;


std::shared_ptr<MulticastDiscovery> discovery(nullptr);

void signal_handler(int signal) {
	LOG(INFO) << "signal_handler(" << signal << ")";
	if(discovery) {
		discovery->terminate();
	}
}

int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);
	std::signal(SIGINT, signal_handler);
	auto vm = parse_args(argc, argv);
	auto multicast_address(vm["multicast-address"].as<std::string>());
	auto bind_address(vm["bind-address"].as<std::string>());
	auto port(vm["port"].as<short>());
	auto log_level(vm["log-level"].as<std::string>());
	auto log_dir(vm["log-dir"].as<std::string>());
	moserit::set_log_level(log_level);
	moserit::set_log_directory(log_dir);

	MulticastDiscovery::Builder builder;
	discovery =
			builder.with_bind_endpoint(bind_address, port)
			.with_multicast_address(multicast_address)
			.build();
	discovery->initialize();
	discovery->start();
	discovery->await_termination();
	return EXIT_SUCCESS;

}
