#pragma once
#include <string>

// ===== Base class Book =====
class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    int year;
    int totalCopies;

public:
    Book(const std::string& t,
        const std::string& a,
        const std::string& i,
        int y,
        int copies = 1);
    virtual ~Book() = default;

    // --- GETTERS (потрібні бібліотеці та для виводу) ---
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getISBN()   const;
    int  getYear()        const;
    int  getTotalCopies() const;

    // --- Поліморфні методи ---
    virtual void   displayInfo() const;
    virtual double getBorrowingCost() const;

    // --- Інші методи ---
    bool matchesTitle(const std::string& q) const;
    bool checkout();
    void checkin();
    bool isOldEdition(int thresholdYear = 2000) const;
    bool isAvailable() const;
};

// ===== 2-й рівень: EBook =====
class EBook : public Book {
private:
    std::string downloadUrl;
    double fileSizeMB;

public:
    EBook(const std::string& t,
        const std::string& a,
        const std::string& i,
        int y,
        const std::string& url,
        double size);

    void getDownloadInfo() const;

    void   displayInfo() const override;
    double getBorrowingCost() const override;
};

// ===== 3-й рівень: SpecialEditionEBook =====
class SpecialEditionEBook : public EBook {
private:
    bool hasBonusContent;

public:
    SpecialEditionEBook(const std::string& t,
        const std::string& a,
        const std::string& i,
        int y,
        const std::string& url,
        double size,
        bool bonusContent);

    void   displayInfo() const override;
    double getBorrowingCost() const override;
};
