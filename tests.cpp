#include <cassert>
#include <iostream>
#include "Book.h"
#include "Loan.h"
#include "User.h"
#include "Library.h"

void testBookAvailability() {
    Book b("1984", "Orwell", "123", 1949, 2);
    assert(b.isAvailable());
    b.checkout();
    assert(b.isAvailable());
    b.checkout();
    assert(!b.isAvailable());
    b.checkin();
    assert(b.isAvailable());
}

void testReaderBorrowReturn() {
    Reader r("Alice", "U001", "alice@example.com");
    assert(r.borrow("123"));
    assert(!r.borrow("123")); // повторне взяття
    assert(r.returnBook("123"));
    assert(!r.returnBook("123")); // повторне повернення
}

void testLoanStatus() {
    time_t now = time(nullptr);
    Loan l("L001", "123", "U001", now, now + 3 * 24 * 60 * 60);
    assert(!l.isReturned());
    l.markReturned();
    assert(l.isReturned());
}

void testLoanDaysLeft() {
    time_t now = time(nullptr);
    Loan l("L002", "123", "U001", now, now + 2 * 24 * 60 * 60);
    assert(l.daysLeft() >= 1 && l.daysLeft() <= 2);
}

void testLoanOverdue() {
    time_t now = time(nullptr);
    Loan l("L003", "123", "U001", now - 10 * 24 * 60 * 60, now - 5 * 24 * 60 * 60);
    assert(l.isOverdue());
}

void testLibraryAddFindBook() {
    Library lib;
    lib.addBook(Book("1984", "Orwell", "123", 1949, 1));
    assert(lib.findBookByISBN("123") != nullptr);
    assert(lib.findBookByISBN("999") == nullptr);
}

void testLibraryAddFindReader() {
    Library lib;
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    assert(lib.findReaderById("U001") != nullptr);
    assert(lib.findReaderById("U999") == nullptr);
}

void testLibraryIssueBookSuccess() {
    Library lib;
    lib.addBook(Book("1984", "Orwell", "123", 1949, 1));
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    assert(lib.issueBook("123", "U001"));
}

void testLibraryIssueBookUnavailable() {
    Library lib;
    Book b("1984", "Orwell", "123", 1949, 0);
    lib.addBook(b);
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    assert(!lib.issueBook("123", "U001"));
}

void testLibraryIssueBookDuplicate() {
    Library lib;
    lib.addBook(Book("1984", "Orwell", "123", 1949, 2));
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    assert(lib.issueBook("123", "U001"));
    assert(!lib.issueBook("123", "U001")); // повторне взяття
}

void testLibraryReturnBookSuccess() {
    Library lib;
    lib.addBook(Book("1984", "Orwell", "123", 1949, 1));
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    lib.issueBook("123", "U001");
    assert(lib.returnBook("123", "U001"));
}

void testLibraryReturnBookNotBorrowed() {
    Library lib;
    lib.addBook(Book("1984", "Orwell", "123", 1949, 1));
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    assert(!lib.returnBook("123", "U001"));
}

void testLibraryReturnBookWrongUser() {
    Library lib;
    lib.addBook(Book("1984", "Orwell", "123", 1949, 1));
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    lib.addReader(Reader("Bob", "U002", "bob@example.com"));
    lib.issueBook("123", "U001");
    assert(!lib.returnBook("123", "U002"));
}

void testReaderListBorrowed() {
    Reader r("Alice", "U001", "alice@example.com");
    r.borrow("123");
    r.borrow("456");
    r.listBorrowed(); // просто вивід
}

void testUserNotify() {
    Reader r("Alice", "U001", "alice@example.com");
    r.notify("Your book is overdue.");
}

void testPolymorphicDisplay() {
    User* u1 = new Reader("Alice", "U001", "alice@example.com");
    u1->displayInfo(); // викликає Reader::displayInfo()
    delete u1;
}

void testMultipleLoans() {
    Library lib;
    lib.addBook(Book("Book1", "Author", "111", 2000, 2));
    lib.addReader(Reader("Alice", "U001", "alice@example.com"));
    assert(lib.issueBook("111", "U001"));
    assert(lib.returnBook("111", "U001"));
    assert(lib.issueBook("111", "U001")); // повторна видача після повернення
}

void testBookCheckinCheckoutBalance() {
    Book b("Test", "Author", "999", 2020, 1);
    assert(b.isAvailable());
    b.checkout();
    assert(!b.isAvailable());
    b.checkin();
    assert(b.isAvailable());
}

void testLoanGetters() {
    Loan l("L001", "123", "U001", time(nullptr), time(nullptr) + 1000);
    assert(l.getLoanId() == "L001");
    assert(l.getISBN() == "123");
    assert(l.getUserId() == "U001");
}
void testPolymorphismBookHierarchy() {
    Book* b1 = new Book("Paper book", "Author A", "P1", 2000, 1);
    Book* b2 = new EBook("Electronic book", "Author B", "E1", 2010,
        "http://example.com/ebook", 1.5);
    Book* b3 = new SpecialEditionEBook("Special edition", "Author C", "S1", 2020,
        "http://example.com/special", 2.0, true);

    Book* items[3] = { b1, b2, b3 };

    for (Book* b : items) {
        // Поліморфний виклик: викликається реалізація відповідно до реального типу
        b->displayInfo();
        double cost = b->getBorrowingCost();
        assert(cost > 0.0);
    }

    delete b1;
    delete b2;
    delete b3;
}
