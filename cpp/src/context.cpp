/*
 * context.cpp
 *
 *  Created on: Nov 14, 2016
 *      Author: natefleming
 */

#include <map>
#include "context.h"
#include "util.h"

namespace moserit {
namespace roper {

class Context::Impl {

public:
	Impl() : map_() {

	}

	~Impl() = default;

	Impl& merge(const Impl& rhs) {
		map_.insert(rhs.map_.begin(), rhs.map_.end());
		return *this;
	}

    std::string& operator[](const std::string& key) {
    	return map_[key];
    }

    const std::string& operator[](const std::string& key) const {

    }

private:

    std::map<std::string, std::string> map_;

};


Context::Context() : impl_(moserit::make_unique<Impl>()) {

}

Context::~Context() {

}

Context&
Context::merge(const Context& rhs) {
	impl_->merge(*rhs.impl_);
	return *this;
}

std::string&
Context::operator[](const std::string& key) {
	return (*impl_)[key];
}

const std::string&
Context::operator[](const std::string& key) const {
	return (*impl_)[key];
}

}
}



