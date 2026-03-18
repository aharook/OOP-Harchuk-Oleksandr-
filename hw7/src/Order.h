#ifndef ORDER_H 
#define OREDER_H

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

#endif 