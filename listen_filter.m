## Grupo Wilberth
## Solución de la tarea 3.
## EL5805 Procesamiento digital de señales

## matfile: Archivo .mat con los valores para el filtro
## soundfile: Archivo .wav con el audio a probar
## Fs: Frecuencia de muestreo 

function listen_filter(matfile, soundfile, Fs = 48000)

pkg load signal

# Obteniendo las muestras del audio, y su frecuencia de muestreo
[audio sound_Fs] = audioread(soundfile);

# Si la frecuencia de muestreo del .wav es distinta a la
# Fs indicada en la función se requiere un resample del
# audio
if Fs ~= sound_Fs
    audio = resample(audio, Fs, sound_Fs);
end

# Se reproduce el audio original obtenido
sound(audio, Fs);

# Recuperando la matriz SOS del archivo
Data = load(matfile, "SOS");

# Se combinan o transforman los sistemas de segundo orden
[B A] = sos2tf(Data.SOS);

# Aplicando el filtro al audio
audio_filtered = filter(B, A, audio);

# Reproduciendo el audio filtrado
sound(audio_filtered, Fs);
