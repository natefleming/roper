/*
 * types.h
 *
 *  Created on: Nov 16, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#include <iostream>
#include <vector>

namespace google {
namespace protobuf {
class Message;
}
}

namespace moserit {
namespace roper {

using Message_t = ::google::protobuf::Message;
//using Buffer_t = std::vector<char>;
using Buffer_t = std::string;

inline std::ostream& operator<<(std::ostream& os, const std::vector<char>& buffer) {
	for (auto i = buffer.begin(); i != buffer.end(); ++i) {
		os << *i << ',';
	}
	return os;
}

}
}



#endif /* INCLUDE_TYPES_H_ */
