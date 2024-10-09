#include "parallel_simd_tdf2.h"


parallel_simd_tdf2::parallel_simd_tdf2() {
    w_n = _mm_setzero_ps();
    w_1_n = _mm_setzero_ps();
    w_2_n = _mm_setzero_ps();
    w_1_n_1 = _mm_setzero_ps();
    w_2_n_1 = _mm_setzero_ps();
    y_n = _mm_setzero_ps();
    x_n = _mm_setzero_ps();
}

parallel_simd_tdf2::~parallel_simd_tdf2() {
}

void parallel_simd_tdf2::set_cascade_coef(const std::vector<std::vector<float> > &filter_coefs) {
    // Se realiza un ciclo para todos los vectores de coeficientes
    int index = 0;
    for (const auto &coefs: filter_coefs) {
        b0_fxx[index] = coefs[0];
        b1_fxx[index] = coefs[1];
        b2_fxx[index] = coefs[2];
        a1_fxx[index] = coefs[4];
        a2_fxx[index] = coefs[5];

        index++;
    }
}

void parallel_simd_tdf2::process(jack_nframes_t nframes, const sample_t *const in, sample_t *const out) {
    const sample_t *start_ptr = in; //Puntero al inicio del buffer de entrada
    const sample_t *end_ptr = in + nframes; //Puntero al final del buffer de entrada
    sample_t *out_ptr = out; //Puntero al inicio del buffer de salida

    while (start_ptr != end_ptr) {
        // Se realiza la implementación del filtro por medio de las ecuaciones de diferencias
        x_n = _mm_set1_ps(*start_ptr);
        y_n = _mm_fmadd_ps(b0_fx, x_n, w_1_n_1);
        w_1_n = _mm_add_ps( _mm_fmsub_ps(b1_fx, x_n, _mm_mul_ps(a1_fx, y_n)), w_2_n_1);
        w_2_n = _mm_fmsub_ps(b2_fx, x_n, _mm_mul_ps(a2_fx, y_n));

        //Tomado de: https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-sse-vector-sum-or-other-reduction
        static __m128 shuf = _mm_movehdup_ps(y_n); // broadcast elements 3,1 to 2,0
        static __m128 sums = _mm_add_ps(y_n, shuf);
        shuf = _mm_movehl_ps(shuf, sums); // high half -> low half
        sums = _mm_add_ss(sums, shuf);
        *out_ptr = _mm_cvtss_f32(sums);

        // Se incrementan los punteros
        start_ptr++;
        out_ptr++;

        w_1_n_1 = w_1_n;
        w_2_n_1 = w_2_n;

    }
}
