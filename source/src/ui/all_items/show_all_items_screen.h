#pragma once
#include "../../music_store/music_repository.h"
#include "../core/screen.h"
#include <algorithm>

struct FilterState {
    std::string *category = nullptr;
    std::string *type = nullptr;
    std::string *name = nullptr;
    std::string *artist = nullptr;
    float *min_price = nullptr;
    float *max_price = nullptr;
    int *min_quantity = nullptr;
    int *max_quantity = nullptr;
};

struct ShowAllItemsState {
    std::vector<MusicItem> items;
    FilterState filter_state;
    std::vector<MusicItem> filtered_items;
    bool loading = true;
    std::string error_message;
    std::string success_message;
    std::string add_item_error_message;
    std::string add_item_success_message;

    std::array<char, 128> new_category = {};
    std::array<char, 128> new_type = {};
    std::array<char, 128> new_name = {};
    std::array<char, 128> new_artist = {};
    std::array<char, 128> new_price = {};
    std::array<char, 128> new_quantity = {};

    std::string editing_id;
    std::unordered_map<std::string, std::array<char, 128> > edit_category;
    std::unordered_map<std::string, std::array<char, 128> > edit_type;
    std::unordered_map<std::string, std::array<char, 128> > edit_artist;
    std::unordered_map<std::string, std::array<char, 128> > edit_name;
    std::unordered_map<std::string, std::array<char, 128> > edit_price;
    std::unordered_map<std::string, std::array<char, 128> > edit_quantity;
};

class ShowAllItemsScreen final : public Screen {
    MusicRepository *music_repository;
    ShowAllItemsState state;

    static bool IsValidFloat(const std::string &s, float &out) {
        try {
            out = std::stof(s);
            return true;
        } catch (...) {
            return false;
        }
    }

    static bool IsValidInt(const std::string &s, int &out) {
        try {
            out = std::stoi(s);
            return true;
        } catch (...) {
            return false;
        }
    }

    void reload() {
        state = ShowAllItemsState();
        state.items = music_repository->GetAllItems();
        filter_item();
    }

    static bool char_equals_ignore_case(const char a, const char b) {
        return std::tolower(static_cast<unsigned char>(a)) ==
               std::tolower(static_cast<unsigned char>(b));
    }

    static bool contains_case_insensitive(const std::string &str, const std::string &substr) {
        if (substr.empty()) return true;
        if (str.empty()) return false;

        const auto it = ranges::search(str, substr, char_equals_ignore_case).begin();

        return it != str.end();
    }

    void filter_item() {
        state.filtered_items.clear();
        state.filtered_items.reserve(state.items.size()); // Pre-allocate for performance

        for (const auto &item: state.items) {
            // Use short-circuit evaluation for better performance
            // Check most common filters first for better performance

            // Text filters
            if (state.filter_state.category &&
                !contains_case_insensitive(item.category, *state.filter_state.category))
                continue;

            if (state.filter_state.name &&
                !contains_case_insensitive(item.name, *state.filter_state.name))
                continue;

            if (state.filter_state.type &&
                !contains_case_insensitive(item.type, *state.filter_state.type))
                continue;

            if (state.filter_state.artist &&
                !contains_case_insensitive(item.artist, *state.filter_state.artist))
                continue;

            // Numeric filters
            if (state.filter_state.min_price && item.price < *state.filter_state.min_price)
                continue;

            if (state.filter_state.max_price && item.price > *state.filter_state.max_price)
                continue;

            if (state.filter_state.min_quantity && item.quantity < *state.filter_state.min_quantity)
                continue;

            if (state.filter_state.max_quantity && item.quantity > *state.filter_state.max_quantity)
                continue;

            // All filters passed, include the item
            state.filtered_items.push_back(item);
        }
    }

public:
    explicit ShowAllItemsScreen(MusicRepository *repository = nullptr)
        : music_repository(repository) {
        state = ShowAllItemsState();
    }

    void render() override;
};
