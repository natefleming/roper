/*
 * life_cycle_aware.h
 *
 *  Created on: Nov 8, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_LIFE_CYCLE_AWARE_H_
#define INCLUDE_LIFE_CYCLE_AWARE_H_

namespace moserit {

	namespace roper {

		class LifeCycleAware {

		public:

			virtual ~LifeCycleAware() {}

			virtual void initialize() = 0;
			virtual void start() = 0;
			virtual void stop() = 0;
			virtual void terminate() = 0;
			virtual void await_termination() = 0;

		};
	}
}





#endif /* INCLUDE_LIFE_CYCLE_AWARE_H_ */
