//
// Created by iljap on 11/17/2024.
//

#include "Logger.h"


void Logger::subscribe(Logger::Subscriber subscriber) {
    m_subscriber = std::move(subscriber);
}

void Logger::print(const std::string &message) {
    print(message, false);
}

void Logger::error(const std::string &message) {
    print(message, true);
}