/*
 * util.h
 *
 *  Created on: Nov 8, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_UTIL_H_
#define INCLUDE_UTIL_H_

namespace moserit {

template<typename T, typename ... Ts>
std::unique_ptr<T> make_unique(Ts&&... params) {
	return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

}

#endif /* INCLUDE_UTIL_H_ */
