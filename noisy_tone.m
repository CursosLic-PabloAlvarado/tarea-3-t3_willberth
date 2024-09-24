#This function generates a .wav tone with noise according to the following parameters and returns its samples:

#Parameter Fs: Sample frequency.
#Parameter s: Duration of noisy tone in seconds.
#Parameter F: Frequency of tone in Hertz.
#Parameter N: Noise Amplitude.
#Parameter gen_file: 1 to generate .wav file, otherwise is not generated.
#Parameter white_noise: Instead of a noisy tone, generate random white noise.
#Output noisy_tone: Samples of the noisy tone.

function noisy_tone=noisy_tone(Fs=48000,s=1,F,N=0.3,A=1,gen_file=1,white_noise=0);
    if(white_noise)
        f=F/Fs;
        duration_samples=Fs.*s;
        samples=[1:duration_samples];
        noise=N.*rand(1,duration_samples);
        x=@(n) A.*cos(2.*pi().*f.*n);
        noisy_tone=x(samples)+noise;
    else:
        noisy_tone=A.*rand(1,duration_samples);
    if(gen_file==1)
        audiowrite([num2str(F),"_",num2str(Fs),"_",num2str(N),"_",".wav"],noisy_tone,Fs);
    endif
endfunction