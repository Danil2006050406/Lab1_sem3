#include "Book.h"
#include "Loan.h"
#include "User.h"
#include <iostream>
#include "Library.h"
#include <fstream>
#include <sstream>

void loadBooksFromFile(Library& lib, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string title, author, isbn;
        int year, copies;
        getline(ss, title, ';');
        getline(ss, author, ';');
        getline(ss, isbn, ';');
        ss >> year;
        ss.ignore(); // skip delimiter
        ss >> copies;
        lib.addBook(Book(title, author, isbn, year, copies));
    }
}

void loadReadersFromFile(Library& lib, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, id, email;
        getline(ss, name, ';');
        getline(ss, id, ';');
        getline(ss, email, ';');
        lib.addReader(Reader(name, id, email));
    }
}

int main() {
    Library lib;

    loadBooksFromFile(lib, "books.txt");
    loadReadersFromFile(lib, "readers.txt");

    lib.issueBook("1234567890", "U001"); 
    lib.issueBook("2345678901", "U002"); 
    lib.issueBook("4567890123", "U003");
    lib.issueBook("1234567890", "U003");
    lib.issueBook("2345678901", "U004");
    lib.issueBook("3456789012", "U005");
    lib.returnBook("4567890123", "U003");
    lib.listBooks();
    lib.listReaders();
    lib.listLoans();


    return 0;
}

//int main() {
//    Book b("The Lord of the Rings", "J. R. R. Tolkien", "1", 1954, 4);
//    b.displayInfo();
//
//    Reader r("Danilo", "U001", "danjadanjasakhno@gmail.com");
//    r.displayInfo();
//    r.borrow("1");
//    r.listBorrowed();
//
//    Loan l("L001", "1234567890", "U001", time(nullptr), time(nullptr) + 8 * 24 * 60 * 60);
//    std::cout << "Loan days left: " << l.daysLeft() << "\n";
//    
//    return 0;
//}