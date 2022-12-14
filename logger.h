#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <chrono>
#include <ctime>
#include <cstring>
#include <filesystem>
#include <stdarg.h>
#include <unistd.h>

class logger {
private:
    static std::string logFile;
    static std::string path;
    static void clearLogs();

public:

    static std::fstream f;
    static void log(const std::string& text, const std::string& color);

    static void warn(const std::string& text);
    static void error(const std::string& text);
    static void info(const std::string& text);
    static void success(const std::string& text);

    //char* formats
    static void warn(const char* text);
    static void error(const char* text);
    static void info(const char* text);
    static void success(const char* text);
};


#endif //LOGGER_H
