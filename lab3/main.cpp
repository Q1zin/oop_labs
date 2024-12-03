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
    Subject();
    ~Subject();

    void attach(std::shared_ptr<IObserver<T>> observer);
    void detach(std::shared_ptr<IObserver<T>> observer);
    void notify(const T& eventData);

    void addData(T data);

private:
    class SubjectImpl;
    std::unique_ptr<SubjectImpl> impl_;
    T data_;
};

template<typename T>
void Subject<T>::addData(T data) {
    this->data_ = data;
    notify(data);
}

template <typename T>
class Subject<T>::SubjectImpl {
public:
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

private:
    std::list<std::shared_ptr<IObserver<T>>> observers_;
};

template <typename T>
Subject<T>::Subject() : impl_(std::make_unique<SubjectImpl>()), data_{} {}

template <typename T>
Subject<T>::~Subject() = default;

template <typename T>
void Subject<T>::attach(std::shared_ptr<IObserver<T>> observer) {
    impl_->attach(observer);
}

template <typename T>
void Subject<T>::detach(std::shared_ptr<IObserver<T>> observer) {
    impl_->detach(observer);
}

template <typename T>
void Subject<T>::notify(const T& eventData) {
    impl_->notify(eventData);
}

template <typename T>
class ConsoleObserver : public IObserver<T>, public std::enable_shared_from_this<ConsoleObserver<T>> {
public:
    explicit ConsoleObserver(std::shared_ptr<Subject<T>> subject) : subject_(subject) {}

    void initialize() {
        subject_->attach(this->shared_from_this());
    }

    ~ConsoleObserver() {
        subject_->detach(this->shared_from_this());
    }

    void onEvent(const T& eventData) override {
        std::cout << "ConsoleObserver: Event data = " << eventData << std::endl;
    }

private:
    std::shared_ptr<Subject<T>> subject_;
};

template <>
class ConsoleObserver<CustomEvent> : public IObserver<CustomEvent>, public std::enable_shared_from_this<ConsoleObserver<CustomEvent>> {
public:
    explicit ConsoleObserver(std::shared_ptr<Subject<CustomEvent>> subject) : subject_(subject) {}

    void initialize() {
        subject_->attach(this->shared_from_this());
    }

    ~ConsoleObserver() {
        subject_->detach(this->shared_from_this());
    }

    void onEvent(const CustomEvent& eventData) override {
        std::cout << "CustomEvent: { id: " << eventData.id << ", payload: " << eventData.payload << " }" << std::endl;
    }

private:
    std::shared_ptr<Subject<CustomEvent>> subject_;
};

template <typename T>
class LoggingObserver : public IObserver<T>, public std::enable_shared_from_this<LoggingObserver<T>> {
public:
    explicit LoggingObserver(std::shared_ptr<Subject<T>> subject, const std::string& logFile)
        : subject_(subject), logFile_(logFile) {
        file_.open(logFile_, std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error("Unable to open log file");
        }
    }

    void initialize() {
        subject_->attach(this->shared_from_this());
    }

    ~LoggingObserver() {
        subject_->detach(this->shared_from_this());
    }

    void onEvent(const T& eventData) override {
        if (file_.is_open()) {
            file_ << "LoggingObserver: Event data = " << eventData << std::endl;
        }
    }

private:
    std::shared_ptr<Subject<T>> subject_;
    std::ofstream file_;
    std::string logFile_;
};

template <>
class LoggingObserver<CustomEvent> : public IObserver<CustomEvent>, public std::enable_shared_from_this<LoggingObserver<CustomEvent>> {
public:
    explicit LoggingObserver(std::shared_ptr<Subject<CustomEvent>> subject, const std::string& logFile)
        : subject_(subject), logFile_(logFile) {
        file_.open(logFile_, std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error("Unable to open log file");
        }
    }

    void initialize() {
        subject_->attach(this->shared_from_this());
    }

    ~LoggingObserver() {
        subject_->detach(this->shared_from_this());
    }

    void onEvent(const CustomEvent& eventData) override {
        if (file_.is_open()) {
            file_ << "CustomEvent: { id: " << eventData.id << ", payload: " << eventData.payload << " }" << std::endl;
        }
    }

private:
    std::shared_ptr<Subject<CustomEvent>> subject_;
    std::ofstream file_;
    std::string logFile_;
};

int main() {
    auto intSubject = std::make_shared<Subject<int>>();
    auto intObserverConsole = std::make_shared<ConsoleObserver<int>>(intSubject);
    intObserverConsole->initialize();
    auto intLoggingObserver = std::make_shared<LoggingObserver<int>>(intSubject, "log.txt");
    intLoggingObserver->initialize();
    intSubject->addData(42);

    auto stringSubject = std::make_shared<Subject<std::string>>();
    auto stringObserverConsole = std::make_shared<ConsoleObserver<std::string>>(stringSubject);
    stringObserverConsole->initialize();
    auto stringLoggingObserver = std::make_shared<LoggingObserver<std::string>>(stringSubject, "log.txt");
    stringLoggingObserver->initialize();
    stringSubject->addData("Hello, Observer!!!");

    auto customSubject = std::make_shared<Subject<CustomEvent>>();
    auto customObserverConsole = std::make_shared<ConsoleObserver<CustomEvent>>(customSubject);
    customObserverConsole->initialize();
    auto customLoggingObserver = std::make_shared<LoggingObserver<CustomEvent>>(customSubject, "log.txt");
    customLoggingObserver->initialize();
    customSubject->addData({228, "payload_data =)"});

    return 0;
}
