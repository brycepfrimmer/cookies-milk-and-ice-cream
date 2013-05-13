#include <screen/screen.h>
#include <bps/navigator.h>
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <bps/virtualkeyboard.h>

#include <glview/glview.h>
#include <GLES/gl.h>

#include "bbutil.h"
#include "Logging.h"

static font_t* font;
static screen_context_t screenContext;
static unsigned int width, height;

void enable2d() {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(0.0f, (float) (width) / (float) (height), 0.0f,
            1.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(1.0f / (float) (height), 1.0f / (float) (height), 1.0f);
//    glTranslatef((float) (width) / (float) (height) / 2, 0.5f, 0.0f);
}

static void initialize(void *p) {
//    virtualkeyboard_show();
//    screen_request_events(screenContext); CHOOSE WHERE TO DO INITIALIZATION STUFF

    glview_get_size(&width, &height);

    glShadeModel(GL_SMOOTH);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    enable2d();

    int dpi = bbutil_calculate_dpi(screenContext);
    font = bbutil_load_font(BBUTIL_DEFAULT_FONT, 12, dpi);
}

static void render(void *p) {
    //Typical render pass
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bbutil_render_text(font, "Testing....", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

static void event(bps_event_t *event, int domain, int code, void *p) {

}

int main(int argc, char *argv[]) {
    util::registerLogger();
    util::setLogVerbosity(7);

    STOP_IF(screen_create_context(&screenContext, 0) != 0, "Error: screen_create_context(..., ...)");
    STOP_IF(bbutil_init_egl(screenContext) != EXIT_SUCCESS, "Error: bbutil_init_egl(...)");

    STOP_IF(glview_initialize(GLVIEW_API_OPENGLES_11, &render) != GLVIEW_SUCCESS, "Error: glview_initialize(..., ...)");
    glview_register_initialize_callback(&initialize);
    glview_register_event_callback(&event);
    return glview_loop();
}
