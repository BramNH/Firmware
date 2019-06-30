/**
 * @file rc_data.hpp
 *
 * @author Bram Nijenhuis <bramnijenhuis99@gmail.com>
 */

#pragma once

#include <uavcan/uavcan.hpp>
#include <uavcan/equipment/input_rc/inputRC.hpp>

#include <perf/perf_counter.h>
#include <uORB/topics/input_rc.h>

class UavcanRcDataController
{
	public:
		UavcanRcDataController(uavcan::INode &node);
		~UavcanRcDataController();

		/*
		 * Publishes the channel data to the CAN bus
		 */
		void update_outputs(uint16_t output[18]);

	private:
		/*
		 * Max update rate to avoid exessive bus traffic
		 */
		static constexpr unsigned	MAX_RATE_HZ = 5;
		/*
		 * libuavcan related things
		 */
		 uavcan::MonotonicTime _prev_cmd_pub; ///< rate limiting
		 uavcan::INode &_node;
		/*
		 * Publishes data over CAN bus
		 */
		 uavcan::Publisher<uavcan::equipment::input_rc::InputRC> _uavcan_pub_raw_cmd;
};
