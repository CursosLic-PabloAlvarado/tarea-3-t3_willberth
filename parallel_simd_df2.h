
#ifndef PARALLEL_SIMD_DF2_H
#define PARALLEL_SIMD_DF2_H

#include "nmmintrin.h" //SSE4.2, 128 bit operations (4 floats)
#include "immintrin.h" //AVX2, 256 bit operations (8 floats)
#include "jack_client.h"

class parallel_simd_df2 {

public:

    typedef jack::client::sample_t sample_t;

    union {
        __m128 a1_fx;
        float a1_fxx[4];
    };

    union {
        __m128 a2_fx;
        float a2_fxx[4];
    };

    union {
        __m128 b0_fx;
        float b0_fxx[4];
    };

    union {
        __m128 b1_fx;
        float b1_fxx[4];
    };

    union {
        __m128 b2_fx;
        float b2_fxx[4];
    };

    float k_x;

    parallel_simd_df2();
    ~parallel_simd_df2();

    void set_cascade_coef(const std::vector<std::vector<float>>& filter_coefs, const float k);

    void process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out);

private:

    __m128 w_n_1;
    __m128 w_n_2;
    __m128 w_n;
    __m128 x_n;
    __m128 y_n;

};



#endif //PARALLEL_SIMD_DF2_H
