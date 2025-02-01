#include <iostream>
#include <cmath>
#include "MAC.h"

// Log quantization function
sc_uint<12> log_quantize(sc_fixed<32, 8> x) {
    sc_uint<12> n_q;

    if (x == 0) {
        return 0xFFF;  // Reserved value for zero (all bits set)
    }

    int exponent = std::round(std::log2(std::abs(x.to_double())));  // Compute exponent
    n_q = (x > 0) ? exponent : (exponent | 0x800);  // Encode sign in MSB
    return n_q;
}

// Function for log dequantization (hardware-compatible)
sc_fixed<32, 8> log_dequantize(sc_uint<12> n_q) {
    if (n_q == 0xFFF) return sc_fixed<32, 8>(0.0);  // Special case for zero


    bool is_negative = (n_q & 0x800);  // Extract sign bit
    int exponent = n_q & 0x7FF;  // Extract 11-bit exponent

    sc_fixed<32, 8> result = std::pow(2.0, exponent);

    // Cast both branches to sc_fixed<32, 8>:
    sc_fixed<32, 8> negative = -result;
    sc_fixed<32, 8> positive = result;

    // Now the ternary operator is unambiguous:
    return is_negative ? negative : positive;
}

void MAC::mac(void) {
    sc_int<8> w;
    sc_int<8> in;
    sc_uint<12> psum_tmp;
    sc_uint<12> psum;

    w = weight.read();
    in = ifmap.read();
    psum_tmp = psum_tmp_RegtoMAC.read();

    // Perform addition in the log domain (equivalent to multiplication in the linear domain)
    sc_uint<12> log_mult = w + in;

    // Dequantize the partial sum
    sc_fixed<32, 8> dequant_psum_tmp = log_dequantize(psum_tmp);

    // Dequantize the multiplication result
    sc_fixed<32, 8> dequant_mult = log_dequantize(log_mult);

    // Perform the addition in the linear domain
    sc_fixed<32, 8> add_result = dequant_mult + dequant_psum_tmp;

    // Quantize the result back to the log domain
    sc_uint<12> quant_psum = log_quantize(add_result);

    psum_tmp_MACtoReg.write(quant_psum);

    tracker->count_mac_op();
}