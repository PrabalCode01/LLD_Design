#include <iostream>
using namespace std;

// Abstract Product A
class Button {
public:
    virtual void render() const = 0;
    virtual ~Button() {}
};

// Abstract Product B
class Checkbox {
public:
    virtual void render() const = 0;
    virtual ~Checkbox() {}
};

// Concrete Product A1
class WindowsButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering Windows Button" << std::endl;
    }
};

// Concrete Product B1
class WindowsCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering Windows Checkbox" << std::endl;
    }
};
// Concrete Product A2
class MacButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering Mac Button" << std::endl;
    }
};

// Concrete Product B2
class MacCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering Mac Checkbox" << std::endl;
    }
};
// Abstract Factory
class GUIFactory {
public:
    virtual Button* createButton() const = 0;
    virtual Checkbox* createCheckbox() const = 0;
    virtual ~GUIFactory() {}
};
// Concrete Factory 1
class WindowsFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new WindowsButton();
    }

    Checkbox* createCheckbox() const override {
        return new WindowsCheckbox();
    }
};

// Concrete Factory 2
class MacFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new MacButton();
    }

    Checkbox* createCheckbox() const override {
        return new MacCheckbox();
    }
};
void renderUI(const GUIFactory& factory) {
    Button* button = factory.createButton();
    Checkbox* checkbox = factory.createCheckbox();

    button->render();
    checkbox->render();

    delete button;
    delete checkbox;
}

int main() {
    // Choose the appropriate factory based on some condition
    GUIFactory* factory = nullptr;

    #if defined(_WIN32) || defined(_WIN64)
    factory = new WindowsFactory();
    #else
    factory = new MacFactory();
    #endif

    if (factory) {
        renderUI(*factory);
        delete factory;
    }

    return 0;
}
