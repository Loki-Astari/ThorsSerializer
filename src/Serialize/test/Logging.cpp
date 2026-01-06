#include "gtest/gtest.h"
#include "ThorsLogging/ThorsLogging.h"
#include <iostream>
#include <string>

class LoggingEnvironment: public ::testing::Environment
{
    public:
    ~LoggingEnvironment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        using namespace std::string_literals;

        char* logging = getenv("THOR_LOG_LEVEL");
        if (logging == nullptr)
        {
            std::cerr << "NO - THOR_LOG_LEVEL\n";
        }
        else
        {
            std::cerr << "Logging Level BEFORE: " << ThorsLogLevelGet() << "\n";
            std::cerr << "THOR_LOG_LEVEL = >" << logging << "<\n";
            int level = std::strtol(logging, nullptr, 10);
            if (level > 0 && level <10)
            {
                ThorsLogLevelSet(level);
            }
            else if ("FATAL"s == logging)
            {
                ThorsLogLevel(FATAL);
            }
            else if ("ERROR"s == logging)
            {
                ThorsLogLevel(ERROR);
            }
            else if ("WARNING"s == logging)
            {
                ThorsLogLevel(WARNING);
            }
            else if ("INFO"s == logging)
            {
                ThorsLogLevel(INFO);
            }
            else if ("DEBUG"s == logging)
            {
                ThorsLogLevel(6);
            }
            else if ("TRACE"s == logging)
            {
                ThorsLogLevel(8);
            }
            else if ("ALL"s == logging)
            {
                ThorsLogLevel(9);
            }
            std::cerr << "Logging Level AFTER: " << ThorsLogLevelGet() << "\n";
        }
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

bool initLogging()
{
    std::cerr << "Logging Init\n";
    ::testing::Environment* const foo_env = ::testing::AddGlobalTestEnvironment(new LoggingEnvironment);
    ((void)foo_env);
    return true;
}

#ifdef THOR_DISABLE_TEST_LOGGING
bool logingInit = false;
#else
bool logingInit = initLogging();
#endif
