/*
 * dispatch_policy.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: natefleming
 */

#include <memory>
#include <future>
#include <chrono>
#include <thread>
#include <glog/logging.h>
#include <boost/range/irange.hpp>
#include "dispatch_policy.h"
#include "util.h"

std::shared_ptr<moserit::roper::DispatchPolicy>
moserit::roper::
DispatchPolicy::sync_retry_policy(int retry_count, long sleep_time_mills) {
	auto policy(
			std::shared_ptr<SyncRetryDispatchPolicy>(
					new SyncRetryDispatchPolicy(retry_count, sleep_time_mills)));
	return policy;
}

std::shared_ptr<moserit::roper::DispatchPolicy>
moserit::roper::
DispatchPolicy::async_policy() {
	auto policy(std::shared_ptr<AsyncDispatchPolicy>(new AsyncDispatchPolicy));
	return policy;
}

moserit::roper::
RetryDispatchPolicy::RetryDispatchPolicy(int retry_count, long sleep_time) :
		retry_count_(retry_count), sleep_time_(sleep_time) {

}

moserit::roper::
SyncRetryDispatchPolicy::SyncRetryDispatchPolicy(
		int retry_count, long sleep_time) :
		RetryDispatchPolicy(retry_count, sleep_time) {

}

void
moserit::roper::
SyncRetryDispatchPolicy::dispatch(
		std::function<void()> command) {
	LOG(INFO)<< "dispatch";
	std::unique_ptr<std::exception> exception(nullptr);
	for(auto i : boost::irange(0, retry_count())) {
		try {
			command();
			exception.reset(nullptr);
			break;
		} catch (const std::exception& e){
			LOG(ERROR) << e.what();
			exception = moserit::make_unique<std::exception>(e);
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time()));
		}
	}
	if(exception) {
		throw *exception;
	}
}

void
moserit::roper::
AsyncDispatchPolicy::dispatch(
	std::function<void()> command) {
	LOG(INFO)<< "dispatch";
	std::future<void> future(std::async(command));
}
