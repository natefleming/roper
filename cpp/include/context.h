/*
 * context.h
 *
 *  Created on: Nov 14, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_CONTEXT_H_
#define INCLUDE_CONTEXT_H_

#include <iostream>
#include <memory>
#include <boost/lexical_cast.hpp>

namespace moserit {
namespace roper {

class Context {

public:

	class Value {
	public:
		Value(const Context::Value& value) :
				value_(value.value_) {
		}

		Value(const std::string& value) :
				value_(value) {
		}

		template<typename T>
		T& as() {
			return boost::lexical_cast<T&>(value_);
		}

		template<typename T>
		const T& as() const {
			return boost::lexical_cast<const T&>(value_);
		}

	private:

		std::string value_;

	};

	Context();
	virtual ~Context();

	Context& merge(const Context& rhs);

	Context::Value& at(const std::string& key);

	void insert(const std::string& key, const Context::Value& value);

private:

	class Impl;
	std::unique_ptr<Impl> impl_;

};

}
}

#endif /* INCLUDE_CONTEXT_H_ */
