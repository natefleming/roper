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

#include "util.h"
#include "../include/configuration.h"

namespace moserit {
namespace roper {

class Configuration::Impl {

public:
	Impl() :
			map_() {
	}

	~Impl() = default;

	Impl& merge(const Impl& rhs) {
		map_.insert(rhs.map_.begin(), rhs.map_.end());
		return *this;
	}

	Configuration::Value& at(const std::string& key) {
		return map_.at(key);
	}

	void insert(const std::string& key, const Configuration::Value& value) {
		map_.insert(std::make_pair(key, value));
	}

private:

	std::map<std::string, Configuration::Value> map_;

};

}
}

moserit::roper::
Configuration::Configuration() :
		impl_(moserit::make_unique<Impl>()) {

}

moserit::roper::
Configuration::~Configuration() {

}

moserit::roper::Configuration&
moserit::roper::
Configuration::merge(const Configuration& rhs) {
	impl_->merge(*rhs.impl_);
	return *this;
}

moserit::roper::Configuration::Value&
moserit::roper::
Configuration::at(const std::string& key) {
	return impl_->at(key);
}

void
moserit::roper::
Configuration::insert(const std::string& key, const Configuration::Value& value) {
	impl_->insert(key, value);
}

void load(std::ifstream& fin, moserit::roper::Configuration& configuration) {
	std::string line;
	while (std::getline(fin, line)) {
		if (line.length() > 0 && line[0] != '#') {
			std::istringstream lineStream(line);
			std::string key;
			std::string value;
			char delim;
			if ((lineStream >> key >> delim >> value) && (delim == '=')) {
				moserit::roper::Configuration::Value v(value);
				configuration.insert(key, v);
			}
		}

	}
}


