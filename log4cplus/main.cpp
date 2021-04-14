#include <log4cplus/log4cplus.h>

void main_console()
{
    //用Initializer类进行初始化
    log4cplus::Initializer initializer;

    //第1步：创建ConsoleAppender
    log4cplus::SharedAppenderPtr appender(new log4cplus::ConsoleAppender());

    //第2步：设置Appender的名称和输出格式（SimpleLayout）
    appender->setName(LOG4CPLUS_TEXT("console"));
    appender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout));

    //第3步：获得一个Logger实例，并设置其日志输出等级阈值
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("test"));
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    //第4步：为Logger实例添加ConsoleAppender
    logger.addAppender(appender);

    //第5步：使用宏将日志输出
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world"));
}

void main_txtFile() {
    //用Initializer类进行初始化
    log4cplus::Initializer initializer;

    //第1步：创建ConsoleAppender和FileAppender(参数app表示内容追加到文件)
    log4cplus::SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender);
    log4cplus::SharedAppenderPtr fileAppender(new log4cplus::FileAppender(
        LOG4CPLUS_TEXT("log.txt"),
        std::ios_base::app
    )
    );

    //第2步：设置Appender的名称和输出格式
    //ConsoleAppender使用SimpleLayout
    //FileAppender使用PatternLayout
    consoleAppender->setName(LOG4CPLUS_TEXT("console"));
    consoleAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout()));
    fileAppender->setName(LOG4CPLUS_TEXT("file"));
    log4cplus::tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S,%Q} [%t] %-5p %c - %m [%l]%n");
    fileAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));

    //第3步：获得一个Logger实例，并设置其日志输出等级阈值
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("test"));
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    //第4步：为Logger实例添加ConsoleAppender和FileAppender
    logger.addAppender(consoleAppender);
    logger.addAppender(fileAppender);

    //第5步：使用宏将日志输出
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world"));

}

int main() {
    main_txtFile();
    return 0;
}