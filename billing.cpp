#include<iostream>
#include<fstream>

using namespace std;

// class containing all the information about the administrator, buyer and items
class shopping {
    private :
        int product_code;
        string product_name;
        float price;
        float discount;
    public :
        void menu();
        void administrator();
        void buyer();
        void addItem();
        void editItem();
        void removeItem();
        void list();
        void reciept();
};

// main menu for the supermarket billing system
void shopping :: menu() {
    m :
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t---------------------------------\n";
    cout << "\t\t\t\t                                 \n";
    cout << "\t\t\t\t      Supermarket Main menu      \n";
    cout << "\t\t\t\t                                 \n";
    cout << "\t\t\t\t---------------------------------\n";
    

    cout << "\t\t\t\t   1) Administrator      |\n";
    cout << "\t\t\t\t                         |\n";
    cout << "\t\t\t\t   2) Buyer              |\n";
    cout << "\t\t\t\t                         |\n";
    cout << "\t\t\t\t   3) Exit               |\n";
    cout << "\t\t\t\t                         |\n";


    cout << "\n\n Please select : ";
    
    cin >>choice;

    switch(choice) {
        case 1 :
            cout << "\nPlease Login \n\n";
            cout << "Enter Email ";
            cin >> email;
            cout << "Enter Password ";
            cin >> password;

            if(email == "a" && password == "1") {
                administrator();
            }
            else {
                cout << "\n\nInvalid email/password\n\n";
            }

            break;
            
        case 2 : 
            {
                buyer();
            }

            break;
        case 3 :
            {
                exit(0);
            }
            
            break;
        default :
            {
                cout << "\n\n Please select from the given options \n\n";
            }
    }
    
    goto m;
}

// Displays the works Administrator can do
void shopping :: administrator() {
    m :
    int choice;
    cout << "\n\n\t\t\t Administrator menu";
    cout << "\n\t\t\t|-----1) Add the product------|";
    cout << "\n\t\t\t|                             |";
    cout << "\n\t\t\t|-----2) Modify the product---|";
    cout << "\n\t\t\t|                             |";
    cout << "\n\t\t\t|-----3) Delete the Product---|";
    cout << "\n\t\t\t|                             |";
    cout << "\n\t\t\t|-----4) Back to main menu----|";
    cout << "\n\t\t\t|                             |";

    cout << "\n\n Please enter your choice ";
    cin >> choice;

    switch(choice) {
        case 1 :
            addItem();
            break;
        case 2 :
            editItem();
            break;
        case 3 :
            removeItem();
            break;
        case 4 :
            menu();
            break;
        default :
            cout << "\n\nInvalid choice!\n\n";
    }
    goto m;
}

// Prompts the options for the buyer
void shopping :: buyer() {
    m :
    int choice;

    cout << "\t\t\t    Buyer  \n";
    cout << "\t\t\t---------------  \n";
    cout << "\t\t\t 1) Buy Product  \n";
    cout << "\t\t\t                 \n";
    cout << "\t\t\t 2) Go Back      \n";
    cout << "\t\t\t                 \n";

    cout << "Enter your choice : ";

    cin >> choice;

    switch(choice) {
        case 1 :
            reciept();
            break;
        case 2 :
            menu();
            break;
        default : 
            cout << "\n\nInvalid Choice\n\n";
    }
    goto m;
}

// Add Item to the database
void shopping::addItem() {
    fstream data;
    int c, token = 0;
    float p, d;
    string n;

    cout << "\nAdd new product ";

    cout << "\n\n Product Code of the product ";
    cin >> c;
    cout << "\n\n Name of the product ";
    cin >> n;
    cout << "\n\n Price of the product ";
    cin >> p;
    cout << "\n\n Discount on the product ";
    cin >> d;

    data.open("database.txt", ios::in);

    if(!data) {
        data.open("database.txt", ios::app | ios::out);
        data << " " << c << " " << n << " " << p << " " << d << "\n";
        data.close();
        cout << "\n\t\t\t Record inserted!";
    }
    else {
        data >> product_code >> product_name >> price >> discount;

        while(!data.eof()) {
            if(c == product_code) {
                token++;
            }
            data >> product_code >> product_name >> price >> discount;
        }
        data.close();

        if(token == 1) {
            cout << "\n\n Product Code already exists! ";
        }
        else {
            data.open("database.txt", ios::app | ios::out);
            data << " " << c << " " << n << " " << p << " " << d << "\n";
            data.close();
            cout << "\n\t\t\t Record inserted!";
        }
    }
}

