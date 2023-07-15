#include "Interface.h";


// class Interface
// -------------------------------------------------------------------------------------------------------------------------------------

char validateChoice() {
    char choice;
    cin >> choice;

    // Перевірка на коректність введення
    while (cin.fail() || !isalpha(choice)) {
        cin.clear(); // Скидаємо флаг помилки
        cin.ignore();
        cout << "Invalid option entered. Please try again: ";
        cin >> choice;
    }

    return toupper(choice); // Convert the character to uppercase
}


void Interface::Welcome()
{
    char choice;
	cout << "------------------ Welcome to system -------------------" << endl;
	cout << "\nAre you an administrator(A) or a user(U) : ";
    choice = validateChoice();

    switch (choice) {
    case 'A': {  SetRole("Admin");  break; }

    case 'U': { SetRole("User"); break; }
    }
}

void Interface::Exit()
{
    cout << "\nGoodbye!" << endl; 
    return;
}


// class Authentication
// -------------------------------------------------------------------------------------------------------------------------------------

void Authentication::AuthenticationMenu()
{
    char choice;
    bool validChoice = false;
    bool authorization = false;

    do {
        cout << "\n(A) Sign in" << endl;
        cout << "(B) Sign-up" << endl;
        cout << "(X) Sign-out" << endl;
        cout << "Select an option: ";
        choice = validateChoice();

        switch (choice) {
        case 'A': {

            if (this->role == "User")
                authorization = userAuthorization();
            else
                authorization = adminAuthorization();

            validChoice = true;
            break;
        }
        case 'B': {

            this->role == "User" ? registerUser() : registerAdmin();
            authorization = true;
            validChoice = true;
            break;
        }
        case 'X': {
            Exit();
            authorization = true;
            validChoice = true;
            break;
        }
        default: {
            cout << "\nInvalid option entered. Please try again." << endl;
        }
        }
    } while (!validChoice || !authorization);
}


void Authentication::registerUser()
{
    string login, password, email;
    cout << "\nEnter username: ";
    cin >> login;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter email: ";
    cin >> email;

    bool freeUserLogin = database.isUserNameAvailable(login);

    if (freeUserLogin) {
        string hashPassword = hashing.GetHash(password);
        database.addUserToDatabase(login, hashPassword, email);
    }
    else
        cout << "Error. A user with this login is already registered" << endl;
}

void Authentication::registerAdmin()
{
    string login, password, email;
    cout << "\nEnter username: ";
    cin >> login;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter email: ";
    cin >> email;

    bool freeAdminLogin = database.isAdminNameAvailable(login);

    if (freeAdminLogin) {
        string hashPassword = hashing.GetHash(password);
        database.addAdminToDatabase(login, hashPassword, email);
    }
    else
        cout << "Error. A user with this login is already registered" << endl;
}

bool Authentication::userAuthorization()
{
    string login, password;
    cout << "\nEnter login: ";
    cin >> login;
    cout << "Enter password: ";
    cin >> password;

    string hashpassword = hashing.GetHash(password);
    bool checkRes = database.searchUserInDB(login, hashpassword);

    if (!checkRes)
        return false;

    return true;
}

bool Authentication::adminAuthorization()
{
    string login, password;
    cout << "\nEnter login: ";
    cin >> login;
    cout << "Enter password: ";
    cin >> password;

    string hashPassword = hashing.GetHash(password);
    bool checkRes = database.searchAdminInDB(login, hashPassword);

    if (!checkRes)
        return false;

    return true;
}



// class DATABASE
// -------------------------------------------------------------------------------------------------------------------------------------

sql::Connection* DB::Connection()
{
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://localhost:3306", "DIMA2003", "Dimas905"); // Localhost:port , Name Server MySql, Password from the server 
        con->setSchema("db_user"); // Name DataBase
    }
    catch (sql::SQLException const& e) {
        cout << "MySQL error when connecting: " << e.what() << endl;
        con = nullptr;  // We return nullptr if an error occurred during connection
    }

    return con;
}

