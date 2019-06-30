/**
 * @file rc_data.cpp
 *
 * @author Bram Nijenhuis <bramnijenhuis99@gmail.com>
 */

#include "rc_data.hpp"
#include <systemlib/err.h>

UavcanRcDataController::UavcanRcDataController(uavcan::INode &node) :
	_node(node),
	_uavcan_pub_raw_cmd(node)
{
}

UavcanRcDataController::~UavcanRcDataController() {}

void UavcanRcDataController::update_outputs(uint16_t output[18]) {

	// Max update rate to avoid exessive bus traffic
	const auto timestamp = _node.getMonotonicTime();
	if ((timestamp - _prev_cmd_pub).toUSec() < (1000000 / MAX_RATE_HZ)) {
		return;
	}
	_prev_cmd_pub = timestamp;

	// DSDL generated header
	uavcan::equipment::input_rc::InputRC msg;
	// Pushes all values into the dynamic array
	for (int i = 0; i < 18; i++) {
		msg.values.push_back(output[i]);
	}

	// Mavlink test print if data structure array is correctly filled,
	// Can be removed
  PX4_INFO("-----------------------");
	for (int i = 0; i < 18; i++) {
		PX4_INFO("msg.values[%d] = [%d]", i, msg.values[i]);
	}
	PX4_INFO("----------------------");

	(void)_uavcan_pub_raw_cmd.broadcast(msg);
}
