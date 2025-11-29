#if __cplusplus < 202002L
#error                                                                         \
    "Logger: C++20 or newer is required (uses <format>). Recommended is C++23."
#endif

/*
 * Author: KopyTKG
 * Version: 2.0.0 - Standalone
 * License: MIT
 * Description: A simple and thread-safe logging utility for C++ applications.
 */

#ifndef LOG_HPP
#define LOG_HPP

#include <ctime>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <string_view>

constexpr const char *ANSI_RESET = "\u001b[0m";
// Colors
constexpr const char *ANSI_RED = "\u001b[31m";
constexpr const char *ANSI_YELLOW = "\u001b[33m";
constexpr const char *ANSI_CYAN = "\u001b[36m";
constexpr const char *ANSI_MAGENTA = "\u001b[35m";
constexpr const char *ANSI_GRAY = "\u001b[38;5;244m";

// Font styles
constexpr const char *ANSI_BOLD = "\u001b[1m";
constexpr const char *ANSI_UNDERLINE = "\u001b[4m";
constexpr const char *ANSI_ITALIC = "\u001b[3m";
constexpr const char *ANSI_BLINK = "\u001b[5m";
constexpr const char *ANSI_INVERSE = "\u001b[7m";
constexpr const char *ANSI_STRIKETHROUGH = "\u001b[9m";

// Log levels
enum class Level { SILENT = 0, ERROR = 1, WARN = 2, DEBUG = 3 };

class Log {
public:
  static auto getInstance() -> Log * {
    static Log instance;
    return &instance;
  }

  // Log level setter
  void setLogLevel(Level level) { log_level = level; }

  // Log file output setter with validation
  void setLogToFile(bool toFile) {
    if (toFile && !log_file_path.empty()) {
      log_to_file = toFile;
    } else {
      log_to_file = false;
      std::cerr << "Log file path is empty. Cannot enable logging to file."
                << std::endl;
    }
  }

  // Console output setter
  void setLogToConsole(bool toConsole) { log_to_console = toConsole; }

  // Log file path setter
  void setLogFilePath(const std::string &path) { log_file_path = path; }

  // Log level getter
  Level getLogLevel() const { return log_level; }

  // File logging state
  bool getLogToFile() const { return log_to_file; }

  // Console logging state
  bool getLogToConsole() const { return log_to_console; }

  // Log file path getter
  const std::string &getLogFilePath() const { return log_file_path; }

  // Full string methods
  static void infoln(const char *message) {
    getInstance()->infoln_private(message);
  }
  static void warnln(const char *message) {
    getInstance()->warnln_private(message);
  }
  static void errorln(const char *message) {
    getInstance()->errorln_private(message);
  }
  static void debugln(const char *message) {
    getInstance()->debugln_private(message);
  }

  // Formatted string methods
  template <typename... Args>
  static void infof(std::string_view format, Args &&...args) {
    infoln(std::vformat(format, std::make_format_args(args...)).c_str());
  }

  template <typename... Args>
  static void warnf(std::string_view format, Args &&...args) {
    warnln(std::vformat(format, std::make_format_args(args...)).c_str());
  }

  template <typename... Args>
  static void errorf(std::string_view format, Args &&...args) {
    errorln(std::vformat(format, std::make_format_args(args...)).c_str());
  }

  template <typename... Args>
  static void debugf(std::string_view format, Args &&...args) {
    debugln(std::vformat(format, std::make_format_args(args...)).c_str());
  }

private:
  // Setup singleton
  Log() {};
  ~Log() {};
  Log(const Log &) = delete;
  Log &operator=(const Log &) = delete;
  Log(Log &&) = delete;
  Log &operator=(Log &&) = delete;

  // Get current time as string
  std::string getTime() {
    time_t timestamp;
    time(&timestamp);
    struct tm *tm_info = localtime(&timestamp);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y.%m.%d %H:%M:%S", tm_info);
    return std::string(buffer);
  }

  void infoln_private(const char *message) {

    std::ostringstream ossCLI;
    ossCLI << ANSI_GRAY << getTime() << ANSI_RESET << ANSI_CYAN << " INFO "
           << ANSI_RESET << message;
    std::string outputCLI = ossCLI.str();

    std::ostringstream ossFile;
    ossFile << getTime() << " INFO " << message;
    std::string outputFile = ossFile.str();

    if (log_level >= Level::ERROR) {
      writeToConsole(outputCLI);
      writeToFile(outputFile);
    }
  }

  void warnln_private(const char *message) {

    std::ostringstream ossCLI;
    ossCLI << ANSI_GRAY << getTime() << ANSI_RESET << ANSI_YELLOW << " WARN "
           << ANSI_RESET << message;
    std::string outputCLI = ossCLI.str();

    std::ostringstream ossFile;
    ossFile << getTime() << " WARN " << message;
    std::string outputFile = ossFile.str();

    if (log_level >= Level::WARN) {
      writeToConsole(outputCLI);
      writeToFile(outputFile);
    }
  }

  void errorln_private(const char *message) {

    std::ostringstream ossCLI;
    ossCLI << ANSI_GRAY << getTime() << ANSI_RESET << ANSI_RED << " ERRO "
           << ANSI_RESET << message;
    std::string outputCLI = ossCLI.str();

    std::ostringstream ossFile;
    ossFile << getTime() << " ERRO " << message;
    std::string outputFile = ossFile.str();

    if (log_level >= Level::ERROR) {
      writeToConsole(outputCLI);
      writeToFile(outputFile);
    }
  }
  void debugln_private(const char *message) {
    std::ostringstream ossCLI;
    ossCLI << ANSI_GRAY << getTime() << ANSI_RESET << ANSI_MAGENTA << " DEBG "
           << ANSI_RESET << message;
    std::string outputCLI = ossCLI.str();

    std::ostringstream ossFile;
    ossFile << getTime() << " DEBG " << message;
    std::string outputFile = ossFile.str();

    if (log_level >= Level::DEBUG) {
      writeToConsole(outputCLI);
      writeToFile(outputFile);
    }
  }

  Level log_level = Level::DEBUG;
  bool log_to_file = false;
  bool log_to_console = true;

  std::mutex log_mutex;

  std::string log_file_path = "log.txt";

  void writeToFile(std::string &message) {
    if (log_to_file) {
      std::lock_guard<std::mutex> lock(log_mutex);
      std::ofstream logFile(log_file_path, std::ios::app);
      if (logFile.is_open()) {
        logFile << message << std::endl;
      } else {
        std::cerr << "Failed to open log file: " << log_file_path << std::endl;
      }
    }
  }

  void writeToConsole(std::string &message) {
    if (log_to_console) {
      std::lock_guard<std::mutex> lock(log_mutex);
      std::cout << message << std::endl;
    }
  }
};

#endif // !LOG_HPP
