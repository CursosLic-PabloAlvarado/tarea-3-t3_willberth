

#ifndef BIQUAD_H
#define BIQUAD_H
#include <vector>
#include <boost/circular_buffer.hpp>
#include <jack/types.h>

class biquad {
public:

    biquad();
    ~biquad();

    float a0, a1, a2, b0, b1, b2;
    unsigned long sample_rate;
    unsigned long buffer_size = sample_rate * 6;

    typedef jack_default_audio_sample_t sample_t;
    boost::circular_buffer<sample_t> w_n;

    void set_coefficients(const std::vector<float> *coefficients);
    void process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out);

};



#endif //BIQUAD_H