// Modify the details about the Product
void shopping :: editItem() {
    fstream data, data1;
    int pkey, token = 0, c;
    float p,d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product Code :";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if(!data) {
        cout << "\n\nFile doesn't exist! ";
    }
    else {
        data1.open("database1.txt", ios::app|ios :: out);
        
        data >> product_code >> product_name >> price >> discount;
        while(!data.eof()) {
            if(pkey == product_code) {
                cout << "\n\t\t New Product Code : ";
                cin >>  c;
                cout << "\n\t\t Name of the Product : ";
                cin >>  n;
                cout << "\n\t\t Price : ";
                cin >>  p;
                cout << "\n\t\t Discount : ";
                cin >>  d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record edited ";
                
                token++;
            }
            else {
                data1 << " "  << product_code << " " << product_name << " " << price << " " << discount << "\n";
            }
            data >> product_code >> product_name >> price >> discount;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0) {
            cout << "\n\n Record not found sorry!";
        }
    }
}

// remove the Item from the database
void shopping :: removeItem() {
    fstream data, data1;
    int pkey, token = 0;
    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product Code :";
    cin >> pkey;
    data.open("database.txt", ios :: in);

    if(!data) {
        cout <<"File doesn't exist!";
    }
    else {
        data1.open("database1.txt", ios::app|ios::out);
        data >> product_code >> product_name >> price >> discount;

        while(!data.eof()) {
            if(product_code == pkey) {
                cout << "\n\n\t Product deleted succesfully!";
                token++;
            }
            else {
                data1 << " " << product_code << " " << product_name << " " << price << " " << discount <<"\n";
            }
            data >> product_code >> product_name >> price >> discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0) {
            cout << "\n\n Record not found!";
        }
    }
}

// list of the items bought
void shopping :: list() {
    fstream data;
    data.open("database.txt", ios :: in);
    cout << "\n\n--------------------------------\n";
    cout << "Product_No\tName\tPrice\n";
    cout << "\n\n--------------------------------\n";
    data >> product_code >> product_name >> price >> discount;
    while(!data.eof()) {
        cout << product_code << "\t\t" << product_name << "\t\t" << price << "\n";
        data >> product_code >> product_name >> price >> discount;
    }
    data.close();
}

// Produce the reciept of the shopping
void shopping :: reciept() {
    m :
    fstream data;
    int array_code[100];
    int array_quantity[100];
    char choice;
    int c = 0;
    float amount = 0, discount_included_price  = 0, total = 0;

    cout << "\n\n\t\t\t\t RECEIPT";
    data.open("database.txt", ios :: in);
    if(!data) {
        cout << "\n\n Empty database\n";
    }
    else {
        data.close();
        list();

        cout << "\n-------------------------------\n";
        cout << "\n                               \n";
        cout << "\n    Please place the order     \n";
        cout << "\n                               \n";
        cout << "\n-------------------------------\n";

        do {
            cout << "\n\nEnter product code : ";
            cin >> array_code[c];
            cout << "\n\nEnter the product quantity : ";
            cin >> array_quantity[c];
            for(int i=0; i<c; ++i) {
                if(array_code[c] == array_code[i]) {
                    cout << "\n\n Duplicate product code. Please try again!";
                    goto m;
                }
            }
            c++;
            cout << "Do you want to buy another product ? If yes press y else n\n";
            cin >> choice;
        }
        while(choice == 'y');

        cout << "\n\n\t\t\t-----------RECEIPT----------\n";
        cout << "\nProduct No\t Product Name\t Product Quantity\t Price\t Amount with discount\n";

        for(int i=0; i<c; ++i) {
            data.open("database.txt",ios::in);
            data >> product_code >> product_name >> price >> discount;
            while(!data.eof()) {
                if(product_code == array_code[i]) {
                    amount = price * array_quantity[i];
                    discount_included_price = amount - ((amount*discount)/100);
                    total += discount_included_price;
                    cout << "\n" << product_code << "\t\t" << product_name << "\t\t" << array_quantity[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << discount_included_price;
                }
                data >> product_code >> product_name >> price >> discount; 
            }
            data.close();
        }
    }
    cout << "\n\n----------------------------------------";
    cout << "\n Total Amount : " << total << endl;
}

// main function displays menu
int main() {
    shopping s;
    s.menu();
}