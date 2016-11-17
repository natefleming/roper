/*
 * context.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: natefleming
 */

#include "context.h"

moserit::roper::
Context::Context(const std::shared_ptr<DispatchPolicy> policy) : policy_(policy) {

}

std::shared_ptr<moserit::roper::DispatchPolicy>
moserit::roper::
Context::dispatch_policy() const {
	return policy_;
}

