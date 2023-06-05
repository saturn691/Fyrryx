#include <headers/buzzer.h>

#define  a3f    208     // 208 Hz
#define  b3f    233     // 233 Hz
#define  b3     247     // 247 Hz
#define  c4     261     // 261 Hz MIDDLE C
#define  c4s    277     // 277 Hz
#define  e4f    311     // 311 Hz    
#define  f4     349     // 349 Hz 
#define  a4f    415     // 415 Hz  
#define  b4f    466     // 466 Hz 
#define  b4     493     // 493 Hz 
#define  c5     523     // 523 Hz 
#define  c5s    554     // 554  Hz
#define  e5f    622     // 622 Hz  
#define  f5     698     // 698 Hz 
#define  f5s    740     // 740 Hz
#define  a5f    831     // 831 Hz 

#define  rest    -1

#define beatlength 75 // determines tempo (lower = faster)
#define beatseparationconstant 0.3

void Buzzer::play(int buzzer_pin, int rhythm[], int melody[]) {
    int notelength;
    int b = 0;

    while (b < sizeof(melody) / sizeof(int)) {
        notelength = beatlength * rhythm[b];
        
        if (melody[b] > 0) {
            tone(buzzer_pin, melody[b], notelength);
        }
        
        b++;
        
        delay(notelength);
        noTone(buzzer_pin);
        delay(notelength * beatseparationconstant);
    }
}

void Buzzer::horn(int buzzer_pin) {
    int melody[] = {a4f};
    int rhythm[] = {10};

    play(buzzer_pin, rhythm, melody);
}

void Buzzer::rickroll_intro(int buzzer_pin) {
    int song_intro_melody[] = {c5s,  e5f, e5f, f5, a5f, f5s, f5, e5f, c5s, e5f, rest, a4f, a4f};
    int song_intro_rhythm[] = {6, 10, 6, 6, 1, 1, 1, 1, 6, 10, 4, 2, 10};

    play(buzzer_pin, song_intro_rhythm, song_intro_melody);

}

void Buzzer::rickroll_chorus(int buzzer_pin) {
    int song_chorus_melody[] =
    { b4f, b4f, a4f, a4f,
    f5, f5, e5f, b4f, b4f, a4f, a4f, e5f, e5f, c5s, c5, b4f,
    c5s, c5s, c5s, c5s,
    c5s, e5f, c5, b4f, a4f, a4f, a4f, e5f, c5s,
    b4f, b4f, a4f, a4f,
    f5,  f5, e5f, b4f, b4f, a4f, a4f, a5f, c5, c5s, c5, b4f,
    c5s, c5s, c5s, c5s,
    c5s, e5f, c5, b4f, a4f, rest, a4f, e5f, c5s, rest
    };

    int song_chorus_rhythm[] =
    { 1, 1, 1, 1,
    3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
    1, 1, 1, 1,
    3, 3, 3, 1, 2, 2, 2, 4, 8,
    1, 1, 1, 1,
    3, 3, 6, 1, 1, 1, 1, 3, 3, 3,  1, 2,
    1, 1, 1, 1,
    3, 3, 3, 1, 2, 2, 2, 4, 8, 4
    };

    play(buzzer_pin, song_chorus_rhythm, song_chorus_melody);
}