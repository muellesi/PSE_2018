#include <string>
#include <memory>

#include <gtest/gtest.h>

#include "../DriveCommandHandler.hpp"
#include "../AutoModeController.hpp"
#include "../ManualModeController.hpp"
#include "../Logging.hpp"

#include "mocks/TerminalHandler.hpp"

class TerminalHandlerTest : public ::testing::Test
{
protected:
  std::shared_ptr<DriveCommandHandler> driveCommandHandler;
  std::shared_ptr<AutoModeController> autoModeController;
  std::shared_ptr<ManualModeController> manualModeController;
  std::shared_ptr<TerminalHandler> terminalHandler;

  void SetUp() override
  {
    driveCommandHandler  = std::make_shared<DriveCommandHandler>();
    autoModeController   = std::make_shared<AutoModeController>(driveCommandHandler);
    manualModeController = std::make_shared<ManualModeController>(driveCommandHandler);
    terminalHandler      = std::make_shared<TerminalHandler>(manualModeController, autoModeController);

    // TerminalHandler sets a default log level, so let's revert this to verbose
    Logging::setMaxLevel(DIAG_VERBOSE);
  }

  void TearDown() override
  {
    // To be sure, also revert to verbose after every test case
    Logging::setMaxLevel(DIAG_VERBOSE);
  }
};

/**
 * \brief tests the TerminalHandler::splitString() function
 */
TEST_F(TerminalHandlerTest, SPLITSTRING)
{
  // Test splitting at space character
  std::string testStr = "Mode Script 0 C:\\path/to folder\\with spaces";
  std::vector<std::string> result;

  terminalHandler->splitString(testStr, result, " ");

  ASSERT_EQ(result.size(), (size_t)6);
  ASSERT_EQ(result[0], "Mode");
  ASSERT_EQ(result[1], "Script");
  ASSERT_EQ(result[2], "0");
  ASSERT_EQ(result[3], "C:\\path/to");
  ASSERT_EQ(result[4], "folder\\with");
  ASSERT_EQ(result[5], "spaces");

  // Test splitting at other characters, such as commas e.g.
  std::string testStr2 = "Mode,Script,0,C:\\path/to,folder\\with,spaces";
  std::vector<std::string> result2;

  terminalHandler->splitString(testStr2, result2, ",");

  ASSERT_EQ(result2.size(), (size_t)6);
  ASSERT_EQ(result2[0], "Mode");
  ASSERT_EQ(result2[1], "Script");
  ASSERT_EQ(result2[2], "0");
  ASSERT_EQ(result2[3], "C:\\path/to");
  ASSERT_EQ(result2[4], "folder\\with");
  ASSERT_EQ(result2[5], "spaces");
}

/**
 * \brief test parsing of the mode-command - handled by TerminalHandler::handleModeCommand()
 */
TEST_F(TerminalHandlerTest, MODECOMMAND)
{
  std::vector<std::string> cmdTokens;
  cmdTokens.emplace_back("mode");
  cmdTokens.emplace_back("1");

  // mode 1 should be a valid command
  ASSERT_EQ(terminalHandler->handleModeCommand(cmdTokens), true);

  // command is now "mode 1 stuff" - which is invalid
  cmdTokens.emplace_back("stuff");
  ASSERT_EQ(terminalHandler->handleModeCommand(cmdTokens), false);

  cmdTokens.pop_back();
  cmdTokens.pop_back();

  // command is now "mode 10" - which should be invalid since only modes 1 and two are allowed
  cmdTokens.emplace_back("10");
  ASSERT_EQ(terminalHandler->handleModeCommand(cmdTokens), false);
}

/**
 * \brief test parsing of the set command if the first parameter is "-l" - handled by
 * TerminalHandler::HandleSetCommand() sets log level so only values between 0 and 4 are allowed
 */
