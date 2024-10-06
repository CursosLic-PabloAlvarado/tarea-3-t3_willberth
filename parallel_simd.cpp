#include "parallel_simd.h"

parallel_simd::parallel_simd() {
    w_n = _mm_setzero_ps();
    w_n_1 = _mm_setzero_ps();
    w_n_2 = _mm_setzero_ps();
    y_n = _mm_setzero_ps();
    x_n = _mm_setzero_ps();

}
parallel_simd::~parallel_simd() {

}

void parallel_simd::set_cascade_coef(const std::vector<std::vector<float> > &filter_coefs) {
    // Se realiza un ciclo para todos los vectores de coeficientes
    int index = 0;
    for (const auto& coefs : filter_coefs) {
        b0_fxx[index] = coefs[0];
        b1_fxx[index] = coefs[1];
        b2_fxx[index] = coefs[2];
        a1_fxx[index] = coefs[4];
        a2_fxx[index] = coefs[5];

        index++;
    }
}

void parallel_simd::process(jack_nframes_t nframes, const sample_t *const in, sample_t *const out) {
    const sample_t* start_ptr = in;        //Puntero al inicio del buffer de entrada
    const sample_t* end_ptr=in+nframes;    //Puntero al final del buffer de entrada
    sample_t* out_ptr=out;                 //Puntero al inicio del buffer de salida

    while(start_ptr!=end_ptr){
        // Se realiza la implementación del filtro por medio de las ecuaciones de diferencias
        x_n = _mm_set1_ps( *start_ptr );
        w_n = _mm_add_ps( _mm_fnmsub_ps( a1_fx, w_n_1, _mm_mul_ps(a2_fx, w_n_2) ), x_n );
        y_n = _mm_add_ps( _mm_fmadd_ps( b0_fx, w_n, _mm_mul_ps( b1_fx, w_n_1 )), _mm_mul_ps( b2_fx , w_n_2 ) );

        //Tomado de: https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-sse-vector-sum-or-other-reduction
        static __m128 shuf = _mm_movehdup_ps(y_n);        // broadcast elements 3,1 to 2,0
        static __m128 sums = _mm_add_ps(y_n, shuf);
        shuf        = _mm_movehl_ps(shuf, sums); // high half -> low half
        sums        = _mm_add_ss(sums, shuf);
        *out_ptr    = _mm_cvtss_f32(sums);

        w_n_2 = w_n_1;
        w_n_1 = w_n;

        // Se incrementan los punteros
        start_ptr++;
        out_ptr++;
    }
}
