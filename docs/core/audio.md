# Audio API

[core/audio.h](/src/core/audio.h) &emsp; [core/audio.c](/src/core/audio.c)

The Audio API makes use of HTML5's audio capabilities in order to play soundtracks with as much relevant control over the audio as HTML would allow. Due to the nature of the audio player HTML provides, there are a few strict limitations.

<!--##### `int sound_play_unsafe(const char* sound_id);`-->

## Functions

---

```c
int sound_play_unsafe(const char* sound_id);
```

Plays a sound that is unsafe

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of <audio> tag that contains the sound bite |

| Return value |
|:---|
| Returns zero if success |
| Returns nonzero if error |

---


`int sound_play(const char* sound_id, bool loop);`

`int sound_stop(const char* sound_id);`

`int sound_pause(const char* sound_id);`

`bool sound_isfinished(const char* sound_id);`

`bool sound_isplaying(const char* sound_id);`

`int sound_play_unsafe2(const char* sound_id, double volume, double speed, bool preserve_pitch);`

`int sound_play2(const char* sound_id, double volume, double speed, bool loop, bool preserve_pitch);`
