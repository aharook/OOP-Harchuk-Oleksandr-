#ifndef CORE_EMAILSERVICE_CPP_
#define CORE_EMAILSERVICE_CPP_

#include <iostream>

class IEmailService {
public:
    virtual ~IEmailService() = default;
    virtual void SendOrderConfirmation(const Order& order) = 0;
};

class ConsoleEmailService : public IEmailService {
public:
    void SendOrderConfirmation(const Order& order) override {
        std::cout << "Sending confirmation email to " << order.getCustomerName() << std::endl;
    }
};

#endif // CORE_EMAILSERVICE_CPP_

