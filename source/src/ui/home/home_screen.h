#pragma once
#include "imgui.h"
#include "../core/screen.h"

class HomeScreen final : public Screen {
private:
    VoidCallback AddNewItemInDatabase;
    VoidCallback ShowAllItems;
    VoidCallback ItemInStock;
    VoidCallback FindMusic;
    VoidCallback EditItem;
    VoidCallback RemoveItem;
    VoidCallback CreateOrder;
    VoidCallback SoldItems;

public:
    HomeScreen(
        const VoidCallback &AddNewItemInDatabase,
        const VoidCallback &ShowAllItems,
        const VoidCallback &ItemInStock,
        const VoidCallback &FindMusic,
        const VoidCallback &EditItem,
        const VoidCallback &RemoveItem,
        const VoidCallback &CreateOrder,
        const VoidCallback &SoldItems
    ): AddNewItemInDatabase(AddNewItemInDatabase),
       ShowAllItems(ShowAllItems),
       ItemInStock(ItemInStock),
       FindMusic(FindMusic),
       EditItem(EditItem),
       RemoveItem(RemoveItem),
       CreateOrder(CreateOrder),
       SoldItems(SoldItems) {
    }

    void drawMainWindows() override {
        // Center the window
        ImGui::Begin("Music Store Management System", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Inventory Management");
        ImGui::Separator();

        const float buttonWidth = ImGui::GetContentRegionAvail().x;

        if (ImGui::Button("Add New Item In Database", ImVec2(buttonWidth, 0))) {
            if (AddNewItemInDatabase) AddNewItemInDatabase();
        }

        if (ImGui::Button("Show All Items", ImVec2(buttonWidth, 0))) {
            if (ShowAllItems) ShowAllItems();
        }

        if (ImGui::Button("Item In Stock", ImVec2(buttonWidth, 0))) {
            if (ItemInStock) ItemInStock();
        }

        if (ImGui::Button("Find Music", ImVec2(buttonWidth, 0))) {
            if (FindMusic) FindMusic();
        }

        ImGui::Spacing();
        ImGui::Text("Item Operations");
        ImGui::Separator();

        if (ImGui::Button("Edit Item", ImVec2(buttonWidth, 0))) {
            if (EditItem) EditItem();
        }

        if (ImGui::Button("Remove Item", ImVec2(buttonWidth, 0))) {
            if (RemoveItem) RemoveItem();
        }

        ImGui::Spacing();
        ImGui::Text("Sales Management");
        ImGui::Separator();

        if (ImGui::Button("Create Order", ImVec2(buttonWidth, 0))) {
            if (CreateOrder) CreateOrder();
        }

        if (ImGui::Button("Sold Items", ImVec2(buttonWidth, 0))) {
            if (SoldItems) SoldItems();
        }
    }
};