/*
 * dispatch_policy.h
 *
 *  Created on: Nov 17, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_DISPATCH_POLICY_H_
#define INCLUDE_DISPATCH_POLICY_H_

#include <functional>
#include <memory>

namespace moserit {
namespace roper {

class DispatchPolicy {

public:

	static const int DEFAULT_RETRY_COUNT = 5;
	static const long DEFAULT_SLEEP_TIME_MILLIS = 1000;

	virtual void dispatch(std::function<void ()> command) = 0;

	static std::shared_ptr<DispatchPolicy> sync_retry_policy(
			int retry_count = DEFAULT_RETRY_COUNT,
			long sleep_time = DEFAULT_SLEEP_TIME_MILLIS);

	static std::shared_ptr<DispatchPolicy> async_policy();

protected:

	DispatchPolicy() {
	}

	virtual ~DispatchPolicy() {
	}

};

class RetryDispatchPolicy : public DispatchPolicy {

public:

	virtual ~RetryDispatchPolicy() {
	}

	int retry_count() const {
		return retry_count_;
	}

	long sleep_time() const {
		return sleep_time_;
	}

protected:

	RetryDispatchPolicy(int retry_count, long sleep_time);

private:

	int retry_count_;
	long sleep_time_;

};

class SyncRetryDispatchPolicy : public RetryDispatchPolicy {

	friend class DispatchPolicy;

public:

	virtual void dispatch(std::function<void ()> command);

	virtual ~SyncRetryDispatchPolicy() {
	}


private:

	SyncRetryDispatchPolicy(int retry_count, long sleep_time);

};

class AsyncDispatchPolicy : public DispatchPolicy {

	friend class DispatchPolicy;

public:

	virtual void dispatch(std::function<void ()> command);

	virtual ~AsyncDispatchPolicy() {
	}


private:

	AsyncDispatchPolicy() {
	}

};

}
}

#endif /* INCLUDE_DISPATCH_POLICY_H_ */
