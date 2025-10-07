#include "LibraryUtils.h"
#include <iostream>

bool issueBookToReader(Book& book, Reader& reader) {
    if (!book.isAvailable()) {
        std::cout << " нига недоступна дл€ выдачи.\n";
        return false;
    }

    if (!reader.borrow(book.getISBN())) {
        std::cout << "„итатель уже вз€л эту книгу.\n";
        return false;
    }

    book.checkout();
    std::cout << " нига успешно выдана.\n";
    return true;
}