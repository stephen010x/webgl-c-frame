# Audio API

[core/audio.h](/src/core/audio.h) &emsp; [core/audio.c](/src/core/audio.c)

The Audio API makes use of HTML5's audio capabilities in order to play soundtracks with as much relevant control over the audio as HTML would allow. Due to the nature of the audio player HTML provides, there are a few strict limitations.

<!--##### `int sound_play_unsafe(const char* sound_id);`-->

## Index

**Functions** \
&emsp; [sound_play_unsafe](#sound_play_unsafe)

## Functions

---
\
\
\
\
---

<a name="sound_play_unsafe"></a>

```c
int sound_play_unsafe(const char* sound_id);
```

<ins>Description</ins> \
Plays a sound that cannot be paused nor stopped. Typically meant for smaller sound bites like footsteps. This allows for being able to play the same soundbite overlapping.

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of `<audio>` tag that contains the sound bite |

<ins>Return value</ins> \
&emsp; Returns zero if success \
&emsp; Returns `-1` if sound not found

---
\
\
\
\
---

<a name="sound_play_unsafe2"></a>

```c
int sound_play_unsafe2(const char* _sound_id, double volume, double speed, bool preserve_pitch);
```

<ins>Description</ins> \
Like [sound_play_unsafe](#sound_play_unsafe) but with more parameter options.

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of `<audio>` tag that contains the sound bite |
| `volume` | Value from 0.0 to 1.0 that represents volume |
| `speed` | multiplier for playback rate (1.0 is normal. 2.0 is double speed. 0.5 is half speed) |
| `preserve_pitch` | `true`/`false` preserve pitch when playback rate is changed |

<ins>Return value</ins> \
&emsp; Returns zero if success \
&emsp; Returns `-1` if sound not found

---
\
\
\
\
---

<a name="sound_play"></a>

```c
int sound_play(const char* sound_id, bool loop);
```

<ins>Description</ins> \
Plays a sound. Multiple sounds can be played at once, but the same sound cannot be played multiple times until the previous instance finishes.

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of <audio> tag that contains the sound bite |
| `loop` | `true`/`false` loop the sound when it finishes playing |

<ins>Return value</ins> \
&emsp; Returns zero if success \
&emsp; Returns `-1` if sound not found

---
\
\
\
\
---

``

`int sound_stop(const char* sound_id);`

`int sound_pause(const char* sound_id);`

`bool sound_isfinished(const char* sound_id);`

`bool sound_isplaying(const char* sound_id);`

`int sound_play_unsafe2(const char* sound_id, double volume, double speed, bool preserve_pitch);`

`int sound_play2(const char* sound_id, double volume, double speed, bool loop, bool preserve_pitch);`
