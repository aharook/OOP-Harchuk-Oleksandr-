#ifndef CORE_ORDERSERVICE_CPP_
#define CORE_ORDERSERVICE_CPP_

#include <iostream>
#include "OrderRepository.h"
#include "OrderValidator.h"
#include "EmailService.h"

class OrderService {
public:

    OrderService(IOrderValidator* validator, IOrderRepository* repository, IEmailService* emailService)
        : m_Validator(validator), m_Repository(repository), m_EmailService(emailService) {}

    void ProcessOrder(Order& order) {
        std::cout << "Processing order ID " << order.getId() << "..." << std::endl;

        if (m_Validator->IsValid(order)) {
            order.setStatus("Processed");
            m_Repository->Save(order);
            m_EmailService->SendOrderConfirmation(order);

            std::cout << "Order processed successfully." << std::endl;
        } else {
            order.setStatus("Failed");
            std::cout << "Order processing failed: Total amount must be greater than 0." << std::endl;
        }
    }

private:
    IOrderValidator* m_Validator;
    IOrderRepository* m_Repository;
    IEmailService* m_EmailService;
};



#endif // CORE_ORDERSERVICE_CPP_

