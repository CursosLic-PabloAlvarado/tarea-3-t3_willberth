#include "cascade.h"
#include "biquad.h"

cascade::cascade(){
    std::vector<float> coeffs = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    _sos_filter_1.set_coef(coeffs);
    coeffs = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    _sos_filter_2.set_coef(coeffs);
    coeffs = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    _sos_filter_3.set_coef(coeffs);
};

cascade::~cascade(){
};

void cascade::set_coef(const std::vector<std::vector<float>>& filter_coefs) {
    if (filter_coefs.size() >= 2) { 
        _sos_filter_1.set_coef(filter_coefs[0]);
        _sos_filter_2.set_coef(filter_coefs[1]);
    } 
    
    if (filter_coefs.size() == 3){
        _sos_filter_3.set_coef(filter_coefs[2]);
    }

}

void cascade::process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out){
    _sos_filter_1.process(nframes,in,out);
    _sos_filter_2.process(nframes,out,out);
    _sos_filter_3.process(nframes,out,out);
};