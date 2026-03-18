#include <iostream>
#include "src/Order.h"
#include "src/OrderRepository.h"
#include "src/OrderValidator.h"
#include "src/EmailService.h"
#include "src/OrderService.h"

int main() {
    Order myOrder(1, "John Doe", 150.0, "waiting");

    SimpleOrderValidator validator;
    InMemoryOrderRepository repository;
    ConsoleEmailService emailService;


    OrderService service(&validator, &repository, &emailService);

    service.ProcessOrder(myOrder);

    std::cout << "Final order status: " << myOrder.getStatus() << std::endl;
}