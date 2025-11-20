#pragma once
#include <string>
#include <vector>

class User {
protected:
    std::string name, id, email;
public:
    User(const std::string& n, const std::string& i, const std::string& e);
    virtual ~User() = default;
    virtual void displayInfo() const = 0;
    virtual void notify(const std::string& message);
    const std::string& getId() const;
};

class Reader : public User {
private:
    std::vector<std::string> borrowedIsbns;
public:
    Reader(const std::string& n, const std::string& i, const std::string& e);
    void displayInfo() const override;
    bool borrow(const std::string& isbn);
    bool returnBook(const std::string& isbn);
    void listBorrowed() const;
};