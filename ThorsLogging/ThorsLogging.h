#ifndef THORSANVIL_LOGGING_THORS_LOGGING_H
#define THORSANVIL_LOGGING_THORS_LOGGING_H

#include "ThorsLoggingConfig.h"


#ifndef LOGURU_WITH_STREAMS
#define LOGURU_WITH_STREAMS 1
#endif

#if defined(THORS_LOGGING_HEADER_ONLY) && THORS_LOGGING_HEADER_ONLY == 1
#include <iostream>
namespace loguru
{
    enum NamedVerbosity : int
    {
        // Used to mark an invalid verbosity. Do not log to this level.
        Verbosity_INVALID = -10, // Never do LOG_F(INVALID)

        // You may use Verbosity_OFF on g_stderr_verbosity, but for nothing else!
        Verbosity_OFF     = -9, // Never do LOG_F(OFF)

        // Prefer to use ABORT_F or ABORT_S over LOG_F(FATAL) or LOG_S(FATAL).
        Verbosity_FATAL   = -3,
        Verbosity_ERROR   = -2,
        Verbosity_WARNING = -1,

        // Normal messages. By default written to stderr.
        Verbosity_INFO    =  0,

        // Same as Verbosity_INFO in every way.
        Verbosity_0       =  0,

        // Verbosity levels 1-9 are generally not written to stderr, but are written to file.
        Verbosity_1       = +1,
        Verbosity_2       = +2,
        Verbosity_3       = +3,
        Verbosity_4       = +4,
        Verbosity_5       = +5,
        Verbosity_6       = +6,
        Verbosity_7       = +7,
        Verbosity_8       = +8,
        Verbosity_9       = +9,

        // Do not use higher verbosity levels, as that will make grepping log files harder.
        Verbosity_MAX     = +9,
    };
}

#ifndef THOR_LOGGING_DEFAULT_LOG_LEVEL
#define THOR_LOGGING_DEFAULT_LOG_LEVEL   3
#endif

#else
#include "loguru.hpp"
#endif
#include "ThorsIOUtil/Utility.h"
#include <stdexcept>
#include <string>


namespace ThorsAnvil
{
    namespace Logging
    {

    // This is for data/application corruption that requires the
    // application to immediately quit.
    class FatalException: public std::runtime_error
    {
        public:
            using std::runtime_error::runtime_error;
    };
    // This is for situations that "should not" happen.
    // Use this exception for code paths that should not be reachable.
    //
    // This will help find issues that can be corrected by unit tests.
    // But occasionally will happen in production. You should only
    // catch this type of error at an action type level to abandon the
    // action.
    //
    // Note: This does not mean there has been data corruptions so we
    //       can potentially continue. The application writer must
    //       make that determination.
    class CriticalException: public std::runtime_error
    {
        public:
            using std::runtime_error::runtime_error;
    };
    // This is for situations where you don't want to happen
    // but is caused because the input data does not conform
    // to expect patterns.
    class LogicalException: public std::runtime_error
    {
        public:
            using std::runtime_error::runtime_error;
    };

    }
}

#if defined(THORS_LOGGING_HEADER_ONLY) && THORS_LOGGING_HEADER_ONLY == 1
#define ThorsLogAndThrowAction(Level, Exception, Scope, Function, ...)  \
do                                                                      \
{                                                                       \
    std::string message_ThorsLogAndThrowAction =                        \
                          ThorsAnvil::Utility::buildErrorMessage(       \
                                            Scope,                      \
                                            Function,                   \
                                            __VA_ARGS__);               \
    if ((loguru::Verbosity_ ## Level) <= THOR_LOGGING_DEFAULT_LOG_LEVEL) {      \
        std::cerr << message_ThorsLogAndThrowAction;                    \
    }                                                                   \
    throw Exception(message_ThorsLogAndThrowAction);                    \
}                                                                       \
while (false)
#define ThorsMessage(Level, ...)                                        \
do                                                                      \
{                                                                       \
    if ((loguru::Verbosity_ ## Level) <= THOR_LOGGING_DEFAULT_LOG_LEVEL) {      \
        std::cerr << ThorsAnvil::Utility::buildErrorMessage(__VA_ARGS__); \
    }                                                                   \
}                                                                       \
while (false)
#else
#define ThorsLogAndThrowAction(Level, Exception, Scope, Function, ...)  \
do                                                                      \
{                                                                       \
    std::string message_ThorsLogAndThrowAction =                        \
                          ThorsAnvil::Utility::buildErrorMessage(       \
                                            Scope,                      \
                                            Function,                   \
                                            __VA_ARGS__);               \
    LOG_F(Level, "%s", message_ThorsLogAndThrowAction.c_str());         \
    throw Exception(message_ThorsLogAndThrowAction);                    \
}                                                                       \
while (false)

#define ThorsMessage(Level, ...)        VLOG_S(loguru::Verbosity_ ## Level) << ThorsAnvil::Utility::buildErrorMessage(__VA_ARGS__)
#endif


#define ThorsLogAndThrowFatal(...)      ThorsLogAndThrowAction(FATAL,   ThorsAnvil::Logging::FatalException, __VA_ARGS__)
#define ThorsLogAndThrowCritical(...)   ThorsLogAndThrowAction(ERROR,   ThorsAnvil::Logging::CriticalException, __VA_ARGS__)
#define ThorsLogAndThrowLogical(...)    ThorsLogAndThrowAction(WARNING, ThorsAnvil::Logging::LogicalException, __VA_ARGS__)
#define ThorsLogAndThrow(...)           ThorsLogAndThrowAction(2, std::runtime_error, __VA_ARGS__)

#define ThorsCatchMessage(S, F, e)      ThorsMessage(2, S, F, "Caught Exception: ", e)
#define ThorsRethrowMessage(S, F, e)    ThorsMessage(2, S, F, "ReThrow Exception: ",e)

#endif
