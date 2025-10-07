#include "Library.h"
#include <iostream>
#include <ctime>

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::addReader(const Reader& reader) {
    readers.push_back(reader);
}

Book* Library::findBookByISBN(const std::string& isbn) {
    for (auto& book : books)
        if (book.getISBN() == isbn)
            return &book;
    return nullptr;
}

Reader* Library::findReaderById(const std::string& id) {
    for (auto& reader : readers)
        if (reader.getId() == id)
            return &reader;
    return nullptr;
}

bool Library::issueBook(const std::string& isbn, const std::string& readerId) {
    Book* book = findBookByISBN(isbn);
    Reader* reader = findReaderById(readerId);

    if (!book || !reader) {
        std::cout << "Book or reader not found.\n";
        return false;
    }

    if (!book->isAvailable()) {
        std::cout << "Book is not available.\n";
        return false;
    }

    if (!reader->borrow(isbn)) {
        std::cout << "Reader has already borrowed this book.\n";
        return false;
    }

    book->checkout();
    std::string loanId = "L" + std::to_string(loans.size() + 1);
    time_t now = time(nullptr);
    loans.emplace_back(loanId, isbn, readerId, now, now + 7 * 24 * 60 * 60);
    std::cout << "Book successfully issued.\n";
    return true;
}

bool Library::returnBook(const std::string& isbn, const std::string& readerId) {
    Book* book = findBookByISBN(isbn);
    Reader* reader = findReaderById(readerId);

    if (!book || !reader) {
        std::cout << "Book or reader not found.\n";
        return false;
    }

    if (!reader->returnBook(isbn)) {
        std::cout << "Reader does not have this book.\n";
        return false;
    }

    book->checkin();

    for (auto& loan : loans) {
        if (loan.getISBN() == isbn && loan.getUserId() == readerId && !loan.isReturned()) {
            loan.markReturned();
            break;
        }
    }

    std::cout << "Book successfully returned.\n";
    return true;
}

void Library::listBooks() const {
    std::cout << "Book list:\n";
    for (const auto& book : books)
        book.displayInfo();
}

void Library::listReaders() const {
    std::cout << "Reader list:\n";
    for (const auto& reader : readers)
        reader.displayInfo();
}

void Library::listLoans() const {
    std::cout << "Loan list:\n";
    for (const auto& loan : loans) {
        std::cout << "Loan " << loan.getLoanId()
            << " | ISBN: " << loan.getISBN()
            << " | Reader: " << loan.getUserId()
            << " | Returned: " << (loan.isReturned() ? "Yes" : "No")
            << "\n";
    }
}