#include "cascade.h"
#include "biquad.h"

cascade::cascade(){
};

cascade::~cascade(){
};

void cascade::set_cascade_coef(const std::vector<std::vector<float>>& filter_coefs) {
    for (const auto& coefs : filter_coefs) {
        biquad filter;
        filter.set_coef(coefs);
        _sos_filters.push_back(filter);
    }
}

void cascade::process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out){

    std::vector<sample_t> buffer_1(nframes);
    std::vector<sample_t> buffer_2(nframes);

    memcpy(buffer_1.data(), in, sizeof(sample_t) * nframes);

    for (auto& filter : _sos_filters) {
        filter.process(nframes, buffer_1.data(), buffer_2.data());
        std::swap(buffer_1,buffer_2);
    }

    std::copy(buffer_1.begin(), buffer_1.end(), out);

};