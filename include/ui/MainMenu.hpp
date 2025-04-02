#pragma once

#include "Window.hpp"
#include <memory>
#include <vector>
#include <string>

namespace ui {

class MainMenu {
private:
    std::shared_ptr<Window> window;
    std::shared_ptr<StatusBar> statusBar;
    std::vector<std::string> menuItems;
    int currentUser;
    bool isAdmin;

public:
    MainMenu(int height, int width, int y, int x);
    void show();
    void setUser(int userId, bool admin);
    void updateStatus(const std::string& status);

private:
    void showAdminMenu();
    void showUserMenu();
    void handleAdminChoice(int choice);
    void handleUserChoice(int choice);
    
    // Admin functions
    void manageUsers();
    void manageLockers();
    void viewReports();
    void systemSettings();
    
    // User functions
    void viewMyLocker();
    void requestLocker();
    void releaseLocker();
    void changePassword();
};

}