TEST_F(TerminalHandlerTest, SET_L_COMMAND)
{
  std::vector<std::string> cmdTokens;

  cmdTokens.emplace_back("set");
  cmdTokens.emplace_back("-l");
  cmdTokens.emplace_back("1");

  // command "set -l 1" should be valid
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), true);

  // After screwing around with the log level, reset it to testing default in order to get proper log messages later on
  Logging::setMaxLevel(DIAG_VERBOSE);

  cmdTokens.pop_back();

  // command "set -l 10" should fail because log levels have to be >0 and <5
  cmdTokens.emplace_back("10"); /* Wrong parameter */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);

  Logging::setMaxLevel(DIAG_VERBOSE);

  // command "set -l" should be invalid since the level parameter is missing
  cmdTokens.pop_back(); /* no parameter */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);

  Logging::setMaxLevel(DIAG_VERBOSE);

  // command "set -l 3 10" should be invalid because it has too many paramters-
  cmdTokens.emplace_back("3");
  cmdTokens.emplace_back("10"); /* Too many parameters */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);

  Logging::setMaxLevel(DIAG_VERBOSE);
}

/**
 * \brief test parsing of the set command if the first parameter is "-t" - handled by
 * TerminalHandler::HandleSetCommand() sets timeout, so only positive values are allowed
 */
TEST_F(TerminalHandlerTest, SET_T_COMMAND)
{
  std::vector<std::string> cmdTokens;

  cmdTokens.emplace_back("set");
  cmdTokens.emplace_back("-t");
  cmdTokens.emplace_back("111.123");

  // command "set -t 111.123" should be successful
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), true);

  cmdTokens.pop_back();

  // command "set -t -10.1" should fail since negative times don't make sense
  cmdTokens.emplace_back("-10.1"); /* Wrong parameter */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);

  // command "set -t" should fail since it is missing a parameter
  cmdTokens.pop_back(); /* no parameter */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);

  // command "set -t 10 10" should fail because it has too many parameters
  cmdTokens.emplace_back("10");
  cmdTokens.emplace_back("10"); /* Too many parameters */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);
}

/**
 * \brief test parsing of the set command if the first parameter is "-d" - handled by
 * TerminalHandler::HandleSetCommand() sets distance to vehicle in front so only positive values are allowed
 */
TEST_F(TerminalHandlerTest, SET_D_COMMAND)
{
  std::vector<std::string> cmdTokens;

  cmdTokens.emplace_back("set");
  cmdTokens.emplace_back("-d");
  cmdTokens.emplace_back("111.123");

  // command "set -d 111.123" should be successful
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), true);

  cmdTokens.pop_back();

  // command "set -d -10.1" should fail because negative distances don't make sense for this application
  cmdTokens.emplace_back("-10.1"); /* Wrong parameter */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);

  // command "set -d" should fail since it does not have enough parameters
  cmdTokens.pop_back(); /* no parameter */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);

  // command "set -d 10 10" should fail because it has too many parameters
  cmdTokens.emplace_back("10");
  cmdTokens.emplace_back("10"); /* Too many parameters */
  ASSERT_EQ(terminalHandler->handleSetCommand(cmdTokens), false);
}

/**
 * \brief tests whether TerminalHandler::handleDriveCommand() correctly checks for the number of supplied arguments
 */
TEST_F(TerminalHandlerTest, DRIVE_COMMAND_NUM_PARAMS)
{
  std::vector<std::string> cmdTokens;
  terminalHandler->evalUserInput("set -d 100");

  cmdTokens.emplace_back("drive");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);  // no argument --> fail
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);  // only one  argument --> fail
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);  // two arguments --> fail
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), true);  // three arguments --> success
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);  // four arguments --> fail
}

/**
 * \brief Tests whether TerminalHandler::handleDriveCommand() accepts non-numerical input for its three arguments
 */
