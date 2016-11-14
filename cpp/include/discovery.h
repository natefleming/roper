/*
 * discovery.h
 *
 *  Created on: Nov 8, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_DISCOVERY_H_
#define INCLUDE_DISCOVERY_H_

namespace moserit {
namespace roper {

class Discovery {

	class SubscriptionEvent {

	};

	class PublicationEvent {
	public:
		PublicationEvent() {

		}
	};

public:

	virtual ~Discovery() {
	}

	virtual void publish() = 0;
	virtual void subscribe() = 0;

	template<typename T>
	class Builder {

	public:

		virtual std::shared_ptr<T> build() = 0;

	};

};

}
}

#endif /* INCLUDE_DISCOVERY_H_ */
