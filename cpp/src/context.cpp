/*
 * context.cpp
 *
 *  Created on: Nov 14, 2016
 *      Author: natefleming
 */

#include <map>
#include <fstream>
#include <string>
#include <sstream>

#include "context.h"
#include "util.h"

namespace moserit {
namespace roper {

class Context::Impl {

public:
	Impl() :
			map_() {
	}

	~Impl() = default;

	Impl& merge(const Impl& rhs) {
		map_.insert(rhs.map_.begin(), rhs.map_.end());
		return *this;
	}

	Context::Value& at(const std::string& key) {
		return map_.at(key);
	}

	void insert(const std::string& key, const Context::Value& value) {
		map_.insert(std::make_pair(key, value));
	}

private:

	std::map<std::string, Context::Value> map_;

};

Context::Context() :
		impl_(moserit::make_unique<Impl>()) {

}

Context::~Context() {

}

Context&
Context::merge(const Context& rhs) {
	impl_->merge(*rhs.impl_);
	return *this;
}

Context::Value&
Context::at(const std::string& key) {
	return impl_->at(key);
}

void Context::insert(const std::string& key, const Context::Value& value) {
	impl_->insert(key, value);
}

void load(std::ifstream& fin, Context& context) {
	std::string line;
	while (std::getline(fin, line)) {
		if (line.length() > 0 && line[0] != '#') {
			std::istringstream lineStream(line);
			std::string key;
			std::string value;
			char delim;
			if ((lineStream >> key >> delim >> value) && (delim == '=')) {
				Context::Value v(value);
				context.insert(key, v);
			}
		}

	}
}

}
}

