#ifndef ORDERREPOSITORY_H
#define ORDERREPOSITORY_H


#include <iostream>

class IOrderRepository {
public:
    virtual ~IOrderRepository() = default;
    virtual void Save(const Order& order) = 0;
    virtual Order GetById(int id) = 0;
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

#endif