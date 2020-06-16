//
// Created by Simon on 28.06.2018.
//

#pragma once

/**
 * \brief Class to to write log messages to a file called "events.log". Messages are buffered in a queue and
 * are written to the file when flushLogs() is called or when the singleton instance gets destroyed
 */
class FileLogger
{
public:
  /**
   * \brief Takes the content of m_messageQueue and writes them to the log file
   */
  void flushLogs()
  {
    if (m_logFile)
    {
      while (!m_messageQueue.empty())
      {
        auto message = m_messageQueue.front();
        m_messageQueue.pop();
        size_t size     = message.size();
        const char* str = message.c_str();
        std::fwrite(str, sizeof(char), size, m_logFile);
      }
    }
  }

  /**
   * \brief Singleton getInstance()
   * \return an instance of this FileLogger
   */
  static FileLogger& getInstance()
  {
    static FileLogger m_instance;
    return m_instance;
  }

  ~FileLogger()
  {
    if (m_logFile)
    {
      flushLogs();
      std::fflush(m_logFile);
      std::fclose(m_logFile);
      m_logFile = NULL;
    }
  }

  /**
   * \brief pushes the message to the message queue
   * \param message the string that is to be pushed to the queue
   */
  // Do NOT pass by reference since message could be a temp variable
  void log(std::string message) { m_messageQueue.push(message); }

private:
  // disallow instantiation and copying
  FileLogger()
  {
    m_logFile = nullptr;
    m_logFile = std::fopen("events.log", "a");  // open the file in append mode

    // Start the log with a distinct message to be able to find the start of the most current log
    m_messageQueue.push("--------------------------------------------------------------------------------\n");
    m_messageQueue.push("Filelogger starting up...\n");
  }

  FileLogger(const FileLogger&) = default;
  FileLogger& operator          =(const FileLogger&);

  FILE* m_logFile;
  std::queue<std::string> m_messageQueue;
};