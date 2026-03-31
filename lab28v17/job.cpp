#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Company {
private:
    int id;
    std::string title;
    std::string address;

public:
    Company() : id(0), title(""), address("") {}
    Company(int id, const std::string& title, const std::string& address)
        : id(id), title(title), address(address) {}

    int GetId() const { return id; }
    std::string GetTitle() const { return title; }
    std::string GetAddress() const { return address; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Company, id, title, address)
};

class Job {
private:
    int id;
    std::string title;
    double salary;
    Company company;

public:
    Job() : id(0), title(""), salary(0.0), company() {}
    Job(int id, const std::string& title, double salary, const Company& company)
        : id(id), title(title), salary(salary), company(company) {}

    int GetId() const { return id; }
    std::string GetTitle() const { return title; }
    double GetSalary() const { return salary; }
    Company GetCompany() const { return company; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Job, id, title, salary, company)
};

class JobRepository {
private:
    std::vector<Job> jobs;

public:
    void Add(const Job& job) { jobs.push_back(job); }
    std::vector<Job> GetAll() const { return jobs; }

    Job GetById(int id) const {
        for (const auto& job : jobs) {
            if (job.GetId() == id) return job;
        }
        return Job(); 
    }

    void SaveToFileAsync(const std::string& filename) const {
        json root = jobs; 
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << root.dump(4);
        }
    }

    void LoadFromFileAsync(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            json root;
            inFile >> root;
            jobs = root.get<std::vector<Job>>();
        }
    }
};

int main() {
    JobRepository repo;

    repo.Add(Job(1, "C++ Developer", 2000, Company(101, "TechCorp", "Kyiv")));
    repo.Add(Job(2, "QA", 1500, Company(102, "SoftServe", "Lviv")));

    std::cout << "Saving to file...\n";
    repo.SaveToFileAsync("jobs.json");


    JobRepository newRepo;
    newRepo.LoadFromFileAsync("jobs.json");

    std::cout << "Loaded jobs:\n";
    for (const auto& job : newRepo.GetAll()) {
        std::cout << "- " << job.GetTitle() << " at " << job.GetCompany().GetTitle() << "\n";
    }
}