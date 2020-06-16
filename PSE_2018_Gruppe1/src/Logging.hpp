//
// Created by Simon on 28.06.2018.
//

#pragma once

#include <cstdio>
#include <cstdarg>

#include <string>
#include <queue>

#include <Diagnostics.hpp>

#undef DIAG_VERBOSE
#undef DIAG_DEBUG
#undef DIAG_INFO
#undef DIAG_WARNING
#undef DIAG_ERROR

#define DIAG_VERBOSE(msg, ...) Logging::log(DiagnosticLevel::DIAG_VERBOSE, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_DEBUG(msg, ...) Logging::log(DiagnosticLevel::DIAG_DEBUG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_INFO(msg, ...) Logging::log(DiagnosticLevel::DIAG_INFO, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_WARNING(msg, ...) Logging::log(DiagnosticLevel::DIAG_WARNING, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_ERROR(msg, ...) Logging::log(DiagnosticLevel::DIAG_ERROR, __FILE__, __LINE__, msg, ##__VA_ARGS__)

/**
 * \brief This is a wrapper class for Diagnostics. Apart from forwarding everything to Diagnostics, it also logs
 * every received message to an instance of FileLogger
 */
class Logging
{
public:
  /**
   * \brief Wrapper for Diagnostics::setMaxLevel() that also sets the max level for the current FileLogger instance
   * \param level max level of log messages
   */
  static void setMaxLevel(DiagnosticLevel level);

  /**
   * \brief Wrapper for Diagnostics::log() that also logs the message to the current FileLogger instance
   * \param level Log level of the message
   * \param file File where the message was generated - filled by macro
   * \param line Line where the message was generated - filled by macro
   * \param message The actual message - can use printf style placeholders
   * \param ... printf style variadic replacements for placeholders in the message
   */
  static void log(DiagnosticLevel level, const char* file, int line, const char* message, ...);
};