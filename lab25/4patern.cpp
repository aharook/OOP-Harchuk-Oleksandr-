#include <iostream>
#include <string>
#include <functional>
#include <vector>



class ILogger {
public:
    virtual void Log(const std::string message) = 0;
};

class ConsoleLogger : public ILogger {
public:
    void Log(const std::string message) override {
        std::cout << "[Console] " << message << std::endl;
    }
};

class FileLogger : public ILogger {
public:
    void Log(const std::string message) override {
        std::cout << "[File] " << message << std::endl;
    }
};

class LoggerFactory {
public:
    virtual std::unique_ptr<ILogger> CreateLogger() = 0;
};

class ConsoleLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<ILogger> CreateLogger() override {
        return std::make_unique<ConsoleLogger>();
    }
};

class FileLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<ILogger> CreateLogger() override {
        return std::make_unique<FileLogger>();
    }
};

class LoggerManager {
private:
    static LoggerManager* instance;
    std::unique_ptr<LoggerFactory> factory;
    std::unique_ptr<ILogger> logger;

    LoggerManager() {}

public:
    static LoggerManager& GetInstance() {
        if (!instance)
            instance = new LoggerManager();
        return *instance;
    }

    void SetFactory(std::unique_ptr<LoggerFactory> newFactory) {
        factory = std::move(newFactory);
        logger = factory->CreateLogger();
    }

    ILogger* GetLogger() {
        return logger.get();
    }
};

class IDataProcessorStrategy {
public:
    virtual std::string Process(const std::string data) = 0;
};

class EncryptDataStrategy : public IDataProcessorStrategy {
public:
    std::string Process(const std::string data) override {
        return "Encrypted(" + data + ")";
    }
};

class CompressDataStrategy : public IDataProcessorStrategy {
public:
    std::string Process(const std::string data) override {
        return "Compressed(" + data + ")";
    }
};

class DataContext {
private:
    std::unique_ptr<IDataProcessorStrategy> strategy;

public:
    DataContext(std::unique_ptr<IDataProcessorStrategy> strat)
        : strategy(std::move(strat)) {}

    void SetStrategy(std::unique_ptr<IDataProcessorStrategy> strat) {
        strategy = std::move(strat);
    }

    std::string Execute(const std::string data) {
        return strategy->Process(data);
    }
};

class DataPublisher {
private:
    std::vector<std::function<void(const std::string)>> observers;

public:
    void Subscribe(std::function<void(const std::string)> observer) {
        observers.push_back(observer);
    }

    void PublishDataProcessed(const std::string data) {
        for (auto& obs : observers)
            obs(data);
    }
};

class ProcessingLoggerObserver {
public:
    void OnDataProcessed(const std::string data) {
        LoggerManager::GetInstance().GetLogger()->Log("Processed data: " + data);
    }
};

int main() {

    std::cout << "===== Scenario 1: Full Integration =====" << std::endl;

    LoggerManager::GetInstance().SetFactory(std::make_unique<ConsoleLoggerFactory>());

    DataContext context(std::make_unique<EncryptDataStrategy>());
    DataPublisher publisher;
    ProcessingLoggerObserver observer;

    publisher.Subscribe([&observer](const std::string data) {
        observer.OnDataProcessed(data);
    });

    std::string result1 = context.Execute("MyData");
    publisher.PublishDataProcessed(result1);

    std::cout << std::endl;
    std::cout << "===== Scenario 2: Dynamic Logger Change =====" << std::endl;

    LoggerManager::GetInstance().SetFactory(std::make_unique<FileLoggerFactory>());

    std::string result2 = context.Execute("MyData");
    publisher.PublishDataProcessed(result2);

    std::cout << "Check log.txt for file logging output." << std::endl;

    std::cout << std::endl;
    std::cout << "===== Scenario 3: Dynamic Strategy Change =====" << std::endl;

    LoggerManager::GetInstance().SetFactory(std::make_unique<ConsoleLoggerFactory>());

    context.SetStrategy(std::make_unique<CompressDataStrategy>());

    std::string result3 = context.Execute("MyData");
    publisher.PublishDataProcessed(result3);

    return 0;
}
