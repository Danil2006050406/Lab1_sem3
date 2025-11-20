#include "Book.h"
#include "Loan.h"
#include "User.h"
#include "Library.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// books.txt:  Title;Author;ISBN;Year;Copies
void loadBooksFromFile(Library& lib, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "[ERROR] cannot open books file: " << filename << "\n";
        return;
    }

    std::string line;
    int lineNo = 0;

    while (std::getline(file, line)) {
        ++lineNo;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string title, author, isbn;
        int year = 0;
        int copies = 1;

        if (!std::getline(ss, title, ';') ||
            !std::getline(ss, author, ';') ||
            !std::getline(ss, isbn, ';')) {
            std::cerr << "[WARN] bad books line " << lineNo << ": " << line << "\n";
            continue;
        }

        if (!(ss >> year))   year = 0;
        if (ss.peek() == ';') ss.get();
        if (!(ss >> copies)) copies = 1;

        lib.addBook(Book(title, author, isbn, year, copies));
    }
}

// readers.txt:  Name;Id;Email
void loadReadersFromFile(Library& lib, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "[ERROR] cannot open readers file: " << filename << "\n";
        return;
    }

    std::string line;
    int lineNo = 0;

    while (std::getline(file, line)) {
        ++lineNo;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, id, email;

        if (!std::getline(ss, name, ';') ||
            !std::getline(ss, id, ';') ||
            !std::getline(ss, email, ';')) {
            std::cerr << "[WARN] bad readers line " << lineNo << ": " << line << "\n";
            continue;
        }

        lib.addReader(Reader(name, id, email));
    }
}

int main() {
    Library lib;

    // читаем з .txt
    loadBooksFromFile(lib, "books.txt");
    loadReadersFromFile(lib, "readers.txt");

    // чтобы были займы
    lib.issueBook("1234567890", "U001");
    lib.issueBook("2345678901", "U002");
    lib.issueBook("4567890123", "U003");
    lib.issueBook("1234567890", "U003");
    lib.issueBook("2345678901", "U004");
    lib.issueBook("3456789012", "U005");
    lib.returnBook("4567890123", "U003");

    // выводим всё, что нужно по лабе
    lib.listBooks();
    lib.listReaders();
    lib.listLoans();

    return 0;
}
