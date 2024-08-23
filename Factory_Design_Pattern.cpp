#include <iostream>
#include <memory>
using namespace std;

// Base Product
class Document {
public:
    virtual void print() = 0; // Pure virtual function
    virtual ~Document() {}
};

// Concrete Products
class WordDocument : public Document {
public:
    void print() override {
        std::cout << "This is a Word document." << std::endl;
    }
};

class PDFDocument : public Document {
public:
    void print() override {
        std::cout << "This is a PDF document." << std::endl;
    }
};

class ExcelDocument : public Document {
public:
    void print() override {
        std::cout << "This is an Excel document." << std::endl;
    }
};

// Factory
class DocumentFactory {
public:
    unique_ptr<Document> createDocument(const string &type) {
        if (type == "word") {
            return make_unique<WordDocument>();
        } else if (type == "pdf") {
            return make_unique<PDFDocument>();
        } else if (type == "excel") {
            return make_unique<ExcelDocument>();
        } else {
            return nullptr;
        }
    }
};

int main() {
    DocumentFactory factory;

    auto doc1 = factory.createDocument("word");
    if (doc1) doc1->print();

    auto doc2 = factory.createDocument("pdf");
    if (doc2) doc2->print();

    return 0;
}
