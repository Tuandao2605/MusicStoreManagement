#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include "mysql.h"
using namespace std;


class MusicRepository {
public:
    // Constructor
    MusicRepository();

    MusicRepository(
        const char *host,
        const char *user,
        const char *passwd,
        const char *db,
        unsigned int port
    );

    // Destructor
    ~MusicRepository();


    void AddNewItemInDatabase();
    void ShowAllItems();
    void ItemInStock();
    void FindMusic();
    void EditItem();
    void RemoveItem();
    void CreateOrder();
    void SoldItems();
    bool isReset() const;
    void resetToDefault();
private:

    bool reset;
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    int qstate;
};