#pragma once
#include <string>

class Book {
private:
    std::string title, author, isbn;
    int year, totalCopies;
public:
    Book(const std::string& t, const std::string& a, const std::string& i, int y, int copies = 1);
    void displayInfo() const;
    bool matchesTitle(const std::string& q) const;
    bool checkout();
    void checkin();
    bool isOldEdition(int thresholdYear = 2000) const;
    bool isAvailable() const;
    const std::string& getISBN() const;
};

class EBook : public Book {
private:
    std::string downloadUrl;
    double fileSizeMB;
public:
    EBook(const std::string& t, const std::string& a, const std::string& i, int y,
        const std::string& url, double size);
    void getDownloadInfo() const;
};

