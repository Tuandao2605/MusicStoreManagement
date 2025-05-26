#pragma once
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include <vector>
// #include <tree>

#include "music_item.h"

extern "C" {
#include "mysql.h"
}

using namespace std;


class MusicRepository {
public:
    // Constructor
    MusicRepository();

    ~MusicRepository();


    bool AddNewItemInDatabase(const string &category, const string &type, const string &name, const string &artist,
                              float price, int quantity);

    std::vector<MusicItem> GetAllItems();

    std::vector<MusicItem> GetAllItemsInStock();

    std::vector<MusicItem> FindMusic(const string &name, const string &category, const string &type,
                                     const string &artist);

    std::vector<MusicItem> getItemsInStock(int min_quantity);

    void EditItem(const MusicItem &music_item);

    void RemoveItem(const MusicItem &music_item);


    void SoldItems();

    bool isReset() const;

    void resetToDefault();

    bool connectToDatabase(
        const char *host,
        const char *user,
        const char *passwd,
        const char *db,
        unsigned int port
    );

    void AddItem(const MusicItem &music_item) {
        AddNewItemInDatabase(
            music_item.category,
            music_item.type,
            music_item.name,
            music_item.artist,
            music_item.price,
            music_item.quantity
        );
    }

    void UpdateItem(const MusicItem &music_item) {
        EditItem(music_item);
    }

    void RemoveItem(const string & id);

private:
    bool reset;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int qstate;
};
