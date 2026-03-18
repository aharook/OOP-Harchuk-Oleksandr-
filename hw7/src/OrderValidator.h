#ifndef CORE_ORDERVALIDATOR_CPP_
#define CORE_ORDERVALIDATOR_CPP_

#include <iostream>

class IOrderValidator {
public:
    virtual ~IOrderValidator() = default;
    virtual bool IsValid(const Order& order) = 0;
};

class SimpleOrderValidator : public IOrderValidator {
public:
    bool IsValid(const Order& order) override {
        return order.getTotalAmount() > 0;
    }
};

#endif // CORE_ORDERVALIDATOR_CPP_

