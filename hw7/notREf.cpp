#include <iostream>
#include <string>

class Order {
public:
    Order(int id, const std::string& customerName, double totalAmount, const std::string& status)
        : m_Id(id), m_CustomerName(customerName), m_TotalAmount(totalAmount), m_Status(status) {}

    int getId() const { return m_Id; }
    std::string getCustomerName() const { return m_CustomerName; }
    double getTotalAmount() const { return m_TotalAmount; }
    std::string getStatus() const { return m_Status; }

    void setStatus(const std::string& status) { m_Status = status; }

private:
    int m_Id;
    std::string m_CustomerName;
    double m_TotalAmount;
    std::string m_Status;
};

class IOrderValidator {
public:
    virtual ~IOrderValidator() = default;
    virtual bool IsValid(const Order& order) = 0;
};

class IOrderRepository {
public:
    virtual ~IOrderRepository() = default;
    virtual void Save(const Order& order) = 0;
    virtual Order GetById(int id) = 0;
};

class IEmailService {
public:
    virtual ~IEmailService() = default;
    virtual void SendOrderConfirmation(const Order& order) = 0;
};

class SimpleOrderValidator : public IOrderValidator {
public:
    bool IsValid(const Order& order) override {
        return order.getTotalAmount() > 0;
    }
};

class InMemoryOrderRepository : public IOrderRepository {
public:
    void Save(const Order& order) override {
        std::cout << "Order ID " << order.getId() << " saved (mock repository)." << std::endl;
    }

    Order GetById(int id) override {
        std::cout << "Getting order ID " << id << " (mock repository)." << std::endl;
        return Order(id, "Mock Customer", 0.0, "waiting");
    }
};

class ConsoleEmailService : public IEmailService {
public:
    void SendOrderConfirmation(const Order& order) override {
        std::cout << "Sending confirmation email to " << order.getCustomerName() << std::endl;
    }
};

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

int main() {
    Order myOrder(1, "John Doe", 150.0, "waiting");

    SimpleOrderValidator validator;
    InMemoryOrderRepository repository;
    ConsoleEmailService emailService;


    OrderService service(&validator, &repository, &emailService);

    service.ProcessOrder(myOrder);

    std::cout << "Final order status: " << myOrder.getStatus() << std::endl;
}
