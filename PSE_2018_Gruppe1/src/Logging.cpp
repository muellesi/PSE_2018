//
// Created by Simon on 28.06.2018.
//

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

#include "Logging.hpp"
#include "FileLogger.hpp"

static DiagnosticLevel s_logLevel = DiagnosticLevel::DIAG_VERBOSE;
static int s_skippedMessages      = 0;

void Logging::log(DiagnosticLevel level, const char* file, int line, const char* message, ...)
{
  if (level <= s_logLevel)
  {
    if (s_skippedMessages > 0)
    {
      std::string str = "--> Skipped ";
      str += std::to_string(s_skippedMessages);
      str += " messages because their logLevel was too high. \n";
      FileLogger::getInstance().log(str);
      s_skippedMessages = 0;
    }

    char tmp1[1024];
    char tmp2[1024];

    va_list args;
    va_start(args, message);
    vsprintf(tmp1, message, args);
    va_end(args);

    Diagnostics::log(level, file, line, tmp1);

    std::string lvl;
    switch (level)
    {
      default:
      case DiagnosticLevel::DIAG_VERBOSE:
        lvl = "VERBOSE";
        break;
      case DiagnosticLevel::DIAG_DEBUG:
        lvl = "DEBUG";
        break;
      case DiagnosticLevel::DIAG_INFO:
        lvl = "INFO";
        break;
      case DiagnosticLevel::DIAG_WARNING:
        lvl = "WARNING";
        break;
      case DiagnosticLevel::DIAG_ERROR:
        lvl = "ERROR";
        break;
    }

    // generate timestamp for file logger
    char time_str[30];

    auto time   = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto time_s = std::chrono::time_point_cast<std::chrono::seconds>(time);
    auto ms     = std::chrono::duration_cast<std::chrono::milliseconds>(time - time_s);

    std::time_t c_time = std::chrono::system_clock::to_time_t(time_s);
    struct tm* p       = std::localtime(&c_time);
    std::strftime(time_str, 30, "%c", p);

    sprintf(tmp2, "%s.%-3lli  %-7s  %s(%d): %s\n", time_str, ms.count(), lvl.c_str(), file, line, tmp1);

    FileLogger::getInstance().log(std::string(tmp2));
  }
  else
  {
    s_skippedMessages++;
  }
}

void Logging::setMaxLevel(DiagnosticLevel level)
{
  Diagnostics::setMaxLevel(level);
  s_logLevel = level;
  DIAG_INFO("Switching to log level %d", level);
}