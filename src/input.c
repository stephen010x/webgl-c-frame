#include <emscripten.h>
#include <emscripten/html5.h>

#include "input.h"




bool key_event_handler(int etype, const EmscriptenKeyboardEvent* event, void* params);
bool mouse_event_handler(int etype, const EmscriptenMouseEvent* event, void* params);
bool touch_event_handler(int etype, const EmscriptenTouchEvent* event, void* params);




char key[256];



void input_init(void) {
    emscripten_set_keydown_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &key_event_handler);
    emscripten_set_keyup_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &key_event_handler);

    // for the mobiley gifted
    /*emscripten_set_touchstart_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &touch_event_handler);*/

    emscripten_set_mousedown_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &mouse_event_handler);
    emscripten_set_mouseup_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &mouse_event_handler);
    emscripten_set_mousemove_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &mouse_event_handler);

    emscripten_set_touchstart_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &touch_event_handler);
    emscripten_set_touchend_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &touch_event_handler);
    emscripten_set_touchmove_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &touch_event_handler);

    // for mobile users. Not that mobile actually listens to it.
    emscripten_lock_orientation(EMSCRIPTEN_ORIENTATION_PORTRAIT_PRIMARY);
}



// these do nothing yet
void input_push_callback(EVENT_CALLBACK callback) {
    return;
}

void input_pop_callback(EVENT_CALLBACK callback) {
    return;
}






bool key_event_handler(int etype, const EmscriptenKeyboardEvent* event, void* params) {
    switch (etype) {
        case EMSCRIPTEN_EVENT_KEYDOWN:
            key[event->keyCode] = KEYDOWN;
            return false;
            //return true;                    // return that it was handled
        case EMSCRIPTEN_EVENT_KEYUP:
            key[event->keyCode] = KEYUP;
            return false;
            //return true;                    // return that it was handled
    }
    return false; // return that it wasn't handled
}


bool touch_event_handler(int etype, const EmscriptenTouchEvent* event, void* params) {
    static int px, py;
    const EmscriptenTouchPoint* point = event->touches+0;

    //emscripten_run_script("alert('hello');");

    //mouse.dx += 1000;
    
    switch (etype) {
        case EMSCRIPTEN_EVENT_TOUCHSTART:
            px = point->clientX;
            py = point->clientY;
            //EM_ASM({}, px, py);
            mouse.button[0 /*event->numTouches*/] = MOUSEDOWN;
            /*EM_ASM({
                let v1 = $0;
                let v2 = $1;
                alert(v1.toString() + ":" + v2.toString());
            }, event->numTouches, 0);*/
            return true;
        case EMSCRIPTEN_EVENT_TOUCHEND:
            mouse.button[0 /*event->numTouches*/] = MOUSEUP;
            return true;
        case EMSCRIPTEN_EVENT_TOUCHMOVE:
            mouse.x = point->clientX;
            mouse.y = point->clientY;
            mouse.dx += point->clientX - px;
            mouse.dy += point->clientY - py;
            /*EM_ASM({
                let v1 = $0;
                let v2 = $1;
                alert(v1.toString() + ":" + v2.toString());
            }, mouse.dx, mouse.dy);*/
            px = point->clientX;
            py = point->clientY;
            return true;
    }
    return false;
}



bool mouse_event_handler(int etype, const EmscriptenMouseEvent *event, void *params) {
    switch (etype) {
        case EMSCRIPTEN_EVENT_MOUSEMOVE:
            mouse.x = event->canvasX;
            mouse.y = event->canvasY;
            // ideally this should be set every frame too. But what can you do?
            mouse.dx += event->movementX; // gets reset every frame
            mouse.dy += event->movementY; // gets reset every frame
            return true;
        case EMSCRIPTEN_EVENT_MOUSEDOWN:
            mouse.button[event->button] = MOUSEDOWN;
            return true;
        case EMSCRIPTEN_EVENT_MOUSEUP:
            mouse.button[event->button] = MOUSEUP;
            return true;
    }
    return false;
}


