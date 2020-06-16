///////////////////////////////////////////////////////////
//  TerminalHandler.cpp
//  Implementation of the Class TerminalHandler
//  Created on:      05-Jun-2018 14:42:06
//  Original author: student
///////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "AbstractModeController.hpp"
#include "TerminalHandler.hpp"
#include "MathFunctions.hpp"

TerminalHandler::~TerminalHandler() = default;

/**
 * \brief Constructor for TerminalHandler
 * \param manualModeController Controller for manual mode commands
 * \param autoModeController  Controller for automatic mode commands
 */
TerminalHandler::TerminalHandler(std::shared_ptr<ManualModeController> manualModeController, std::shared_ptr<AutoModeController> autoModeController) :
  m_manualModeController(manualModeController),
  m_autoModeController(autoModeController)
{
  Logging::setMaxLevel(DEFAULT_DIAGNOSTICS_MAX_LEVEL);
  tryRunSetupScript();
}

bool TerminalHandler::tryRunSetupScript()
{
  std::vector<std::string> cmd;
  cmd.emplace_back("script");
  cmd.emplace_back("setup.pse");

  m_abortScript = false;
  return handleScriptCommand(cmd, 0);
}

/**
 * \brief Abort the current command execution, whatever is being run right now
 */
void TerminalHandler::abort()
{
  DIAG_INFO("Aborting current command");

  m_abortScript = true;

  if (m_isInAutoMode)
  {
    m_isInAutoMode = false;
    m_autoModeController->abort();
  }
  else
  {
    m_manualModeController->abort();
  }
}

/**
 * \brief Splits a given string at a given delimiter and saves the resulting tokens in the vector result
 * \param input The string
 * \param result A ref to a vector that will be filled with the tokens
 * \param delim The delimiter for the split operation
 */
void TerminalHandler::splitString(const std::string& input, std::vector<std::string>& result, const char* delim)
{
  size_t currPos   = 0;
  size_t nextDelim = input.find(delim, currPos);

  while (nextDelim != std::string::npos)
  {
    std::string token = input.substr(currPos, nextDelim - currPos);  //-1 to cut off delimiter
    result.emplace_back(token);

    currPos   = nextDelim + 1;               //+ 1 to cut off delimiter
    nextDelim = input.find(delim, currPos);  // find next occurence of delim
  }

  result.emplace_back(input.substr(currPos, input.length() - currPos));
}

/**
 * \brief Executes the "set" command (see spec)
 * \param commandTokens all tokens that were extracted from the input
 * \return True on success, False on Fail
 */
bool TerminalHandler::handleSetCommand(const std::vector<std::string>& commandTokens)
{
  if (commandTokens.size() != 3 || commandTokens[1].compare(0, 1, "-") != 0)
  {
    std::cout << "Error! Usage: set [-l, -t, -d] <value>" << std::endl
              << "Parameters: " << std::endl
              << "-t: Set drive timeout (value > 0.0)" << std::endl
              << "-d: Set desired distance to keep from markers. (value > 0.0)" << std::endl
              << "-l: Set logging level" << std::endl
              << "Available Levels: 0: Error, 1: Warning, 2: Info, 3: Debug, 4: Verbose" << std::endl;
    return false;
  }
  else
  {
    std::string sw = commandTokens[1];
    char* err      = nullptr;

    if (sw == "-t")  ///< set timeout switch
    {
      double num = strtod(commandTokens[2].c_str(), &err);
      if (err == commandTokens[2].c_str())
        return false;

      if (num > 0.0)
      {
        DIAG_VERBOSE("Setting max drive duration to %d seconds", static_cast<long long int>(num * 1000) / 1000);
        m_manualModeController->setMaxDriveDuration(std::chrono::milliseconds(static_cast<long long int>(num * 1000)));
      }
      else
      {
        DIAG_ERROR("Timeout value has to be > 0");
        return false;
      }
    }
    else if (sw == "-d")  ///< set distance switch
    {
      double num = strtod(commandTokens[2].c_str(), &err);
      if (err == commandTokens[2].c_str())
        return false;

      if (num > 0.0)
      {
        DIAG_VERBOSE("Setting desired auto mode distance to %d", num);
        m_autoModeController->setDistance(num);
      }
      else
      {
        DIAG_ERROR("Distance value has to be > 0");
        return false;
      }
    }
    else if (sw == "-l")  ///< set logging level switch
    {
      int num = strtol(commandTokens[2].c_str(), &err, 10);
      if (err == commandTokens[2].c_str())
        return false;

      if (num >= 0 && num <= 4)
      {
        Logging::setMaxLevel(static_cast<DiagnosticLevel>(num));
        DIAG_INFO("Log level set to level %d", num);
      }
      else
      {
        DIAG_ERROR("Error level has to be between 0 and 4");
        return false;
      }
    }
    else
    {
      DIAG_ERROR("Unrecognized switch parameter: %s", sw.c_str());
      return false;
    }
  }
  return true;
}

