/*
 * Context.h
 *
 *  Created on: Nov 17, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_CONTEXT_H_
#define INCLUDE_CONTEXT_H_

#include "dispatch_policy.h"

namespace moserit {
namespace roper {

class Context {

public:

	Context(const std::shared_ptr<DispatchPolicy> policy = DispatchPolicy::sync_retry_policy());

	std::shared_ptr<DispatchPolicy> dispatch_policy() const;

private:

	std::shared_ptr<DispatchPolicy> policy_;

};

}
}



#endif /* INCLUDE_CONTEXT_H_ */
