#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <string>
#include <stdexcept>

// Інтерфейс для роботи з файлами
class IFileStorage {
public:
    virtual ~IFileStorage() = default;
    virtual std::string loadFile(const std::string& filename) = 0;
    virtual void saveFile(const std::string& filename, const std::string& content) = 0;
};

class IVirusScanner {
public:
    virtual ~IVirusScanner() = default;
    virtual bool hasVirus(const std::string& content) = 0;
};

class FileService {
private:
    IFileStorage& _storage;
    IVirusScanner& _scanner;

public:
    FileService(IFileStorage& storage, IVirusScanner& scanner);


    bool processFile(const std::string& filename);
    void uploadFile(const std::string& filename, const std::string& content);
};

#endif