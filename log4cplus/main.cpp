#include <log4cplus/log4cplus.h>

void main_console()
{
    //��Initializer����г�ʼ��
    log4cplus::Initializer initializer;

    //��1��������ConsoleAppender
    log4cplus::SharedAppenderPtr appender(new log4cplus::ConsoleAppender());

    //��2��������Appender�����ƺ������ʽ��SimpleLayout��
    appender->setName(LOG4CPLUS_TEXT("console"));
    appender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout));

    //��3�������һ��Loggerʵ��������������־����ȼ���ֵ
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("test"));
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    //��4����ΪLoggerʵ�����ConsoleAppender
    logger.addAppender(appender);

    //��5����ʹ�ú꽫��־���
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world"));
}

void main_txtFile() {
    //��Initializer����г�ʼ��
    log4cplus::Initializer initializer;

    //��1��������ConsoleAppender��FileAppender(����app��ʾ����׷�ӵ��ļ�)
    log4cplus::SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender);
    log4cplus::SharedAppenderPtr fileAppender(new log4cplus::FileAppender(
        LOG4CPLUS_TEXT("log.txt"),
        std::ios_base::app
    )
    );

    //��2��������Appender�����ƺ������ʽ
    //ConsoleAppenderʹ��SimpleLayout
    //FileAppenderʹ��PatternLayout
    consoleAppender->setName(LOG4CPLUS_TEXT("console"));
    consoleAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout()));
    fileAppender->setName(LOG4CPLUS_TEXT("file"));
    log4cplus::tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S,%Q} [%t] %-5p %c - %m [%l]%n");
    fileAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));

    //��3�������һ��Loggerʵ��������������־����ȼ���ֵ
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("test"));
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    //��4����ΪLoggerʵ�����ConsoleAppender��FileAppender
    logger.addAppender(consoleAppender);
    logger.addAppender(fileAppender);

    //��5����ʹ�ú꽫��־���
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world"));

}

int main() {
    main_txtFile();
    return 0;
}