void DB::addUserToDatabase(const string& login, const string& password, const string& email)
{
    sql::Connection* con = Connection();

    if (con == nullptr) {
        cout << "Unable to insert data. No connection to the database." << endl;
        return;
    }

    try {
        sql::PreparedStatement* pstmt;
        string query = "INSERT INTO users (Login, Password, Email, Reg_Date) VALUES(? , ? , ? , ? )";
        pstmt = con->prepareStatement(query);

        //Setting query parameters
        pstmt->setString(1, login);
        pstmt->setString(2, password);
        pstmt->setString(3, email);
        pstmt->setString(4, GetDate());

        pstmt->execute();

        delete pstmt;

        cout << endl;
        cout << login << " thank you for registering ^)" << endl;
    }
    catch (sql::SQLException const& e) {
        cout << "MySQL error when inserting data: " << e.what() << endl;
    }
    delete con;
}

void DB::addAdminToDatabase(const string& login, const string& password, const string& email)
{
    sql::Connection* con = Connection();

    if (con == nullptr) {
        cout << "Unable to insert data. No connection to the database." << endl;
        return;
    }

    try {
        sql::PreparedStatement* pstmt;
        string query = "INSERT INTO administrators (Login, Password, Email, Reg_Date) VALUES(? , ? , ? , ? )";
        pstmt = con->prepareStatement(query);

        //Setting query parameters
        pstmt->setString(1, login);
        pstmt->setString(2, password);
        pstmt->setString(3, email);
        pstmt->setString(4, GetDate());

        pstmt->execute();

        delete pstmt;

        cout << endl;
        cout << login << " welcome to the team ^)" << endl;
    }
    catch (sql::SQLException const& e) {
        cout << "MySQL error when inserting data: " << e.what() << endl;
    }
    delete con;
}

string DB::GetDate() // Function to get date in format: YYYY/MM/DD
{
    time_t currentTime = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &currentTime);

    int year = localTime.tm_year + 1900;
    int month = localTime.tm_mon + 1;
    int day = localTime.tm_mday;

    return (to_string(year) + "-" + to_string(month) + "-" + to_string(day));
}

