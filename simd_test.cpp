
#include <iostream>
#include <parallel_simd_df2.h>

int main() {
    parallel_simd_df2 dut;
    const int nframes = 8;

    // Example input signal
    float input_signal[nframes] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    // Arrays to hold output
    float output_simd[nframes] = {0};  // SIMD output
    float output_scalar[nframes] = {0};  // Scalar output

    // Run the scalar version of the filter
    dut.process(nframes, input_signal, output_scalar);

    // Run the SIMD version of the filter (assuming the function is implemented)
    parallel_simd_df2 simd_filter;  // Assuming the SIMD filter object is defined
    simd_filter.process(nframes, input_signal, output_simd);

    // Compare results
    for (int i = 0; i < nframes; ++i) {
        std::cout << "Frame " << i << ": SIMD = " << output_simd[i] << ", Scalar = " << output_scalar[i] << std::endl;
    }

    return 0;
}
