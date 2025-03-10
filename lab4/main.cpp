#include <iostream>
#include <fstream>
#include <list>
#include <memory>
#include <string>

struct CustomEvent {
    int id;
    std::string payload;
};

template <typename T>
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const T& eventData) = 0;
};

template <typename T>
class Subject {
public:
    Subject() = default;
    ~Subject() = default;

    void attach(std::shared_ptr<IObserver<T>> observer) {
        observers_.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver<T>> observer) {
        observers_.remove(observer);
    }

    void notify(const T& eventData) {
        for (const auto& observer : observers_) {
            if (observer) {
                observer->onEvent(eventData);
            }
        }
    }

    void addData(const T& data) {
        notify(data);
    }

private:
    std::list<std::shared_ptr<IObserver<T>>> observers_;
};

template <typename T>
class ConsoleObserver : public IObserver<T>, public std::enable_shared_from_this<ConsoleObserver<T>> {
public:
    void onEvent(const T& eventData) override {
        handleEvent(eventData);
    }

private:
    void handleEvent(const T& eventData) {
        std::cout << "ConsoleObserver: Event data = " << eventData << std::endl;
    }
};

template <>
void ConsoleObserver<CustomEvent>::handleEvent(const CustomEvent& eventData) {
    std::cout << "CustomEvent: { id: " << eventData.id << ", payload: " << eventData.payload << " }" << std::endl;
}

template <typename T>
class LoggingObserver : public IObserver<T> {
public:
    explicit LoggingObserver(const std::string& logFile)
        : logFile_(logFile) {
        file_.open(logFile_, std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error("Unable to open log file");
        }
    }

    ~LoggingObserver() {
        if (file_.is_open()) {
            file_.close();
        }
    }

    void onEvent(const T& eventData) override {
        handleEvent(eventData);
    }

private:
    void handleEvent(const T& eventData) {
        if (file_.is_open()) {
            file_ << "LoggingObserver: Event data = " << eventData << std::endl;
        }
    }

    std::ofstream file_;
    std::string logFile_;
};

template <>
void LoggingObserver<CustomEvent>::handleEvent(const CustomEvent& eventData) {
    if (file_.is_open()) {
        file_ << "CustomEvent: { id: " << eventData.id << ", payload: " << eventData.payload << " }" << std::endl;
    }
}

int main() {
    auto intSubject = std::make_shared<Subject<int>>();

    auto intObserverConsole = std::make_shared<ConsoleObserver<int>>();
    auto intLoggingObserver = std::make_shared<LoggingObserver<int>>("log.txt");

    intSubject->attach(intObserverConsole);
    intSubject->attach(intLoggingObserver);
    intSubject->addData(42);

    auto stringSubject = std::make_shared<Subject<std::string>>();
    auto stringObserverConsole = std::make_shared<ConsoleObserver<std::string>>();
    auto stringLoggingObserver = std::make_shared<LoggingObserver<std::string>>("log.txt");

    stringSubject->attach(stringObserverConsole);
    stringSubject->attach(stringLoggingObserver);
    stringSubject->addData("Hello, Observer!!!");

    auto customSubject = std::make_shared<Subject<CustomEvent>>();
    auto customObserverConsole = std::make_shared<ConsoleObserver<CustomEvent>>();
    auto customLoggingObserver = std::make_shared<LoggingObserver<CustomEvent>>("log.txt");

    customSubject->attach(customObserverConsole);
    customSubject->attach(customLoggingObserver);
    customSubject->addData({228, "payload_data =)"});

    return 0;
}