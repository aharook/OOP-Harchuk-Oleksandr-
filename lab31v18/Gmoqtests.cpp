#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileService.h"

using ::testing::Return;
using ::testing::_;


class MockFileStorage : public IFileStorage {
public:
    MOCK_METHOD(std::string, loadFile, (const std::string& filename), (override));
    MOCK_METHOD(void, saveFile, (const std::string& filename, const std::string& content), (override));
};

class MockVirusScanner : public IVirusScanner {
public:
    MOCK_METHOD(bool, hasVirus, (const std::string& content), (override));
};


class FileServiceTests : public ::testing::Test {
protected:
    MockFileStorage mockStorage;
    MockVirusScanner mockScanner;
    FileService* fileService;

    void SetUp() override {

        fileService = new FileService(mockStorage, mockScanner);
    }

    void TearDown() override {
        delete fileService;
    }
};


TEST_F(FileServiceTests, ProcessFile_CleanFile_ReturnsTrue) {
    std::string testFile = "document.txt";
    std::string fakeContent = "Safe content";


    EXPECT_CALL(mockStorage, loadFile(testFile)).WillOnce(Return(fakeContent));
    EXPECT_CALL(mockScanner, hasVirus(fakeContent)).WillOnce(Return(false));

    bool result = fileService->processFile(testFile);

    EXPECT_TRUE(result);
}


TEST_F(FileServiceTests, ProcessFile_InfectedFile_ReturnsFalse) {
    std::string testFile = "malware.exe";
    std::string badContent = "malicious code";

    EXPECT_CALL(mockStorage, loadFile(testFile)).WillOnce(Return(badContent));
    EXPECT_CALL(mockScanner, hasVirus(badContent)).WillOnce(Return(true));

    bool result = fileService->processFile(testFile);

    EXPECT_FALSE(result);
}


TEST_F(FileServiceTests, UploadFile_CleanContent_CallsSaveFile) {
    std::string testFile = "new_doc.txt";
    std::string cleanContent = "Hello world";

    EXPECT_CALL(mockScanner, hasVirus(cleanContent)).WillOnce(Return(false));
    EXPECT_CALL(mockStorage, saveFile(testFile, cleanContent)).Times(1);

    fileService->uploadFile(testFile, cleanContent);
}

TEST_F(FileServiceTests, UploadFile_InfectedContent_ThrowsException) {
    std::string testFile = "bad.exe";
    std::string badContent = "Trojan";

    EXPECT_CALL(mockScanner, hasVirus(badContent)).WillOnce(Return(true));
    EXPECT_CALL(mockStorage, saveFile(_, _)).Times(0);

    EXPECT_THROW(fileService->uploadFile(testFile, badContent), std::runtime_error);
}

TEST_F(FileServiceTests, ProcessFile_CallsLoadFileExactlyOnce) {
    std::string testFile = "test.txt";

    EXPECT_CALL(mockStorage, loadFile(testFile)).Times(1).WillOnce(Return("data"));
    EXPECT_CALL(mockScanner, hasVirus(_)).WillOnce(Return(false));

    fileService->processFile(testFile);
}

TEST_F(FileServiceTests, ProcessFile_EmptyFile_HandledCorrectly) {
    EXPECT_CALL(mockStorage, loadFile("empty.txt")).WillOnce(Return(""));
    EXPECT_CALL(mockScanner, hasVirus("")).WillOnce(Return(false));

    bool result = fileService->processFile("empty.txt");

    EXPECT_TRUE(result);
}

TEST_F(FileServiceTests, UploadFile_PassesCorrectContentToScanner) {
    std::string contentToUpload = "Important Data";

    EXPECT_CALL(mockScanner, hasVirus(contentToUpload)).Times(1).WillOnce(Return(false));
    EXPECT_CALL(mockStorage, saveFile(_, _));

    fileService->uploadFile("file.txt", contentToUpload);
}

TEST_F(FileServiceTests, ManualVerifyExample) {
    EXPECT_CALL(mockStorage, loadFile("manual.txt")).WillOnce(Return("content"));
    EXPECT_CALL(mockScanner, hasVirus("content")).WillOnce(Return(false));

    fileService->processFile("manual.txt");

    bool storageVerified = ::testing::Mock::VerifyAndClearExpectations(&mockStorage);
    bool scannerVerified = ::testing::Mock::VerifyAndClearExpectations(&mockScanner);

    EXPECT_TRUE(storageVerified);
    EXPECT_TRUE(scannerVerified);
}