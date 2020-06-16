//
// Created by Simon on 13.06.2018.
//
#include <iostream>
#include <cstdarg>

#include "Diagnostics.hpp"

static DiagnosticLevel maxLevel = DiagnosticLevel::DIAG_VERBOSE;

void Diagnostics::setMaxLevel(DiagnosticLevel level){
  maxLevel = level;
}

void Diagnostics::log(DiagnosticLevel level, const char* file, int line, const char* const msg, ...){
  if(level <= maxLevel){
    std::string lvl;

    switch (level) {
      default:
      case DiagnosticLevel::DIAG_VERBOSE: lvl = "VERBOSE"; break;
      case DiagnosticLevel::DIAG_DEBUG: lvl = "DEBUG"; break;
      case DiagnosticLevel::DIAG_INFO: lvl = "INFO"; break;
      case DiagnosticLevel::DIAG_WARNING: lvl = "WARNING"; break;
      case DiagnosticLevel::DIAG_ERROR: lvl = "ERROR"; break;
    }

    char tmp1[1024];

    va_list args;
    va_start(args, msg);
    vsprintf(tmp1, msg, args);
    va_end(args);

    std::printf("###%s### %s(%d): %s \n", lvl.c_str(), file, line, tmp1);
  }
}
