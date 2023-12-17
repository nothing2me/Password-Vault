#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
// Password Vault
// 1. Ask for master password, if none create one.
// 2. View passwords, : Site, username/email : password
// 3. Create passwords, : Enter site, username/email, password
// 4. Save passwords
// 4. Exit

bool masterPassword();
void menuOptions();
void viewPasswords();
void createPasswords();
string createSave();

int main() {
    cout << "Welcome to Password Vault 1.0 \n";

    if (masterPassword()){
        cout << "Master Password Entered.\n";
        menuOptions();
    }
    return 0;
}

bool masterPassword() {
    ifstream masterPassView("masterPass.txt"); // file name here
    string tempPass, storedPassword, line, delimData;
    int counter = 0;
    bool empty = true;
    // Check if the save file is empty
    if(masterPassView.peek() == ifstream::traits_type::eof()) {
        storedPassword = createSave();
    } else {
        cout << "Save found.\n";
        if(getline(masterPassView, line)){
            size_t colonPos = line.find(':');
            delimData = line.substr(colonPos + 1);
        }
    }


    while(true) {
        if (counter == 5){
            cout << "Youve ran out of password attempts. Exiting.\n";
            return false;
        }
        cout << "Enter the Master Password: ";
        cin >> tempPass;
        if (tempPass == delimData || tempPass == storedPassword) {
            return true;
        }
        counter += 1;
    }
}
// Create the save file if none with data is present and return created password
string createSave(){
    string storedMasterPassword;
    ofstream masterPassSave("masterPass.txt", ios::app);
    cout << "Save file not found, create a Master Password: ";
    cin >> storedMasterPassword;
    if(masterPassSave.is_open()){
        masterPassSave << "MasterPass:" << storedMasterPassword << "\n";
        masterPassSave.close();
    } else{
        cout << "error";
    }
    return storedMasterPassword;
}

void menuOptions(){
    int input;
    while(true) {
        cout << "-Welcome to the main menu-\n";
        cout << "(1) View Passwords\n";
        cout << "(2) Create Password\n";
        cout << "(3) Leave\n";
        cin >> input;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else if (input >= 1 && input <= 3){
            switch(input){
                case 1: viewPasswords();
                    break;
                case 2: createPasswords();
                    break;
                case 3: exit(99);
            }
        }
    }
}

void viewPasswords(){
    ifstream masterPassView("masterPass.txt");
    string line;
    if(!masterPassView.is_open()){
        cout << "No passwords found.";
        return;
    }
    while(getline(masterPassView, line)){
        cout << line << "\n";
    }
}
// Creates passwords with format
void createPasswords(){
    ofstream masterPassSave("masterPass.txt", ios::app);
    string site, username, password;
    cout << "Enter Website: ";
    cin >> site;

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    masterPassSave << site << ", " << username << " : " << password << "\n";

    masterPassSave.close();

}
