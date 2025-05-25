#include "music_repository.h"

MusicRepository::MusicRepository() {
    // create connection
    reset = false;
    conn = mysql_init(0);
    if (conn) {
        cout << "Database Connected" << endl;
        cout << "Press any key to continue..." << endl;
    } else
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "root", "test", 3306, NULL, 0);
    if (conn) {
        cout << "Database Connected To MySql" << conn << endl;
        cout << "Press any key to continue..." << endl;
    } else
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
}

MusicRepository::MusicRepository(const char *host, const char *user, const char *passwd, const char *db,
                                 unsigned int port) {
    reset = false;
    conn = mysql_init(0);
    if (conn) {
        cout << "Database Connected" << endl;
        cout << "Press any key to continue..." << endl;
    } else
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    conn = mysql_real_connect(conn, host, user, passwd, db, port, NULL, 0);
    if (conn) {
        cout << "Database Connected To MySql" << conn << endl;
        cout << "Press any key to continue..." << endl;
    } else
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
}

MusicRepository::~MusicRepository() {
    // Close connection
    mysql_close(conn);
    cout << "Database Disconnected" << endl;
    cout << "Press any key to continue..." << endl;
}

bool MusicRepository::AddNewItemInDatabase(const string &category, const string &type, const string &name,
                                           const string &artist, const float price, const int quantity) {
    const string insert_query =
            "insert into musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) values ('" + category
            + "','" + type + "','" + name + "','" + artist + "','" + to_string(price) + "','" + to_string(quantity) +
            "')";

    const char *q = insert_query.c_str();

    qstate = mysql_query(conn, q);

    if (!qstate) {
        return true;
    }
    return false;
}

std::vector<MusicItem> MusicRepository::GetAllItems() {
    std::vector<MusicItem> items;
    qstate = mysql_query(conn, "select * from musicinfo_tb");
    if (!qstate) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) {
            MusicItem item;
            item.id = atoi(row[0]);
            item.category = row[1];
            item.type = row[2];
            item.name = row[3];
            item.artist = row[4];
            item.price = atof(row[5]);
            item.quantity = atoi(row[6]);
            items.push_back(item);
        }
    }
    return items;
}

void MusicRepository::ItemInStock() {
    char choose;

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Items In Stock Menu" << endl << endl;

    qstate = mysql_query(conn, "select m_name, m_artist, m_price, m_quantity from musicinfo_tb");
    if (!qstate) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) {
            if (atoi(row[3]) > 0) {
                cout << "Name: " << row[0] << "\nArtist: " << row[1] << "\nPrice: " << row[2] << "\nQuantity: " << row[
                    3] << endl << endl;
            }
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        reset = true;
    } else {
        exit(0);
    }
}

std::vector<MusicItem> MusicRepository::FindMusic(const string &name, const string &category, const string &type,
                                                  const string &artist) {
    const std::vector<MusicItem> items = GetAllItems();
    std::vector<MusicItem> foundItems;
    for (const auto &item: items) {
        if ((!name.empty() && item.name.find(name) != string::npos) ||
            (!category.empty() && item.category.find(category) != string::npos) ||
            (!type.empty() && item.type.find(type) != string::npos) ||
            (!artist.empty() && item.artist.find(artist) != string::npos)) {
            foundItems.push_back(item);
        }
    }
    return foundItems;
}

