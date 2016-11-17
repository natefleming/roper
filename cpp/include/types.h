/*
 * types.h
 *
 *  Created on: Nov 16, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#include <vector>

namespace google {
namespace protobuf {
class Message;
}
}

namespace moserit {
namespace roper {

using Message_t = ::google::protobuf::Message;
using Buffer_t = std::vector<char>;

}
}



#endif /* INCLUDE_TYPES_H_ */
