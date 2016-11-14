/*
 * context.h
 *
 *  Created on: Nov 14, 2016
 *      Author: natefleming
 */

#ifndef INCLUDE_CONTEXT_H_
#define INCLUDE_CONTEXT_H_

#include <string>

namespace moserit {
namespace roper {

class Context {

public:

	Context();
	virtual ~Context();

	Context& merge(const Context& rhs);

    std::string& operator[](const std::string& key);
    const std::string& operator[](const std::string& key) const;

private:

    class Impl;
    std::unique_ptr<Impl> impl_;

};

}
}


#endif /* INCLUDE_CONTEXT_H_ */