void MusicRepository::EditItem() {
    // Variables
    string category = "";
    string type = "";
    string name = "";
    string artist = "";
    string items[5000];
    string price = "";
    string quantity = "";
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storecategory = "";
    string storetype = "";
    string storename = "";
    string storeartist = "";
    string storeprice = "";
    string storequantity = "";
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Edit Item Menu" << endl << endl;

    qstate = mysql_query(conn, "select m_id, m_name from musicinfo_tb");
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << "ID\tName\n" << endl;
        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << "\t" << row[1] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    } catch (exception e) {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false) {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++) {
            if (strid != items[i]) {
                NotInDatabase = true;
            } else {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false) {
            string findbyid_query = "select * from musicinfo_tb where m_id = '" + strid + "'";
            const char *qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate) {
                res = mysql_store_result(conn);
                cout << endl;
                while ((row = mysql_fetch_row(res))) {
                    cout << "ID: " << row[0] << "\nCategory: " << row[1] << "\nType: " << row[2] << "\nName: " << row[3]
                            << "\nArtist: " << row[4] << "\nPrice: " << row[5] << "\nQuantity: " << row[6] << endl <<
                            endl;
                    storeid = row[0];
                    storecategory = row[1];
                    storetype = row[2];
                    storename = row[3];
                    storeartist = row[4];
                    storeprice = row[5];
                    storequantity = row[6];
                }
            } else {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            cout << "Enter Category (xN to not change): ";
            getline(cin, category);
            if (category == "xN") {
                category = storecategory;
            }
            cout << "Enter Type (xN to not change): ";
            getline(cin, type);
            if (type == "xN") {
                type = storetype;
            }
            cout << "Enter Name (xN to not change): ";
            getline(cin, name);
            if (name == "xN") {
                name = storename;
            }
            cout << "Enter Artist (xN to not change): ";
            getline(cin, artist);
            if (artist == "xN") {
                artist = storeartist;
            }
            cout << "Enter Price (xN to not change): ";
            cin >> price;
            if (price == "xN") {
                category = storecategory;
            }
            cout << "Enter Quantity (xN to not change): ";
            cin >> quantity;
            if (quantity == "xN") {
                quantity = storequantity;
            }

            string update_query = "update musicinfo_tb set m_category = '" + category + "', m_type = '" + type +
                                  "', m_name = '" + name + "', m_artist = '" + artist + "', m_price = '" + price +
                                  "', m_quantity = '" + quantity + "' where m_id = '" + strid + "'";
            const char *qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate) {
                cout << endl << "Successfully Saved In Database." << endl;
            } else {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
        } else {
            cout << "Item Not Found in database." << endl;
        }
    }

ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        reset = true;
    } else if (choose == 'e' || choose == 'E') {
        EditItem();
    } else {
        exit(0);
    }
}

void MusicRepository::RemoveItem() {
    // Variables
    char choose;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Remove Item Menu" << endl << endl;

    qstate = mysql_query(conn, "select m_id, m_name from musicinfo_tb");
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << "ID\tName\n" << endl;
        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << "\t" << row[1] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    } catch (exception e) {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false) {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++) {
            if (strid != items[i]) {
                NotInDatabase = true;
            } else {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false) {
            string delete_query = "delete from musicinfo_tb where m_id = '" + strid + "'";
            const char *qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate) {
                cout << "Successfully Deleted From Database." << endl;
            } else {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }
        } else {
            cout << "Item Not Found in database." << endl;
        }
    }

    // Exit Code
ExitMenu:
    cout << "Press 'm' to Menu, 'd' to delete another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        reset = true;
    } else if (choose == 'd' || choose == 'D') {
        EditItem();
    } else {
        exit(0);
    }
}

