/*
 * multicast_discovery_test.cpp
 *
 *  Created on: Nov 9, 2016
 *      Author: natefleming
 */

#include <gtest/gtest.h>
#include <glog/logging.h>

#include "../include/configuration_test.h"
#include "debug.h"
#include "message_sender_test.h"
#include "message_receiver_test.h"
#include "dispatch_policy_test.h"
//#include "multicast_discovery_test.h"


int main(int argc, char **argv) {
  ::google::InitGoogleLogging(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
