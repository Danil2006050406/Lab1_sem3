#include "User.h"
#include <iostream>
#include <algorithm>

User::User(const std::string& n, const std::string& i, const std::string& e)
    : name(n), id(i), email(e) {
}

void User::notify(const std::string& message) {
    std::cout << "Notify " << name << " (" << id << "): " << message << "\n";
}

const std::string& User::getId() const {
    return id;
}

// Reader

Reader::Reader(const std::string& n, const std::string& i, const std::string& e)
    : User(n, i, e) {
}

void Reader::displayInfo() const {
    std::cout << "Reader: " << name << " id=" << id
        << " email=" << email << " borrowed:" << borrowedIsbns.size() << "\n";
}

bool Reader::borrow(const std::string& isbn) {
    if (std::find(borrowedIsbns.begin(), borrowedIsbns.end(), isbn) != borrowedIsbns.end()) {
        std::cout << "Already borrowed: " << isbn << "\n";
        return false;
    }
    borrowedIsbns.push_back(isbn);
    return true;
}

bool Reader::returnBook(const std::string& isbn) {
    auto it = std::find(borrowedIsbns.begin(), borrowedIsbns.end(), isbn);
    if (it == borrowedIsbns.end()) return false;
    borrowedIsbns.erase(it);
    return true;
}

void Reader::listBorrowed() const {
    std::cout << "Borrowed by " << name << ":\n";
    for (const auto& isbn : borrowedIsbns)
        std::cout << "  - " << isbn << "\n";
}