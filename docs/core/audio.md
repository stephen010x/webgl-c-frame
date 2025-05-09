# Audio API

[core/audio.h](/src/core/audio.h) &emsp; [core/audio.c](/src/core/audio.c)

The Audio API makes use of HTML5's audio capabilities in order to play soundtracks with as much relevant control over the audio as HTML would allow. Due to the nature of the audio player HTML provides, there are a few strict limitations.

<!--##### `int sound_play_unsafe(const char* sound_id);`-->

## Index

**Functions** \
&emsp; [sound_play_unsafe](#sound_play_unsafe) \
&emsp; [sound_play_unsafe2](#sound_play_unsafe2) \
&emsp; [sound_play](#sound_play) \
&emsp; [sound_play2](#sound_play2) \
&emsp; [sound_stop](#sound_stop) \
&emsp; [sound_pause](#sound_pause) \
&emsp; [sound_isfinished](#sound_isfinished) \
&emsp; [sound_isplaying](#sound_isplaying)

## Functions




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
<br><br><br><br>




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
<br><br><br><br>




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
<br><br><br><br>




---

<a name="sound_play2"></a>
```c
int sound_play2(const char* sound_id, double volume, double speed, bool loop, bool preserve_pitch);
```

<ins>Description</ins> \
Like [sound_play](#sound_play), but with more parameter options

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of `<audio>` tag that contains the sound bite |
| `volume` | Value from 0.0 to 1.0 that represents volume |
| `speed` | multiplier for playback rate (1.0 is normal. 2.0 is double speed. 0.5 is half speed) |
| `loop` | `true`/`false` loop the sound when it finishes playing |
| `preserve_pitch` | `true`/`false` preserve pitch when playback rate is changed |

<ins>Return value</ins> \
&emsp; Returns zero if success \
&emsp; Returns `-1` if sound not found

---
<br><br><br><br>




---

<a name="sound_stop"></a>
```c
int sound_stop(const char* sound_id);
```

<ins>Description</ins> \
Stops a sound. Cannot be resumed.

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of <audio> tag that contains the sound bite |

<ins>Return value</ins> \
&emsp; Returns zero if success \
&emsp; Returns `-1` if sound not found

---
<br><br><br><br>




---

<a name="sound_pause"></a>
```c
int sound_pause(const char* sound_id);
```

<ins>Description</ins> \
Pauses a sound. Can be resumed with [sound_play](#sound_play)

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of <audio> tag that contains the sound bite |

<ins>Return value</ins> \
&emsp; Returns zero if success \
&emsp; Returns `-1` if sound not found

---
<br><br><br><br>




---

<a name="sound_isfinished"></a>
```c
bool sound_isfinished(const char* sound_id);
```

<ins>Description</ins> \
Checks if a sound is finished playing.

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of <audio> tag that contains the sound bite |

<ins>Return value</ins> \
&emsp; Returns `true` if sound has ended or stopped \
&emsp; Returns `false` if sound has not ended or stopped

---
<br><br><br><br>




---

<a name="sound_isplaying"></a>
```c
bool sound_isplaying(const char* sound_id);
```

<ins>Description</ins> \
Checks if a sound is playing.

| Parameter | Description |
|:---|:---|
| `sound_id` | String pointer to HTML/CSS ID of <audio> tag that contains the sound bite |

<ins>Return value</ins> \
&emsp; Returns `true` if sound is not paused \
&emsp; Returns `false` if sound is paused or stopped

---
