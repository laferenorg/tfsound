// MIT License

// Copyright (c) 2021 laferenorg

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>

// Library C
#include <stdio.h>
#include <stdlib.h>

// Library C++
#include <queue>
#include <cmath>

#include "../../include/SDL2/SDL.h"
#include "../../include/SDL2/SDL_audio.h"
#include "../../header/deps/sound.hpp"

// structure of BeepObject
struct BeepObject
{
    double freq;
    int samplesLeft;
};

// class for beeper
class Beeper {
    private:
        double v;
        std::queue<BeepObject> beeps;
    public:
        Beeper();
        ~Beeper();
        void beep(double freq, int duration);
        void generateSamples(Sint16 *stream, int length);
        void wait();
};

// function audio callback
void audio_callback(void*, Uint8*, int);

// variable for settings
const int AMPLITUDE = 28000;
const int FREQUENCY = 44100;

// function contructor prototype
Beeper::Beeper() {
    SDL_AudioSpec desiredSpec;

    desiredSpec.freq = FREQUENCY;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audio_callback;
    desiredSpec.userdata = this;

    SDL_AudioSpec obtainedSpec;

    // you might want to look for errors here
    SDL_OpenAudio(&desiredSpec, &obtainedSpec);

    // start play audio
    SDL_PauseAudio(0);
}

// function deconstructor prototype
Beeper::~Beeper() {
    SDL_CloseAudio();
}

// function generate sample
void Beeper::generateSamples(Sint16 *stream, int length)
{
    int i = 0;
    while (i < length) {

        if (beeps.empty()) {
            while (i < length) {
                stream[i] = 0;
                i++;
            }
            return;
        }
        BeepObject& bo = beeps.front();

        int samplesToDo = std::min(i + bo.samplesLeft, length);
        bo.samplesLeft -= samplesToDo - i;

        while (i < samplesToDo) {
            stream[i] = AMPLITUDE * std::sin(v * 2 * M_PI / FREQUENCY);
            i++;
            v += bo.freq;
        }

        if (bo.samplesLeft == 0) {
            beeps.pop();
        }
    }
}

// function prototype beepe
void Beeper::beep(double freq, int duration)
{
    BeepObject bo;
    bo.freq = freq;
    bo.samplesLeft = duration * FREQUENCY / 1000;

    SDL_LockAudio();
    beeps.push(bo);
    SDL_UnlockAudio();
}

// function protype wait
void Beeper::wait()
{
    int size;
    do {
        SDL_Delay(20);
        SDL_LockAudio();
        size = beeps.size();
        SDL_UnlockAudio();
    } while (size > 0);

}

// function prototype audio_callback
void audio_callback(void *_beeper, Uint8 *_stream, int _length)
{
    Sint16 *stream = (Sint16*) _stream;
    int length = _length / 2;
    Beeper* beeper = (Beeper*) _beeper;

    beeper->generateSamples(stream, length);
}

// function sound prototype of constructor
void sound::tone(double Hz_Ss, int duration_Ss) {
    Hz_S = Hz_Ss;
    duration_S = duration_Ss;

    SDL_Init(SDL_INIT_AUDIO);

    // Duration
    int duration = duration_S * 10;
    double Hz = Hz_S;

    // Varibale Beeper
    Beeper b;
    b.beep(Hz, duration);
    b.wait();
}