#include "FileService.h"

FileService::FileService(IFileStorage& storage, IVirusScanner& scanner) 
    : _storage(storage), _scanner(scanner) {}

bool FileService::processFile(const std::string& filename) {
    std::string content = _storage.loadFile(filename);
    
    if (_scanner.hasVirus(content)) {
        return false; 
    }
    return true; 
}

void FileService::uploadFile(const std::string& filename, const std::string& content) {
    if (_scanner.hasVirus(content)) {
        throw std::runtime_error("Virus detected! Upload aborted.");
    }
    _storage.saveFile(filename, content);
}