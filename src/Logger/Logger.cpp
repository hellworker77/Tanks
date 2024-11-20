//
// Created by iljap on 11/17/2024.
//

#include "Logger.h"


void Logger::subscribe(Logger::Subscriber subscriber) {
    m_subscriber = std::move(subscriber);
}

void Logger::setLogLevel(LogLevel logLevel) {
    m_logLevel = logLevel;
}


void Logger::print(const std::string &message, bool logging) {
    std::string log;
    print(message, "[PRINT]", m_subscriber.m_messageColor, log);

    if(m_logLevel <= ALL && logging){
        fileLog(log);
    }

}

void Logger::warning(const std::string &message, bool logging) {
    std::string log;
    print(message, "[WARNING]", WARNING_COLOR, log);
    if(m_logLevel <= WARNING && logging){
        fileLog(log);
    }
}

void Logger::info(const std::string &message, bool logging) {
    std::string log;
    print(message, "[INFO]", INFO_COLOR, log);
    if(m_logLevel <= INFO && logging){
        fileLog(log);
    }
}

void Logger::fatal(const std::string &message, bool logging) {
    std::string log;
    print(message, "[FATAL]", FATAL_COLOR, log);
    if(m_logLevel <= FATAL && logging){
        fileLog(log);
    }
}

void Logger::success(const std::string &message, bool logging) {
    std::string log;
    print(message, "[SUCCESS]", SUCCESS_COLOR, log);
    if(m_logLevel <= SUCCESS && logging){
        fileLog(log);
    }
}

void Logger::message(const std::string &message, bool logging) {
    std::string log;
    print(message, "[MESSAGE]", DEFAULT_COLOR, log);
    if(m_logLevel <= MESSAGE && logging){
        fileLog(log);
    }
}



