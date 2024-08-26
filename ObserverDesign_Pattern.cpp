#include <iostream>
#include <vector>

// Observer interface
class Listener {
public:
    virtual void onClick() = 0;  // Method to be called when the button is clicked
};

// Subject class
class Button {
private:
    std::vector<Listener *> listeners;  // List of listeners

public:
    void addListener(Listener *listener) {
        listeners.push_back(listener);  // Add a listener to the list
    }

    void click() {
        // Notify all listeners when the button is clicked
        for (Listener *listener : listeners) {
            listener->onClick();
        }
    }
};

// Concrete Observer
class PrintListener : public Listener {
public:
    void onClick() override {
        std::cout << "Button clicked!" << std::endl;
    }
};

int main() {
    Button button;

    PrintListener printListener;
    button.addListener(&printListener);  // Add the listener to the button

    button.click();  // Simulate a button click

    return 0;
}
