

#ifndef LOGGING_H_
#define LOGGING_H_

#include <sys/slog2.h>
#include <stdlib.h>

namespace util {

int registerLogger();
void log(int severity, const char *fmt, ...);
void setLogVerbosity(int value);
void stop(const char* fmt, ...);

#define LOG_ERROR( FMT, ... ) util::log( SLOG2_ERROR, FMT, ##__VA_ARGS__ )
#define LOG_WARN( FMT, ... ) util::log( SLOG2_WARNING, FMT, ##__VA_ARGS__ )
#define LOG_INFO( FMT, ... ) util::log( SLOG2_INFO, FMT, ##__VA_ARGS__ )
#define LOG_DEBUG( FMT, ... ) util::log( SLOG2_DEBUG1, FMT, ##__VA_ARGS__ )


#define STOP_IF(cond, FMT, ...) do {                           \
    if(cond) {                                                 \
      util::stop("STOP: "FMT, ## __VA_ARGS__);                       \
    }                                                          \
  } while(0)

#define STOP(FMT, ...) do {                                    \
      util::stop("STOP: "FMT, ## __VA_ARGS__);                       \
  } while(0)
}

#endif /*LOGGING_H_*/