void MusicRepository::CreateOrder() {
    // Variables
    char choose;
    string getId = "";
    string itemId[5000];
    string itemName[5000];
    char chooseEditOrBuy;
    int itemIndex = 0;
    float totalPrice = 0.0;
    bool purchase, itemFalse = false;

    string storeId[5000];
    string storeName[5000];
    string storeCategory[5000];
    string storeType[5000];
    string storeArtist[5000];
    string storePrice[5000];
    string storeQuantity[5000];
    int storeIndex = 0, storeIndexN = 0;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Show All Items Menu" << endl << endl;

    qstate = mysql_query(conn, "select * from musicinfo_tb");
    if (!qstate) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) {
            if (atoi(row[6]) > 0) {
                cout << "ID: " << row[0] << "\nCategory: " << row[1] << "\nType: " << row[2] << "\nName: " << row[3] <<
                        "\nArtist: " << row[4] << "\nPrice: " << row[5] << endl << endl;
                storeId[storeIndex] = row[0];
                storeCategory[storeIndex] = row[1];
                storeType[storeIndex] = row[2];
                storeName[storeIndex] = row[3];
                storeArtist[storeIndex] = row[4];
                storePrice[storeIndex] = row[5];
                storeQuantity[storeIndex] = row[6];
                storeIndex++;
            }
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    for (itemIndex = 0;; itemIndex++) {
        cout << "Enter a Music ID's (q to exit): ";
        cin >> getId;
        if (getId == "q") {
            break;
        } else {
            for (int i = 0; i < storeIndex; i++) {
                if (getId == storeId[i]) {
                    itemId[itemIndex] = getId;
                    itemFalse = false;
                    break;
                } else {
                    itemFalse = true;
                }
            }
            if (itemFalse == true) {
                cout << "Enter a valid number." << endl;
                itemIndex--;
                itemFalse = false;
            }
        }
    }

    cout << "You choose this song id's: ";
    for (int i = 0; i < itemIndex; i++) {
        cout << itemId[i] << " ";
    }

CHOOSEEDITORBUY:
    cout << endl << "Do you want to edit items(e) or buy this items(b): ";
    cin >> chooseEditOrBuy;

    if (chooseEditOrBuy == 'e') {
        for (int i = 0;; i++) {
            cout << "Remove item id's (q to exit): ";
            cin >> getId;
            if (getId == "q") {
                break;
            } else {
                for (int j = 0; j < itemIndex; j++) {
                    if (itemId[j] == getId) {
                        for (int k = j; k < itemIndex; k++) {
                            itemId[k] = itemId[k + 1];
                        }
                        itemId[itemIndex--] = "\0";
                    }
                }
            }
        }

        cout << "You choose this song id's: ";
        for (int i = 0; i < itemIndex; i++) {
            cout << itemId[i] << " ";
        }

        goto CHOOSEEDITORBUY;
    } else if (chooseEditOrBuy == 'b') {
        for (int i = 0; i < itemIndex; i++) {
            for (int j = 0; j < storeIndex; j++) {
                if (itemId[i] == storeId[j]) {
                    qstate = mysql_query(conn, "select m_quantity from musicinfo_tb");
                    if (!qstate) {
                        res = mysql_store_result(conn);
                        while ((row = mysql_fetch_row(res))) {
                            if (atoi(row[0]) > 0) {
                                storeQuantity[storeIndexN] = row[0];
                                storeIndexN++;
                            }
                        }
                        storeIndexN = 0;
                    } else {
                        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                    }

                    totalPrice += strtof((storePrice[j]).c_str(), 0);

                    float quan1 = strtof((storeQuantity[j]).c_str(), 0);
                    quan1 -= 1;
                    float quan2 = strtof((storeQuantity[j]).c_str(), 0);
                    float quan = quan2 - quan1;
                    string getResult;
                    stringstream strquan;
                    strquan << quan;
                    strquan >> getResult;

                    string getQuan1;
                    stringstream strquan1;
                    strquan1 << quan1;
                    strquan1 >> getQuan1;

                    string insert_query =
                            "insert into solditem_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) values ('"
                            + storeCategory[j] + "','" + storeType[j] + "','" + storeName[j] + "','" + storeArtist[j] +
                            "','" + storePrice[j] + "','" + getResult + "')";
                    purchase = true;

                    //cout << insert_query << endl;


                    const char *q = insert_query.c_str(); // c_str converts string to constant char and this is required

                    qstate = mysql_query(conn, q);

                    if (!qstate) {
                        purchase = true;
                    } else {
                        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                    }


                    string update_query = "update musicinfo_tb set m_quantity = '" + getQuan1 + "' where m_id = '" +
                                          storeId[j] + "'";
                    const char *qu = update_query.c_str();
                    //cout << update_query << endl;

                    qstate = mysql_query(conn, qu);

                    if (qstate) {
                        cout << "Failed To Update!" << mysql_errno(conn) << endl;
                    }
                }
            }
        }

        if (purchase == true) {
            cout << endl << "Purchase Successfully Done." << endl;
            cout << endl << "Total Price: " << totalPrice << endl;
        }
    }

    // Exit Code
    cout << endl << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        reset = true;
    } else {
        exit(0);
    }
}

void MusicRepository::SoldItems() {
    // Variables
    char choose;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Sold Items Menu" << endl << endl;

    qstate = mysql_query(
        conn, "select m_name, m_artist, m_category, m_type, m_price, sum(m_quantity) from solditem_tb group by m_name");
    if (!qstate) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) {
            cout << "Name: " << row[0] << "\nArtist: " << row[1] << "\nCategory: " << row[2] << "\nType: " << row[3] <<
                    "\nPrice: " << row[4] << "\nQuantity: " << row[5] << endl << endl;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        reset = true;
    } else {
        exit(0);
    }
}

bool MusicRepository::isReset() const {
    return reset;
}

void MusicRepository::resetToDefault() {
    reset = false;
    cout << "Welcome To Music Store" << endl << endl;
    cout << "Press any key to continue..." << endl;
}

bool MusicRepository::connectToDatabase(const char *host, const char *user, const char *passwd, const char *db,
                                        unsigned int port) {
    reset = false;
    conn = mysql_init(0);
    if (conn) {
        cout << "Database Connected" << endl;
        cout << "Press any key to continue..." << endl;
    } else
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    conn = mysql_real_connect(conn, host, user, passwd, db, port, NULL, 0);
    if (conn) {
        cout << "Database Connected To MySql" << conn << endl;
        cout << "Press any key to continue..." << endl;
        return true;
    }
    cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    return false;
}
