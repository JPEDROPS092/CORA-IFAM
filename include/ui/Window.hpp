#pragma once

#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace ui {

class Window {
private:
    WINDOW* win;
    int height;
    int width;
    int startY;
    int startX;
    bool hasBorder;
    int colorPair;

public:
    Window(int h, int w, int y, int x, bool border = true, int color = 1)
        : height(h), width(w), startY(y), startX(x), hasBorder(border), colorPair(color) {
        win = newwin(height, width, startY, startX);
        keypad(win, TRUE);
        if (hasBorder) {
            box(win, 0, 0);
        }
    }

    ~Window() {
        delwin(win);
    }

    void refresh() {
        wrefresh(win);
    }

    void clear() {
        wclear(win);
        if (hasBorder) {
            box(win, 0, 0);
        }
    }

    void print(int y, int x, const std::string& text, bool highlight = false) {
        if (highlight) {
            wattron(win, A_REVERSE);
        }
        mvwprintw(win, y, x, text.c_str());
        if (highlight) {
            wattroff(win, A_REVERSE);
        }
    }

    void printCentered(int y, const std::string& text, bool highlight = false) {
        int x = (width - text.length()) / 2;
        print(y, x, text, highlight);
    }

    void setColor(int pair) {
        colorPair = pair;
        wattron(win, COLOR_PAIR(pair));
    }

    void resetColor() {
        wattroff(win, COLOR_PAIR(colorPair));
    }

    int getKey() {
        return wgetch(win);
    }

    std::string getInput(int y, int x, const std::string& prompt, int maxLength) {
        echo();
        print(y, x, prompt);
        char input[256];
        mvwgetnstr(win, y, x + prompt.length(), input, maxLength);
        noecho();
        return std::string(input);
    }

    int showMenu(const std::vector<std::string>& items, int startY = 1) {
        int highlight = 0;
        int choice;
        int maxWidth = 0;

        for (const auto& item : items) {
            if (item.length() > maxWidth) {
                maxWidth = item.length();
            }
        }

        while (1) {
            for (size_t i = 0; i < items.size(); i++) {
                int y = startY + i;
                int x = (width - items[i].length()) / 2;
                print(y, x, items[i], i == highlight);
            }
            refresh();

            choice = getKey();
            switch (choice) {
                case KEY_UP:
                    if (highlight > 0) highlight--;
                    break;
                case KEY_DOWN:
                    if (highlight < items.size() - 1) highlight++;
                    break;
                case 10:  // Enter key
                    return highlight;
            }
        }
    }

    void showMessage(const std::string& message, bool error = false) {
        clear();
        setColor(error ? 3 : 4);  // 3 = red (error), 4 = green (success)
        printCentered(height/2, message);
        resetColor();
        printCentered(height-2, "Pressione qualquer tecla para continuar...");
        refresh();
        getKey();
    }

    WINDOW* getWindow() { return win; }
};

class Dialog {
private:
    std::shared_ptr<Window> window;

public:
    Dialog(const std::string& title, int height = 10, int width = 40) {
        int startY = (LINES - height) / 2;
        int startX = (COLS - width) / 2;
        window = std::make_shared<Window>(height, width, startY, startX);
        window->printCentered(1, title);
        window->refresh();
    }

    bool confirm(const std::string& message) {
        window->printCentered(3, message);
        window->printCentered(5, "S - Sim    N - Não");
        window->refresh();

        while (true) {
            int ch = window->getKey();
            if (ch == 's' || ch == 'S') return true;
            if (ch == 'n' || ch == 'N') return false;
        }
    }

    std::string input(const std::string& prompt, int maxLength = 50) {
        return window->getInput(3, 2, prompt, maxLength);
    }
};

class StatusBar {
private:
    WINDOW* win;
    int width;

public:
    StatusBar() {
        width = COLS;
        win = newwin(1, width, LINES-1, 0);
    }

    ~StatusBar() {
        delwin(win);
    }

    void update(const std::string& status) {
        werase(win);
        wattron(win, A_REVERSE);
        mvwprintw(win, 0, 0, status.c_str());
        for (int i = status.length(); i < width; i++) {
            wprintw(win, " ");
        }
        wattroff(win, A_REVERSE);
        wrefresh(win);
    }
};

}