bool DB::searchUserInDB(const string& login, const string& password)
{
    sql::Connection* con = Connection();

    if (con == nullptr) {
        cout << "Unable to retrieve data. No connection to the database." << endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt;
        string query = "SELECT * FROM users WHERE Login = '" + login + "' AND Password = '" + password + "';";
        pstmt = con->prepareStatement(query);


        sql::ResultSet* res = pstmt->executeQuery();

        // Обробка результату
        if (res->next()) {
            int fetchedId = res->getInt("id");
            string fetchedLogin = res->getString("Login");
            string fetchedPassword = res->getString("Password");

            if ((fetchedLogin == login) && (fetchedPassword == password))
            {
                cout << "Authorization was successful!" << endl;
                return true;
            }
        }
        else {
            cout << "Authorization error!" << endl;
            return false;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException const& e) {
        cout << "MySQL error when retrieving data: " << e.what() << endl;
    }

    delete con;
}

bool DB::searchAdminInDB(const string& login, const string& password)
{
    sql::Connection* con = Connection();

    if (con == nullptr) {
        cout << "Unable to retrieve data. No connection to the database." << endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt;
        string query = "SELECT * FROM administrators WHERE Login = '" + login + "' AND Password = '" + password + "';";
        pstmt = con->prepareStatement(query);


        sql::ResultSet* res = pstmt->executeQuery();

        // Обробка результату
        if (res->next()) {
            int fetchedId = res->getInt("id");
            string fetchedLogin = res->getString("Login");
            string fetchedPassword = res->getString("Password");

            if ((fetchedLogin == login) && (fetchedPassword == password))
            {
                cout << "Authorization was successful!" << endl;
                return true;
            }
        }
        else {
            cout << "Authorization error!" << endl;
            return false;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException const& e) {
        cout << "MySQL error when retrieving data: " << e.what() << endl;
    }

    delete con;
}

bool DB::isUserNameAvailable(const string& login)
{
    sql::Connection* con = Connection();
    bool isAvailable = false;

    if (con == nullptr) {
        cout << "Unable to insert data. No connection to the database." << endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        string query = "SELECT * FROM users WHERE Login = '" + login + "'";

        pstmt = con->prepareStatement(query);
        res = pstmt->executeQuery();

        isAvailable = !res->next();

        delete pstmt;
        delete res;
    }
    catch (sql::SQLException const& e) {
        cout << "MySQL error when inserting data: " << e.what() << endl;
        return false;
    }

    delete con;
    return isAvailable;
}

bool DB::isAdminNameAvailable(const string& login)
{
    sql::Connection* con = Connection();
    bool isAvailable = false;

    if (con == nullptr) {
        cout << "Unable to insert data. No connection to the database." << endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        string query = "SELECT * FROM administrators WHERE Login = '" + login + "'";

        pstmt = con->prepareStatement(query);
        res = pstmt->executeQuery();

        isAvailable = !res->next();

        delete pstmt;
        delete res;
    }
    catch (sql::SQLException const& e) {
        cout << "MySQL error when inserting data: " << e.what() << endl;
        return false;
    }

    delete con;
    return isAvailable;
}

// class Hashing
// -------------------------------------------------------------------------------------------------------------------------------------

string Hashing::GetHash(string password)
{
    if (lenHash > 3)
    {
        this->hash.clear();

        // minimum hash length 2^n
        unsigned int minLenHash = 2;
        // a hash length that is close to the desired length
        unsigned int realMinHash = 0;

        // Salt original string (password)
        unsigned int originalSalt = gelControlSum(password);
        unsigned int originalLenStr = password.size();

        // get string lengths 2^n closer to the given hash length
        while (minLenHash <= lenHash)
            realMinHash = (minLenHash *= 2);

        // we get closer to the length of the given line - 2^n
        // example : if original password lengths = 20, lengths hash will be = 32 (2^n)
        // length of the hash must be longer than the original password
        while (minLenHash <= originalLenStr)
            minLenHash *= 2;

        // number of symbols that must be added to the hash length
        int addCount = minLenHash - originalLenStr;

        // adding
        for (int i = 0; i < addCount; i++)
        {
            password += receivingExistCodes(password[i] + password[i + 1]);
        }

        // Maximum hash length salt
        int maxlenHashSalt = gelControlSum(password);
        int maxLenStr = password.size();

        // hash compressions : password.size / 2, until password.size != realMinHash
        while (password.size() != realMinHash)
        {
            int center = password.size() / 2;

            for (int i = 0; i < center; i++)
            {
                this->hash += receivingExistCodes(password[center - i] + password[center + i]);
            }

            password = this->hash;
            this->hash.clear();
        }

        int rem = realMinHash - lenHash;
        int countCompress = realMinHash / rem;

        // build a new hash from the previous hash, his new length = actual required length - 4 ( (-4) - because we will add 4 salts to the hash)
        for (int i = 0; hash.size() < (lenHash - 4); i++)
        {
            if (i % countCompress == 0)
                hash += receivingExistCodes(password[i] + password[++i]);
            else
                hash += password[i];
        }

        // adding salts
        hash += receivingExistCodes(originalSalt);
        hash += receivingExistCodes(originalLenStr);

        hash += receivingExistCodes(maxlenHashSalt);
        hash += receivingExistCodes(maxLenStr);

        return hash;
    }
    return "";
}

int Hashing::gelControlSum(string password)
{
    int salt = 0, lenUserStr = password.length();

    for (int i = 0; i < lenUserStr; i++)
    {
        salt += (int)password[i];
    }
    return salt;
}

char Hashing::receivingExistCodes(int x)
{
    x += 48;

    while (!((x >= 48 && x <= 57) || (x >= 65 && x <= 90) || (x >= 97 && x <= 122)))
    {
        if (x < 48) x += 20;
        else if (x > 122) x -= 100;

        else
            x -= 10;
    }
    return x;
}

