/*
 * MulticastDiscovery.h
 *
 *  Created on: Nov 8, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_MULTICAST_DISCOVERY_H_
#define INCLUDE_MULTICAST_DISCOVERY_H_

#include <string>

#include "life_cycle_aware.h"
#include "discovery.h"

namespace moserit {

	namespace roper {

		class MulticastDiscovery : public Discovery, public LifeCycleAware {

		friend class MulticastDiscoveryTest;

		public:

			MulticastDiscovery(
					const std::string& listen_address,
					const std::string& multicast_address,
					short mulitcast_port);

			MulticastDiscovery(
					const std::string& multicast_address,
					short mulitcast_port);
		/*
			MulticastDiscovery(MulticastDiscovery&& rhs);
			MulticastDiscovery(const MulticastDiscovery& rhs);
			MulticastDiscovery& operator=(MulticastDiscovery&& rhs);
			MulticastDiscovery& operator=(const MulticastDiscovery& rhs);
		*/
			virtual ~MulticastDiscovery();

			virtual void initialize() override;
			virtual void start() override;
			virtual void stop() override;
			virtual void terminate() override;
			virtual void await_termination() override;

			virtual void publish() override;
			virtual void subscribe() override;

			class Builder : public Discovery::Builder<MulticastDiscovery> {

		    public:

		        virtual std::shared_ptr<MulticastDiscovery> build() override {
		        	return std::make_shared<MulticastDiscovery>(
		        			bind_address_,
							multicast_address_,
							port_);
		        }

		        Builder& with_bind_endpoint(const std::string& bind_address, short port) {
		        	bind_address_ = bind_address;
		        	port_ = port;
		        	return *this;
		        }

		        Builder& with_multicast_address(const std::string& multicast_address) {
		        	multicast_address_ = multicast_address;
		        	return *this;
		        }

		    private:

		        std::string bind_address_;
		        std::string multicast_address_;
				short port_;

			};

		private:

		   class Impl;
		   std::unique_ptr<Impl> impl_;

		};

	}

}


#endif /* INCLUDE_MULTICAST_DISCOVERY_H_ */
