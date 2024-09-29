#include "cascade.h"
#include "biquad.h"

cascade::cascade(){
    
};

cascade::~cascade(){
};

void cascade::set_coef(const std::vector<std::vector<float>>& filter_coefs) {
    _sos_filters.clear(); 

        // Loop through each set of coefficients and initialize a biquad filter
        for (const auto& coefs : filter_coefs) {
            if (coefs.size() == 6) { // Ensure we have exactly 6 coefficients for each biquad
                biquad filter;
                filter.set_coef(coefs); // Set the coefficients for this biquad
                _sos_filters.push_back(filter);
        }
    }
}

void cascade::process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out){
    const sample_t* current_input = in;  // Start with the input pointer

    for (auto& filter : _sos_filters) {
        filter.process(nframes, current_input, out);  

        current_input = out;
    }

};