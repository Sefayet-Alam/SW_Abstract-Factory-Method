#include <iostream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

// ===== Abstract Product A (Button) =====
class Button {
public:
    virtual string paint() const = 0;
    virtual ~Button() = default;
};

// ===== Abstract Product B (Checkbox) =====
class Checkbox {
public:
    virtual string paint() const = 0;
    virtual ~Checkbox() = default;
};

// ===== Concrete Product A1 (Windows Button) =====
class WinButton : public Button {
public:
    string paint() const override {
        return "Rendered a Windows Button";
    }
};

// ===== Concrete Product B1 (Windows Checkbox) =====
class WinCheckbox : public Checkbox {
public:
    string paint() const override {
        return "Rendered a Windows Checkbox";
    }
};

// ===== Concrete Product A2 (Mac Button) =====
class MacButton : public Button {
public:
    string paint() const override {
        return "Rendered a Mac Button";
    }
};

// ===== Concrete Product B2 (Mac Checkbox) =====
class MacCheckbox : public Checkbox {
public:
    string paint() const override {
        return "Rendered a Mac Checkbox";
    }
};

// ===== Abstract Factory =====
class GUIFactory {
public:
    virtual Button* createButton() const = 0;
    virtual Checkbox* createCheckbox() const = 0;
    virtual ~GUIFactory() = default;
};

// ===== Concrete Factory 1 (Windows) =====
class WinFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new WinButton();
    }

    Checkbox* createCheckbox() const override {
        return new WinCheckbox();
    }
};

// ===== Concrete Factory 2 (Mac) =====
class MacFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new MacButton();
    }

    Checkbox* createCheckbox() const override {
        return new MacCheckbox();
    }
};

// ===== Client Code (uses the abstract factory) =====
class Application {
private:
    GUIFactory* factory;

public:
    Application(GUIFactory* f) : factory(f) {}

    string renderUI() {
        Button* button = factory->createButton();
        Checkbox* checkbox = factory->createCheckbox();
        string result = button->paint() + "\n" + checkbox->paint();
        delete button;
        delete checkbox;
        return result;
    }
};

// ===== Google Tests =====
TEST(AbstractFactoryTest, WindowsUI) {
    WinFactory factory;
    Application app(&factory);
    string output = app.renderUI();
    EXPECT_EQ(output, "Rendered a Windows Button\nRendered a Windows Checkbox");
}

TEST(AbstractFactoryTest, MacUI) {
    MacFactory factory;
    Application app(&factory);
    string output = app.renderUI();
    EXPECT_EQ(output, "Rendered a Mac Button\nRendered a Mac Checkbox");
}

// Negative test (ensure Mac doesn't match Windows output)
TEST(AbstractFactoryTest, MismatchUI) {
    MacFactory factory;
    Application app(&factory);
    string output = app.renderUI();
    EXPECT_NE(output, "Rendered a Windows Button\nRendered a Windows Checkbox");
}

// Entry point for Google Test
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/*
g++ abstract_factory.cpp /home/sefayet/googletest/build/lib/libgtest.a -lpthread -I /home/sefayet/googletest/googletest/include/ -o abstract_factory_test
./abstract_factory_test
echo "# SW_Abstract-Factory-Method" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/Sefayet-Alam/SW_Abstract-Factory-Method.git
git push -u origin main
*/