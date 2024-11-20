//
// Created by iljap on 11/17/2024.
//
#pragma once
#ifndef BATTLECITY_LOGGER_H
#define BATTLECITY_LOGGER_H

#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <filesystem>

#define WARNING_COLOR 0x4
#define INFO_COLOR 0x9
#define SUCCESS_COLOR 0xA
#define FATAL_COLOR 0xC
#define DEFAULT_COLOR 0xF

enum LogLevel {
    ALL,
    MESSAGE,
    SUCCESS,
    INFO,
    WARNING,
    FATAL
};

class Logger {
public:
    struct Subscriber {
        friend Logger;
    public:
        Subscriber() = default;

        Subscriber(const std::string &target,
                   char targetColor,
                   char messageColor,
                   bool displayTime) {

            m_target = target;
            m_targetColor = targetColor;
            m_messageColor = messageColor;
            m_displayTime = displayTime;
        }

    private:

        std::string m_target = "ENGINE";
        char m_targetColor = DEFAULT_COLOR;
        char m_messageColor = DEFAULT_COLOR;
        bool m_displayTime = DEFAULT_COLOR;
    };
public:
    void print(const std::string &message, bool logging = true);

    void warning(const std::string &message, bool logging = true);

    void info(const std::string &message, bool logging = true);

    void fatal(const std::string &message, bool logging = true);

    void success(const std::string &message, bool logging = true);

    void message(const std::string &message, bool logging = true);

    void subscribe(Subscriber subscriber);

    void setLogLevel(LogLevel logLevel);

    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

    static Logger &getInstance() {
        static Logger m_instance;
        return m_instance;
    }

private:
    Logger() = default;

    ~Logger() = default;

    HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Subscriber m_subscriber;
    LogLevel m_logLevel = WARNING;

    void print(const std::string &message, const char* suffix, char color, std::string& formated) {

        std::time_t t = std::time(nullptr);
        std::tm *time_info = std::localtime(&t);
        std::ostringstream oss;

        oss << "["
            << std::setw(2) << std::setfill('0') << (time_info->tm_mon + 1) << "."
            << std::setw(2) << std::setfill('0') << time_info->tm_mday << " "
            << std::setw(2) << std::setfill('0') << time_info->tm_hour << ":"
            << std::setw(2) << std::setfill('0') << time_info->tm_min << "]";


        std::string current_time = oss.str();


        if (m_subscriber.m_displayTime) {
            SetConsoleTextAttribute(m_hConsole, DEFAULT_COLOR);
            std::cout << current_time << " ";
        }

        SetConsoleTextAttribute(m_hConsole, m_subscriber.m_targetColor);
        std::cout << m_subscriber.m_target << " ";

        SetConsoleTextAttribute(m_hConsole, color);

        std::cout << suffix <<": " << message << std::endl;

        SetConsoleTextAttribute(m_hConsole, DEFAULT_COLOR);

        formated = current_time + " "+ m_subscriber.m_target + " " + suffix + ": " + message;
    }

    void fileLog(const std::string& log){
        try {
            std::filesystem::path logDir = "logs";
            if (!std::filesystem::exists(logDir)) {
                std::filesystem::create_directory(logDir);
                message("Created logs directory...", false);
            }

            std::filesystem::path logFile = logDir / "runtimelogs.txt";

            std::ofstream file(logFile, std::ios::app);
            if (!file) {
                throw std::ios_base::failure("Unable to open file runtimelogs.txt");
            }
            file << log << std::endl;
        } catch (const std::exception& e) {
            warning(e.what(), false);
            std::cerr << "[ERROR]: " << e.what() << std::endl;
        }

    }
};


#endif //BATTLECITY_LOGGER_H
