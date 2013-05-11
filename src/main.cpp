/*
 * Copyright (c) 2011-2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <screen/screen.h>
#include <bps/navigator.h>
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include "bbutil.h"

#include "Logging.h"
#include <glview/glview.h>

static GLfloat vertices[8];
static GLfloat colors[16];

void handleScreenEvent(bps_event_t *event) {
    screen_event_t screen_event = screen_event_get_event(event);

    int screen_val;
    screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TYPE,
            &screen_val);

    switch (screen_val) {
    case SCREEN_EVENT_MTOUCH_TOUCH:
    case SCREEN_EVENT_MTOUCH_MOVE:
    case SCREEN_EVENT_MTOUCH_RELEASE:
        break;
    }
}

int initialize() {
    //Initialize vertex and color data
    vertices[0] = -0.25f;
    vertices[1] = -0.25f;

    vertices[2] = 0.25f;
    vertices[3] = -0.25f;

    vertices[4] = -0.25f;
    vertices[5] = 0.25f;

    vertices[6] = 0.25f;
    vertices[7] = 0.25f;

    colors[0] = 1.0f;
    colors[1] = 0.0f;
    colors[2] = 1.0f;
    colors[3] = 1.0f;

    colors[4] = 1.0f;
    colors[5] = 1.0f;
    colors[6] = 0.0f;
    colors[7] = 1.0f;

    colors[8] = 0.0f;
    colors[9] = 1.0f;
    colors[10] = 1.0f;
    colors[11] = 1.0f;

    colors[12] = 0.0f;
    colors[13] = 1.0f;
    colors[14] = 1.0f;
    colors[15] = 1.0f;

    //Query width and height of the window surface created by utility code
    EGLint surface_width, surface_height;

    eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
    eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

    EGLint err = eglGetError();
    if (err != 0x3000) {
        fprintf(stderr, "Unable to query EGL surface dimensions\n");
        return EXIT_FAILURE;
    }

    glShadeModel(GL_SMOOTH);

    //set clear color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glViewport(0, 0, surface_width, surface_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(0.0f, (float) (surface_width) / (float) (surface_height), 0.0f,
            1.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef((float) (surface_width) / (float) (surface_height) / 2, 0.5f,
            0.0f);

    return EXIT_SUCCESS;
}

void render() {
    //Typical render pass
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, colors);

    glRotatef(0.5f, 0.0f, 1.0f, 0.0f);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    //Use utility code to update the screen
    bbutil_swap();
}

int main(int argc, char *argv[]) {
    util::registerLogger();
    util::setLogVerbosity(7);

//    int init = glview_initialize(GLVIEW_API_OPENGLES_11, &render);
}
