#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <csignal>
#include <cstring>

#include <SensorManager.hpp>
#include <DriveController.hpp>

#include "AutoModeController.hpp"
#include "ManualModeController.hpp"
#include "DriveCommandHandler.hpp"
#include "TerminalHandler.hpp"
#include "FileLogger.hpp"

std::atomic<bool> g_doStep;

static bool s_flushLogInstant;

/**
 * \brief this functions has to run the whole time the program is alive.
 * It calls step() on the DriveController every 10 ms.
 */
void motorStep()
{
  while (g_doStep)
  {
#ifndef TEST_MODE
    DriveController::getInstance()->step();
#endif

    std::this_thread::sleep_for(std::chrono::microseconds(5000));
  }
}

/**
 * Main function of the project
 */
int main(int argc, char** argv)
{
  g_doStep          = true;
  s_flushLogInstant = true;

  // DriveController wants us to call step() every 10ms, so do so in a separate thread
  std::thread motorStepThread(&motorStep);

  sched_param sch;
  int policy;
  pthread_getschedparam(motorStepThread.native_handle(), &policy, &sch);
  sch.sched_priority = 99;
  if (pthread_setschedparam(motorStepThread.native_handle(), SCHED_FIFO, &sch))
  {
    DIAG_WARNING("Failed to setschedparam: %s ", std::strerror(errno));
  }

  // Module setup
  std::shared_ptr<DriveCommandHandler> driveCommandHandler   = std::make_shared<DriveCommandHandler>();
  std::shared_ptr<AutoModeController> autoModeController     = std::make_shared<AutoModeController>(driveCommandHandler);
  std::shared_ptr<ManualModeController> manualModeController = std::make_shared<ManualModeController>(driveCommandHandler);
  static std::shared_ptr<TerminalHandler> terminalHandler    = std::make_shared<TerminalHandler>(manualModeController, autoModeController);

  std::thread terminalThread(&TerminalHandler::startInputHandling, terminalHandler);

#ifdef TEST_MODE
  DriveController::getInstance()->setTestMode(true);
#endif

  // Install a signal handler
  std::signal(SIGINT, [](int signum) {
    DIAG_INFO("Caught signal %d", signum);
    terminalHandler->abort();
  });

  while (terminalHandler->isRunning())  // isRunning() returns false after the user decided to quit the program
  {
    SensorManager::getInstance()->runOnce();
    if (terminalHandler->isInAutoMode())
    {
      // Runs every automode module's processData() method
      autoModeController->step();
    }
    else
    {
      // Calls SensorManager::runOnce() during blocking getline() in TerminalHandler::startInputHandling() to get
      // constant video output
      manualModeController->step();
    }
    if (s_flushLogInstant)
    {
      // FileLogger only writes messages to an in memory queue.
      // We need to call FileLogger::flushLogs() explicitly to write them to the log file
      FileLogger::getInstance().flushLogs();
    }

    DIAG_VERBOSE("FPS: %.2f", SensorManager::getInstance()->getFps());
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  g_doStep = false;

  terminalThread.join();
  DIAG_INFO("Terminal Thread shut down");
  motorStepThread.join();
  DIAG_INFO("Motor Thread shut down");

  std::cout << "Program ended!" << std::endl;
  return 0;
}
