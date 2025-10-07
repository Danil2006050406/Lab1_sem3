#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
#include "Loan.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<Reader> readers;
    std::vector<Loan> loans;

public:
    void addBook(const Book& book);
    void addReader(const Reader& reader);

    Book* findBookByISBN(const std::string& isbn);
    Reader* findReaderById(const std::string& id);

    bool issueBook(const std::string& isbn, const std::string& readerId);
    bool returnBook(const std::string& isbn, const std::string& readerId);

    void listBooks() const;
    void listReaders() const;
    void listLoans() const;
};