///////////////////////////////////////////////////////////
//  TerminalHandler.h
//  Implementation of the Class TerminalHandler
//  Created on:      05-Jun-2018 14:42:06
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "AutoModeController.hpp"
#include "ManualModeController.hpp"
#include "Logging.hpp"

class TerminalHandler
{
public:
  /**
   * \brief Constructs a new TerminalHandler.
   * \param manualModeController Controller for manual operation.
   * \param autoModeController Controller for automatic marker based operation.
   */
  TerminalHandler(std::shared_ptr<ManualModeController> manualModeController, std::shared_ptr<AutoModeController> autoModeController);

  virtual ~TerminalHandler();

  /**
   * \brief Aborts all running operations.
   */
  void abort();

  /**
   * \brief Main entry point to the TerminalHandler.
   * Displays a banner and opens a user prompt.
   * ONLY CALL THIS FROM A SEPARATE THREAD!
   */
  void startInputHandling();

  /**
   * \brief Checks whether the user chose to operate in automatic mode.
   * \return value of m_IsInAutoMode.
   */
  bool isInAutoMode() const;

  /**
   * \brief The user can stop the program via terminal. main() uses this method to check for this case and terminate.
   * \return value of m_handleInput.
   */
  bool isRunning() const;

private:
  std::shared_ptr<ManualModeController> m_manualModeController;
  std::shared_ptr<AutoModeController> m_autoModeController;
  std::atomic<bool> m_isInAutoMode{false};
  std::atomic<bool> m_handleInput{true};
  std::atomic<bool> m_abortScript{true};

  /**
   * \brief Handles a command if its first token is `set`.
   * Sets the specified values, as described in the specification.
   * \param commandTokens A token representation of the entered user command, split at every space character.
   * \return true if the user input did not contain errors and the command succeeded, false otherwise.
   */
  bool handleSetCommand(const std::vector<std::string>& commandTokens);

  /**
   * \brief Handles a command if its first token is `drive`.
   * Drives with the given speed in a given direction for a given time if all three parameters.
   * are within the boundaries that are given in the specification.
   * \param commandTokens A token representation of the entered user command, split at every space character.
   * \return true if the user input did not contain errors and the command succeeded. false otherwise.
   */
  bool handleDriveCommand(const std::vector<std::string>& commandTokens);

  /**
   * \brief Handles a command if its first token is `script`.
   * If a script is found at the given path, this command handler executes the script line by line.
   * \param commandTokens A token representation of the entered user command, split at every space character.
   * \return true if the user input did not contain errors and the command succeeded. false otherwise.
   */
  bool handleScriptCommand(const std::vector<std::string>& commandTokens, int recursionDepth);

  /**
   * \brief Handles a command if its first token is `search`.
   * Starts a new blocking marker search.
   * \param commandTokens A token representation of the entered user command, split at every space character.
   * \return true if the user input did not contain errors and the command succeeded. false otherwise.
   */
  bool handleSearchCommand(const std::vector<std::string>& commandTokens);

  /**
   * \brief Handles a command if its first token is `mode`.
   * If the second token is a valid mode of operation according to the specification (1 or 2),
   * the mode is switched accordingly.
   * \param commandTokens A token representation of the entered user command, split at every space character.
   * \return true if the user input did not contain errors and the command succeeded. false otherwise.
   */
  bool handleModeCommand(const std::vector<std::string>& commandTokens);

  /**
   * \brief Handler for the case that the user entered quit, q or QUIT.
   * \param commandTokens A token representation of the entered user command, split at every space character.
   * \return always true for now.
   */
  bool handleQuitCommand(const std::vector<std::string>& commandTokens);

  /**
   * \brief Gets called whenever the user entered a new line and tries to parse the entered command.
   * \param input Command string as entered by the user.
   * \param scriptMode Scripts also use this function. In order to block them from using certain commands,
   * handleScriptCommand() sets this to true.
   * \param recursionDepth A script using the script command to call itself might cause infinite recursion.
   * This parameter counts the depth of the current call so we can abort if it gets too deep.
   * \return true if input contained a valid command and the command execution succeeded.
   */
  bool evalUserInput(const std::string& input, bool scriptMode = false, int recursionDepth = 0);

  /**
   * \brief Splits a given input string at a 1-character delimiter.
   * \param input String that has to be split.
   * \param result Reference to a existing vector that wil lbe used to store the resulting tokens.
   * \param delim 1-character delimiter that is used to split the input string.
   */
  static void splitString(const std::string& input, std::vector<std::string>& result, const char* delim);

  /**
   * \brief checks if a script called setup.pse is placed besides the application executable.
   * If such a script is found, it is executed.
   * \return true if the script was successfully executed.
   */
  bool tryRunSetupScript();

  static constexpr int MAX_RECURSION_DEPTH = 5;

  // only log errors by default
  static constexpr DiagnosticLevel DEFAULT_DIAGNOSTICS_MAX_LEVEL = DiagnosticLevel::DIAG_ERROR;
};
