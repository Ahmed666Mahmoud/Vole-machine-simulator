#include <QApplication>
#include "MainWindow.h"
#include "Machine.h"
#include "MainMenu.h"
#include <string>

int main(int argc, char *argv[])
{
    // Allow running CLI mode with "--cli" flag
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--cli") {
            Machine myMachine;
            MainMenu menu(myMachine);
            menu.run();
            return 0;
        }
    }

    // Default: Launch Qt Widgets GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