/**
 * \brief Handles the "drive" command (see spec)
 * \param commandTokens all tokens that were extracted from the input
 * \return True on success, False on Fail
 */
bool TerminalHandler::handleDriveCommand(const std::vector<std::string>& commandTokens)
{
  if (commandTokens.size() != 4)
  {
    std::cout << "Error! Usage: drive <time> <velocity> <steering>" << std::endl;
    return false;
  }
  else
  {
    char* err   = nullptr;
    double time = strtod(commandTokens[1].c_str(), &err);
    if (err == commandTokens[1].c_str())
      return false;
    double velo = strtod(commandTokens[2].c_str(), &err);
    if (err == commandTokens[2].c_str())
      return false;
    double steer = strtod(commandTokens[3].c_str(), &err);
    if (err == commandTokens[3].c_str())
      return false;

    if (CheckLimits(time, 0.0, std::numeric_limits<double>::max()) && CheckLimits(velo, -100.0, 100.0) && CheckLimits(steer, -100.0, 100.0))
    {
      DIAG_VERBOSE("Driving towards %d with a velocity of %d for %d seconds", steer, velo, time);
      m_manualModeController->driveBlocking(std::chrono::milliseconds(static_cast<long long int>(time * 1000)), velo, steer);
    }
    else
    {
      DIAG_ERROR("Drive command parameters not in valid range!");
      return false;
    }
  }
  return true;
}

/**
 * \brief Handles the "script" command (see spec)
 * \param commandTokens all tokens that were extracted from the input
 * \return True on success, False on Fail
 */
bool TerminalHandler::handleScriptCommand(const std::vector<std::string>& commandTokens, int recursionDepth)
{
  if (recursionDepth >= MAX_RECURSION_DEPTH)
  {
    DIAG_ERROR("Maximum recursion depth reached! Check your script for possible infinite loops!");
    return false;
  }

  if (commandTokens.size() < 2)
  {
    std::cout << "Error! Usage: script /path/to/script file/may/contain/spaces" << std::endl;
    return false;
  }

  /* URI might contain spaces which causes it to get split into multiple tokens - because of that we have to rebuild it
   * here */
  std::stringstream uri;
  auto it = commandTokens.begin();
  it++;        // skip "script" command token
  uri << *it;  // read first token outside of loop to prevent leading space
  it++;
  for (; it != commandTokens.end(); it++)
  {
    uri << " " << *it;
  }
  std::string str = uri.str();

  std::ifstream scriptFileStream(uri.str(), std::ifstream::in);

  if (scriptFileStream.fail())
  {
    DIAG_ERROR("Specified script file %s could not be opened.", uri.str().c_str());
    return false;
  }

  std::vector<std::string> commandLines;
  std::string command;

  while (std::getline(scriptFileStream, command))
  {
    if (!std::all_of(command.begin(), command.end(), isspace))
    {  // check for empty line
      commandLines.emplace_back(command);
    }
  }

  for (auto& commandLine : commandLines)
  {
    if (m_abortScript)
    {  // Check if Ctrl + C was pressed while script execution
      break;
    }
    DIAG_INFO("Script: Executing command: %s", commandLine.c_str());
    if (evalUserInput(commandLine, true, recursionDepth))
    {
      DIAG_DEBUG("Script: Success!");
    }
    else
    {
      DIAG_ERROR("Script: Error while executing command %s", commandLine.c_str());
      return false;
    }
  }

  DIAG_VERBOSE("Script execution finished!");

  return true;
}

