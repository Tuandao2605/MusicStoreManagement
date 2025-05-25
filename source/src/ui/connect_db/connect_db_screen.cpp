#include "connect_db_screen.h"
#include "imgui.h"
#include <iostream>

void ConnectDbScreen::render() {
    static char hostBuffer[128] = "127.0.0.1";
    static char userBuffer[128] = "root";
    static char passwdBuffer[128] = "root";
    static char dbBuffer[128] = "test_db";

    ImGui::Begin("Connect to Database");

    ImGui::InputText("Host", hostBuffer, sizeof(hostBuffer));
    ImGui::InputText("User", userBuffer, sizeof(userBuffer));
    ImGui::InputText("Password", passwdBuffer, sizeof(passwdBuffer), ImGuiInputTextFlags_Password);
    ImGui::InputText("Database", dbBuffer, sizeof(dbBuffer));

    if (ImGui::Button("Connect")) {
        // Attempt to connect to the database
        std::cout << "Connecting to DB with the following details:" << std::endl;
        std::cout << "Host: " << hostBuffer << std::endl;
        std::cout << "User: " << userBuffer << std::endl;
        std::cout << "Password: " << passwdBuffer << std::endl;
        std::cout << "Database: " << dbBuffer << std::endl;

        // Here you can add logic to initialize the database connection
        // using the provided details.
    }

    ImGui::End();
}