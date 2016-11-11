#include <google/protobuf/message.h>
#include "multicast_message_receiver.h"
#include "util.h"

class moserit::roper::MulticastMessageReceiver::Impl {

public:
	 Impl() {

	 }

};

moserit::roper::
MulticastMessageReceiver::MulticastMessageReceiver() : impl_(moserit::make_unique<Impl>()) {

}

moserit::roper::
MulticastMessageReceiver::~MulticastMessageReceiver() {

}

void
moserit::roper::
MulticastMessageReceiver::on_receive(const Message_t& message) {

}