TEST_F(TerminalHandlerTest, DRIVE_COMMAND_PARAM_SANITY)
{
  std::vector<std::string> cmdTokens;
  cmdTokens.emplace_back("drive");
  cmdTokens.emplace_back("a");
  cmdTokens.emplace_back(";");
  cmdTokens.emplace_back("'");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);
}

/**
 * \brief Test whether drive command times are handled correctly in TerminalHandler::handleDriveCommand()
 */
TEST_F(TerminalHandlerTest, DRIVE_COMMAND_TIME)
{
  std::vector<std::string> cmdTokens;

  terminalHandler->evalUserInput("set -t 1");

  // first, supply a valid command which should succeed
  cmdTokens.emplace_back("drive");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");

  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), true);

  cmdTokens.pop_back();
  cmdTokens.pop_back();
  cmdTokens.pop_back();

  // negative times should not work
  cmdTokens.emplace_back("-10");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);

  cmdTokens.pop_back();
  cmdTokens.pop_back();
  cmdTokens.pop_back();

  // huge times should work though
  cmdTokens.emplace_back("1000");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), true);
}

/**
 * \brief Tests whether TerminalHandler::handleDriveCommand() handles various velocity values correctly
 */
TEST_F(TerminalHandlerTest, DRIVE_COMMAND_VELO)
{
  std::vector<std::string> cmdTokens;

  terminalHandler->evalUserInput("set -t 1");

  // first, supply a valid command --> should be successful
  cmdTokens.emplace_back("drive");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), true);

  cmdTokens.pop_back();
  cmdTokens.pop_back();
  cmdTokens.pop_back();

  // velocities that are not in the interval of -100...100 should fail
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("-100.1");
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);

  cmdTokens.pop_back();
  cmdTokens.pop_back();
  cmdTokens.pop_back();

  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("100.1");
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);
}

/**
 * \brief Tests whether TerminalHandler::handleDriveCommand() handles various steering values correctly
 */
TEST_F(TerminalHandlerTest, DRIVE_COMMAND_STEER)
{
  std::vector<std::string> cmdTokens;

  terminalHandler->evalUserInput("set -t 1");

  // first, supply a valid command --> should be successful
  cmdTokens.emplace_back("drive");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), true);

  cmdTokens.pop_back();
  cmdTokens.pop_back();
  cmdTokens.pop_back();

  // steering values that are not in the interval of -100...100 should fail
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("-100.1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);

  cmdTokens.pop_back();
  cmdTokens.pop_back();
  cmdTokens.pop_back();

  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("1");
  cmdTokens.emplace_back("100.1");
  ASSERT_EQ(terminalHandler->handleDriveCommand(cmdTokens), false);
}

/**
 * \brief Tests whether TerminalHandler::handleQuitCommand() handles user input correctly
 */
TEST_F(TerminalHandlerTest, DRIVE_COMMAND_QUIT)
{
  // Check whether m_handleInput was initialized correctly
  ASSERT_EQ(terminalHandler->isRunning(), true);

  // test "quit"
  terminalHandler->evalUserInput("quit");
  ASSERT_EQ(terminalHandler->isRunning(), false);

  // test "QUIT"
  terminalHandler->m_handleInput = true;
  terminalHandler->evalUserInput("QUIT");
  ASSERT_EQ(terminalHandler->isRunning(), false);

  // test "q"
  terminalHandler->m_handleInput = true;
  terminalHandler->evalUserInput("q");
  ASSERT_EQ(terminalHandler->isRunning(), false);

  terminalHandler->m_handleInput = true;
}

/****************************************************************
 *
 * Unfortunataly there is no possibility to use gmock. Otherwise we could test quite easily whether evalUserInput()
 * calls the correct submethods.
 *
 *****************************************************************/

/*
 * The following test routine invokes the terminal interface which blocks execution and waits for user input.
 * Only enable this if you want to test the terminal manually on x86
 */

TEST_F(TerminalHandlerTest, DISABLED_BLOCKING_DONT_ENABLE) { terminalHandler->startInputHandling(); }