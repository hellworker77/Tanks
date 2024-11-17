//
// Created by iljap on 11/17/2024.
//

#ifndef BATTLECITY_LOGGER_H
#define BATTLECITY_LOGGER_H

#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <utility>

#define ERROR_COLOR 0xC
#define DEFAULT_COLOR 0xF

class Logger {
public:
    Logger() = default;
    ~Logger() = default;

    struct Subscriber{
        std::string target = "ENGINE";

        char timeColor;
        char targetColor;
        char messageColor;

        bool displayTime;
    };

public:
    virtual void print(const std::string& message);
    virtual void error(const std::string& message);
    virtual void subscribe(Subscriber subscriber);
private:
    HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Subscriber m_subscriber;
    void print(const std::string& message, bool isError){
        char error_color = 12;

        if (m_subscriber.displayTime) {
            std::time_t t = std::time(nullptr);
            std::tm *time_info = std::localtime(&t);
            std::ostringstream oss;

            oss << "["
                << std::setw(2) << std::setfill('0') << (time_info->tm_mon + 1) << "."
                << std::setw(2) << std::setfill('0') << time_info->tm_mday << " "
                << std::setw(2) << std::setfill('0') << time_info->tm_hour << ":"
                << std::setw(2) << std::setfill('0') << time_info->tm_min << "]";


            std::string current_time = oss.str();
            SetConsoleTextAttribute(m_hConsole, m_subscriber.timeColor);
            std::cout << oss.str() << " ";
        }

        SetConsoleTextAttribute(m_hConsole, m_subscriber.targetColor);
        std::cout << m_subscriber.target << ": ";

        if (isError) {
            SetConsoleTextAttribute(m_hConsole, ERROR_COLOR);
        } else {
            SetConsoleTextAttribute(m_hConsole, m_subscriber.messageColor);
        }

        std::cout << message << std::endl;

        SetConsoleTextAttribute(m_hConsole, DEFAULT_COLOR);
    }
};


#endif //BATTLECITY_LOGGER_H
