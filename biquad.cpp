
#include "biquad.h"

#include <csignal>
#include <boost/program_options/errors.hpp>

biquad::biquad() : sample_rate(48000), w_n(buffer_size) {
}

biquad::~biquad() = default;

void biquad::set_coefficients(const std::vector<float> *coefficients) {
    if(coefficients->size() == 6) {
        b0 = (*coefficients)[0];
        b1 = (*coefficients)[1];
        b2 = (*coefficients)[2];
        a0 = 1.0;
        a1 = (*coefficients)[4];
        a2 = (*coefficients)[5];

    }else {
        throw std::runtime_error("Got a coefficient row vector of unexpected length");
    }
}

void biquad::process(jack_nframes_t nframes, const sample_t *const in, sample_t *const out) {
    const sample_t* startptr = in;          //Puntero al inicio del buffer de entrada
    const sample_t* endptr=in+nframes;    //Puntero al final del buffer de entrada
    sample_t* outptr=out;                 //Puntero al inicio del buffer de salida

    while (startptr != endptr) {
        w_n.push_back( -a1*w_n.back() - a2 * *(w_n.rbegin() + 1) + *startptr );
        *outptr = b0*w_n.back() + b1 * *(w_n.rbegin() + 1) + b2 * *(w_n.rbegin() + 2);
        startptr++;
        outptr++;
    }
}




