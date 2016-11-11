/*
 * debug.h
 *
 *  Created on: Nov 10, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_


#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <glog/logging.h>

namespace moserit {

	class StaticInitialization {
	public:
		StaticInitialization() {
			FLAGS_logtostderr = true;
			//FLAGS_minloglevel = 0;
		}
	};

	const static StaticInitialization STATIC_INIT;

	const std::string DEFAULT_LOG_LEVEL = "INFO";
	const std::map<std::string, int> LOG_LEVELS = {
			{"INFO", 0},
			{"WARNING", 1},
			{"ERROR", 2},
			{"FATAL", 3}
	};

	static inline void set_log_level(const std::string& log_level) throw (std::invalid_argument) {
		std::string l(log_level);
		std::transform(l.begin(), l.end(), l.begin(), ::toupper);
		std::map<std::string, int>::const_iterator found(LOG_LEVELS.find(l));
		if (found == LOG_LEVELS.end()) {
			throw std::invalid_argument("invalid log level [" + log_level + "]");
		}
		FLAGS_minloglevel = found->second;
	}

	static inline void set_log_directory(const std::string& directory) {
		if(boost::trim_copy(directory).empty()) return;
		FLAGS_logtostderr = false;
		FLAGS_log_dir = directory;
	}
}



#endif /* INCLUDE_DEBUG_H_ */
