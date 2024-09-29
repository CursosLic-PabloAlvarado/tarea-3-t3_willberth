#ifndef _CASCADE_H
#define _CASCADE_H

#include <vector>
#include "jack_client.h"
#include "biquad.h"

class cascade {

public:

cascade();
~cascade();

typedef jack_default_audio_sample_t sample_t;

void set_coef(const std::vector<std::vector<float>>& filter_coefs);

void process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out);

private:

std::vector<biquad> _sos_filters;


};



#endif