// Music Store Manangement System in C++ Design and Developed by CodeWithC.com

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include "mysql.h"

#include "music_repository.h"
using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 6)
    {
        cout << "Usage: " << argv[0] << " <host> <user> <password> <database> <port>" << endl;
        return 1;
    }
    const char *host = argv[1];
    const char *user = argv[2];
    const char *password = argv[3];
    const char *database = argv[4];
    unsigned int port = atoi(argv[5]);
    cout << "Host: " << host << endl;
    cout << "User: " << user << endl;
    cout << "Password: " << (password ? password : "null") << endl;
    cout << "Database: " << database << endl;
    cout << "Port: " << port << endl;
    cout << "------------------------" << endl;

    // MusicRepository *musicRepository = new MusicRepository();
    MusicRepository *musicRepository = new MusicRepository(host, user, password, database, port);

reset:
    musicRepository->resetToDefault();

    int chooseOneFromMenu = 0;
    char exitSurity;
    // Variables End

    cout << "Welcome To Music Store" << endl;
    cout << "Music Store Menu" << endl;
    cout << "1. Create Order." << endl;
    cout << "2. Find Music." << endl;
    cout << "3. Sold Items." << endl;
    cout << "4. Item in Stock." << endl;
    cout << "5. All Items." << endl;
    cout << "6. Add New Item." << endl;
    cout << "7. Edit Item." << endl;
    cout << "8. Remove Item." << endl;
    cout << "9. Exit." << endl;
    cout << "Choose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        musicRepository->CreateOrder();
        break;
    case 2:
        musicRepository->FindMusic();
        break;
    case 3:
        musicRepository->SoldItems();
        break;
    case 4:
        musicRepository->ItemInStock();
        break;
    case 5:
        musicRepository->ShowAllItems();
        break;
    case 6:
        musicRepository->AddNewItemInDatabase();
        break;
    case 7:
        musicRepository->EditItem();
        break;
    case 8:
        musicRepository->RemoveItem();
        break;
    case 9:
    ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y')
        {
            return 0;
        }
        else if (exitSurity == 'n' || exitSurity == 'N')
        {
            goto reset;
        }
        else
        {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 7. Press Enter To Continue...";
        getch();
        goto reset;
        break;
    }
    if (musicRepository->isReset())
    {
        goto reset;
    }
    return 0;
}
