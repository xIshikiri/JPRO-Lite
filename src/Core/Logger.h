#ifdef _DEBUG
#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <ctime>

enum class LogLevel : uint8_t { INFO, WARN, ERR };

inline const char* LogLevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARN: return "WARN";
    case LogLevel::ERR:  return "ERROR";
    default:             return "UNKNOWN";
    }
}

inline WORD LogLevelToColor(LogLevel level) {
    switch (level) {
    case LogLevel::INFO: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // White
    case LogLevel::WARN: return FOREGROUND_RED | FOREGROUND_GREEN;                  // Yellow
    case LogLevel::ERR:  return FOREGROUND_RED;                                     // Red
    default:             return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

inline std::ofstream& GetLogFile() {
    static bool initialized = false;
    static std::ofstream logFile;

    if (!initialized) {
        logFile.open("log.txt", std::ios::out | std::ios::trunc);
        initialized = true;
    }

    return logFile;
}

inline void InternalDebugLog(LogLevel level, const std::string& message) {
    std::ostringstream oss;
    oss << "[" << LogLevelToString(level) << "] "
        << message << std::endl;

    // Console color
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = LogLevelToColor(level);
    SetConsoleTextAttribute(hConsole, color);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // OutputDebugString
    OutputDebugStringA(oss.str().c_str());

    // Log file
    GetLogFile() << oss.str();
}

#define DEBUG_LOG(level, message)                                \
    do {                                                         \
        std::ostringstream oss;                                  \
        oss << message;                                          \
        InternalDebugLog(level, oss.str());                      \
    } while (0)
#else
#define DEBUG_LOG(level, message) do {} while(0)
#endif
