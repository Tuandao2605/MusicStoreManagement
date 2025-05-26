#include "connect_db_screen.h"
#include "imgui.h"
#include <iostream>

void ConnectDbScreen::drawMainWindows() {
    static char hostBuffer[128] = "127.0.0.1";
    static char userBuffer[128] = "root";
    static char passwdBuffer[128] = "root";
    static char dbBuffer[128] = "test_db";
    static char portBuffer[10] = "3306";

    ImGui::Begin("Connect to Database");

    ImGui::InputText("Host", hostBuffer, sizeof(hostBuffer));
    ImGui::InputText("User", userBuffer, sizeof(userBuffer));
    ImGui::InputText("Password", passwdBuffer, sizeof(passwdBuffer), ImGuiInputTextFlags_Password);
    ImGui::InputText("Database", dbBuffer, sizeof(dbBuffer));

    if (ImGui::Button("Connect")) {
        // Attempt to connect to the database
        const int port = std::atoi(portBuffer);
        bool isConnectSuccessful = music_repository->connectToDatabase(
            hostBuffer,
            userBuffer,
            passwdBuffer,
            dbBuffer,
            port
        );

        if (isConnectSuccessful) {
            onConnectDbSuccess();
        }

        // Here you can add logic to initialize the database connection
        // using the provided details.
    }
}
