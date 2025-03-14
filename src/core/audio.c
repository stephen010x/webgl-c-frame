#include <emscripten.h>
#include <emscripten/html5.h>

#include "camera.h"


EM_JS(int, play_sound_unsafe, (const char* _sound_id), {
    const sound_id = UTF8ToString(_sound_id);
    
    var sound = document.getElementById(sound_id);
    sound.cloneNode(true).play();
})


// TODO: add a way to create sound instance id's, return them when you play them
// and be able to use those to stop sounds


EM_JS(int, sound_play, (const char* _sound_id, bool loop), {
    const sound_id = UTF8ToString(_sound_id);

    // stops sound if playing
    sound.load();

    var sound = document.getElementById(sound_id);
    sound.loop = !!loop;
    sound.play();
})

EM_JS(int, sound_play2, (const char* _sound_id, double volume, double speed, bool loop, bool preserve_pitch), {
    const sound_id = UTF8ToString(_sound_id);
    var sound = document.getElementById(sound_id);

    // stops sound if playing
    sound.load();

    sound.volume = volume;
    sound.playbackRate = speed;
    sound.preservesPitch = !!preserve_pitch;
    sound.loop = !!loop;
    sound.play();
})

EM_JS(int, sound_stop, (const char* _sound_id), {
    const sound_id = UTF8ToString(_sound_id);
})

EM_JS(int, sound_pause, (const char* _sound_id), {
    const sound_id = UTF8ToString(_sound_id);
})

EM_JS(int, sound_is_playing, (const char* _sound_id), {
    const sound_id = UTF8ToString(_sound_id);
    //HTMLMediaElement.ended
})

EM_JS(int, sound_is_paused, (const char* _sound_id), {
    const sound_id = UTF8ToString(_sound_id);
    //HTMLMediaElement.ended
})
