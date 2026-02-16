#include <iostream>
#include <cmath>
#include <vector>


class INumericOperationStrategy {
public:
    virtual double Execute(double value) = 0;
};

class SquareOperationStrategy: public INumericOperationStrategy {
public:
    double Execute(double value) override {
        return value * value;
    }
};
class CubeOperationStrategy: public INumericOperationStrategy {
public:
    double Execute(double value) override {
        return value * value * value;
    }
};

class SquareRootOperationStrategy: public INumericOperationStrategy {
public:
    double Execute(double value) override {
        return std::sqrt(value);
    }
};

class NumericProcessor {
private:
    INumericOperationStrategy* strategy;
public:
    NumericProcessor(INumericOperationStrategy* strategy) : strategy(strategy) {}

    void SetStrategy(INumericOperationStrategy* strategy){
        this->strategy = strategy;
    }

    double Process(double input) {

        return strategy->Execute(input);
    }

};

class IObserver {
public:
    virtual void OnResultCalculated(double result, const std::string& operationName) = 0;
};

class ResultPublisher {
private:
    std::vector<IObserver*> observers;

public:
    void AddObserver(IObserver* observer) {
        observers.push_back(observer);
    }

    void PublishResult(double result, const std::string& operationName) {
        for (auto observer : observers) {
            observer->OnResultCalculated(result, operationName);
        }
    }
};

class ConsoleObserver : public IObserver {
public:
    void OnResultCalculated(double result, const std::string& operationName) override {
        std::cout << "Operation: " << operationName << ", Result: " << result << std::endl;
    }
};

class HistoryLoggerObserver : public IObserver {
public:
    void OnResultCalculated(double result, const std::string& operationName) override {
        static std::vector<double> history;
        history.push_back(result);
        std::cout << "History Logger - Operation: " << operationName << ", Result: " << result << ", History Size: " << history.size() << std::endl;
    }
};

class ThresholdNotifierObserver: public IObserver {
public:
    void OnResultCalculated(double result, const std::string& operationName) override {
        if (result > 100) {
            std::cout << "Threshold exceeded for operation: " << operationName << ", Result: " << result << std::endl;
        }
    }
};

int main() {
    SquareOperationStrategy squareStrategy;
    CubeOperationStrategy cubeStrategy;
    SquareRootOperationStrategy sqrtStrategy;

    NumericProcessor processor(&squareStrategy);
    ResultPublisher publisher;

    ConsoleObserver consoleObserver;
    HistoryLoggerObserver historyLoggerObserver;
    ThresholdNotifierObserver thresholdObserver;

    publisher.AddObserver(&consoleObserver);
    publisher.AddObserver(&historyLoggerObserver);
    publisher.AddObserver(&thresholdObserver);

    double input = 5.0;

    double result = processor.Process(input);
    publisher.PublishResult(result, "Square");

    processor.SetStrategy(&cubeStrategy);
    result = processor.Process(input);
    publisher.PublishResult(result, "Cube");

    processor.SetStrategy(&sqrtStrategy);
    result = processor.Process(input);
    publisher.PublishResult(result, "Square Root");
};
