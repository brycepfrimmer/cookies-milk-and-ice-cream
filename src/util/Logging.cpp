/*
 * AccessoryLog.cpp
 *
 *  Created on: Aug 15, 2012
 *      Author: aodziemkowski
 */

#include "Logging.h"

#include <stdio.h>
#include <stdarg.h>
#include <sys/slog2.h>

namespace util {

static slog2_buffer_set_config_t      buffer_config;
static slog2_buffer_t                 buffer_handle[1];

int registerLogger() {
    buffer_config.buffer_set_name = "mybp_terminal_app";

    // These two buffers are configured below.
    buffer_config.num_buffers = 1;

    // Request an initial verbosity level.  Note that the slogger2 PPS-based verbosity control
    // will override this, if configured by the user at /pps/services/slogger2/verbose.
    //
    // We recommend that all components use SLOG2_INFO as the default verbosity level, then
    // use SLOG2_DEBUG1 and SLOG2_DEBUG2 for higher levels of verbosity for in-depth investigations
    // performed by developers or testers.
    //
    // All buffers within the set share the same verbosity level.
    //
    buffer_config.verbosity_level = SLOG2_DEBUG1;

    // !! NOTE: Please use a maximum of 32KB for the total of all your individual buffers !!
    // Please discuss with Conrad Kreek, Mark Slevinsky and Robert Turner if you need an
    // exception.  The goal is that only a few monster processes (eg. Qualcomm's AP process)
    // will need more than 32KB.  See http://go/slogger2 for more info.

    // Configure the first buffer, using 7 x 4KB pages.  This larger buffer will be used for
    // very chatty logging.  Our goal is to have 30-60 seconds of history at any given time
    // so we will want to log at a rate of around one log line with a string of 16 bytes
    // long every 150 milliseconds.
    //
    buffer_config.buffer_config[0].buffer_name = "hi_rate_logging";
    buffer_config.buffer_config[0].num_pages = 7;

    // Configure the second buffer, which we will use for high level info logging that is very
    // infrequent, but we want a longer history (hours or maybe even over a day or two).  This
    // buffer uses 1 x 4KB.
    //
    //buffer_config.buffer_config[1].buffer_name = "lo_rate_logging";
    //buffer_config.buffer_config[1].num_pages = 1;

    // Register the Buffer Set
    if( -1 == slog2_register( &buffer_config, buffer_handle, 0 ) ) {
        fprintf( stderr, "Error registering slogger2 buffer!\n" );
        return -1;
    }
    return 0;
}

void setLogVerbosity(int value) {
    slog2_set_verbosity( buffer_handle[0], value );
}

void log(int severity, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vslog2f( buffer_handle[0], 0, severity, fmt, args);
    va_end(args);
}

void stop(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    vslog2f( buffer_handle[0], 0, SLOG2_CRITICAL, fmt, args);
    vfprintf( stderr, fmt, args );
    va_end(args);
    fprintf(stderr,"\n");
    const char* msg = "A core dump is created in the 'logs' directory, "
                      "please attach the executable as well as the core "
                      "dump in your bug report to help us identify the problem.";
    log(SLOG2_CRITICAL, "%s", msg);
    fprintf( stderr, "%s", msg);
    abort();
}

}
