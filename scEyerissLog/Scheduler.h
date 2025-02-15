#pragma once
#include <systemc>
using namespace sc_core;
using namespace sc_dt;

SC_MODULE(SCHEDULER) {
	sc_in <   bool		>		clk;
	sc_in <   bool		>		rst;
	sc_in <   bool		>		in_vld;
	
	// Configuration signals
	sc_in<  sc_bv<4>  >			filter_height_cf;
	sc_in<  sc_bv<4>  >			filter_width_cf;
	sc_in<  sc_bv<10> >			ifmap_height_cf;
	sc_in<  sc_bv<10> >			ifmap_width_cf;
	sc_in<  sc_bv<13> >			units_cf;
	sc_in<  sc_bv<7>  >			stride_cf;
	sc_in<  sc_bv<3>  >			padding_cf;
	sc_in<  sc_uint<32>>		ofmap_height_cf;
	sc_in<  sc_uint<32>>		ofmap_width_cf;
	sc_in<  sc_bv<2>  >			dataflow_cf;
	sc_in<  sc_bv<2>  >			layer_cf;
	sc_in<  sc_uint<32>>		folding_cf;
	sc_in<  sc_uint<32>>		propass_cf;

	// From GLB.
	sc_in<  sc_int<8> >			weight[filter_height];
	sc_in<  sc_int<8> >			ifmap[ifmap_height];

	// Send data to PE set.
	sc_out<    bool	  >			enable;
	sc_out<    bool	  >			in_vld_PE;
	sc_out< sc_int<8> >			weight_out_PE[PE_length][PE_width];
	sc_out<	sc_int<8> >			ifmap_out_PE[PE_length][PE_width];

	sc_signal<  bool  >			start_sche;

	// Test signal
	sc_signal<sc_int<8>>		count_pass;

	SC_CTOR(SCHEDULER) {
		SC_CTHREAD(controller, clk.pos());
		reset_signal_is(rst, true);
		SC_CTHREAD(ifmap_scheduling, clk.pos());
		reset_signal_is(rst, true);
		set_stack_size(0x1600000);
		SC_CTHREAD(weight_scheduling, clk.pos());
		reset_signal_is(rst, true);
	}
	void controller(void);
	void weight_scheduling(void);
	void ifmap_scheduling(void);
};