/**
 * \brief Handles the "search" command (see spec)
 * \param commandTokens all tokens that were extracted from the input
 * \return True on success, False on Fail
 */
bool TerminalHandler::handleSearchCommand(const std::vector<std::string>& commandTokens)
{
  DIAG_VERBOSE("Searching for marker...");
  m_manualModeController->searchMarkerBlocking();
  DIAG_VERBOSE("Marker search ended.");
  return true;  // TODO return bool or void?
}

/**
 * \brief Handles the "mode" command (see spec)
 * \param commandTokens all tokens that were extracted from the input
 * \return True on success, False on Fail
 */
bool TerminalHandler::handleModeCommand(const std::vector<std::string>& commandTokens)
{
  // [1:automatic; 2:manual]

  if (commandTokens.size() != 2)
  {
    DIAG_ERROR("Wrong token size! ");
    return false;
  }
  else
  {
    std::string cmd = commandTokens[1];

    if (cmd == "1")
    {
      DIAG_INFO("Auto mode is activated!");
      m_isInAutoMode = true;
      return true;
    }
    else if (cmd == "2")
    {
      DIAG_INFO("Man mode is activated!");
      m_isInAutoMode = false;
      m_autoModeController->abort();
      return true;
    }
    else
    {
      DIAG_ERROR("Invalid mode! choose= 1:automatic OR 2:manual ");
      return false;
    }
  }
}

bool TerminalHandler::handleQuitCommand(const std::vector<std::string>& vector)
{
  m_handleInput = false;
  return true;
}

/**
 * \brief Tries to execute a given command string
 * \param input the command string
 * \return True on success, False on Fail
 */
bool TerminalHandler::evalUserInput(const std::string& input, bool scriptMode, int recursionDepth)
{
  auto success = false;
  std::vector<std::string> tokens;

  splitString(input, tokens, " ");

  if (tokens.empty())
  {
    DIAG_ERROR("Empty token list returned!");
    return false;
  }

  std::string cmd = tokens[0];

  if (cmd == "set")
  {
    DIAG_VERBOSE("Handling set command %s", input.c_str());
    success = handleSetCommand(tokens);
  }
  else if (cmd == "drive")
  {
    DIAG_VERBOSE("Handling drive command %s", input.c_str());
    success = handleDriveCommand(tokens);
  }
  else if (cmd == "script")
  {
    DIAG_VERBOSE("Handling script command %s", input.c_str());
    m_abortScript = false;
    success       = handleScriptCommand(tokens, recursionDepth + 1);
  }
  else if (cmd == "search")
  {
    DIAG_VERBOSE("Handling search command %s", input.c_str());
    success = handleSearchCommand(tokens);
  }
  else if (cmd == "mode")
  {
    DIAG_VERBOSE("Handling mode command %s", input.c_str());

    // Switching from manual mode to automatic mode dureing script execution causes undefined behavior so prevent it
    if (scriptMode)
    {
      DIAG_ERROR("Mode switching is not available in scripts!");
      return false;
    }

    success = handleModeCommand(tokens);
  }
  else if (cmd == "quit" || cmd == "q" || cmd == "QUIT")
  {
    DIAG_VERBOSE("Handling quit command %s", input.c_str());

    success = handleQuitCommand(tokens);
  }
  else
  {
    DIAG_ERROR("Invalid command: %s", cmd.c_str());
  }

  if (!success)
    DIAG_DEBUG("User command \" %s \" contained errors!", input.c_str());

  return success;
}

/**
 * \brief Main Terminal Handler function. Will run in its own thread.
 */
void TerminalHandler::startInputHandling()
{
  std::string userCommand;

  std::cout << "####################################################################################" << std::endl
            << "##############                  TIVSEG COMMAND LINE                 ################" << std::endl
            << "####################################################################################" << std::endl
            << std::endl;

  while (m_handleInput)
  {
    std::cout << "> ";

    std::cin.clear();
    std::getline(std::cin, userCommand);

    evalUserInput(userCommand);
  }
}

bool TerminalHandler::isInAutoMode() const { return m_isInAutoMode; }

bool TerminalHandler::isRunning() const { return m_handleInput; }
