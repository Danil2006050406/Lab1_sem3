#include "Book.h"
#include <iostream>
#include <algorithm>
#include <cctype>

// ===== Book =====

Book::Book(const std::string& t,
    const std::string& a,
    const std::string& i,
    int y,
    int copies)
    : title(t),
    author(a),
    isbn(i),
    year(y),
    totalCopies(copies) {
}

// --- getters ---
const std::string& Book::getTitle() const {
    return title;
}

const std::string& Book::getAuthor() const {
    return author;
}

const std::string& Book::getISBN() const {
    return isbn;
}

int Book::getYear() const {
    return year;
}

int Book::getTotalCopies() const {
    return totalCopies;
}

// --- behavior ---
void Book::displayInfo() const {
    std::cout << "Book: '" << title << "' by " << author
        << " (" << year << ") ISBN: " << isbn
        << " copies: " << totalCopies
        << " available: " << (isAvailable() ? "yes" : "no")
        << "\n";
}

double Book::getBorrowingCost() const {
    return 1.0; // базова вартість
}

bool Book::matchesTitle(const std::string& q) const {
    auto toLower = [](unsigned char c) { return std::tolower(c); };

    std::string lowTitle = title;
    std::string lowQuery = q;

    std::transform(lowTitle.begin(), lowTitle.end(), lowTitle.begin(), toLower);
    std::transform(lowQuery.begin(), lowQuery.end(), lowQuery.begin(), toLower);

    return lowTitle.find(lowQuery) != std::string::npos;
}

bool Book::checkout() {
    if (!isAvailable()) return false;
    --totalCopies;
    return true;
}

void Book::checkin() {
    ++totalCopies;
}

bool Book::isOldEdition(int thresholdYear) const {
    return year < thresholdYear;
}

bool Book::isAvailable() const {
    return totalCopies > 0;
}

// ===== EBook =====

EBook::EBook(const std::string& t,
    const std::string& a,
    const std::string& i,
    int y,
    const std::string& url,
    double size)
    : Book(t, a, i, y, 1),
    downloadUrl(url),
    fileSizeMB(size) {
}

void EBook::getDownloadInfo() const {
    std::cout << "EBook download: " << downloadUrl
        << " (" << fileSizeMB << " MB)\n";
}

void EBook::displayInfo() const {
    Book::displayInfo();
    std::cout << " [eBook " << fileSizeMB << " MB]\n";
}

double EBook::getBorrowingCost() const {
    return 0.5; // електронні книги дешевші
}

// ===== SpecialEditionEBook =====

SpecialEditionEBook::SpecialEditionEBook(const std::string& t,
    const std::string& a,
    const std::string& i,
    int y,
    const std::string& url,
    double size,
    bool bonusContent)
    : EBook(t, a, i, y, url, size),
    hasBonusContent(bonusContent) {
}

void SpecialEditionEBook::displayInfo() const {
    EBook::displayInfo();
    std::cout << " [special edition"
        << (hasBonusContent ? ", with bonus content" : "")
        << "]\n";
}

double SpecialEditionEBook::getBorrowingCost() const {
    return hasBonusContent ? 2.0 : 1.2;
}
