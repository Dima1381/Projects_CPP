User Registration and Authentication System with MySQL Database

The project is a Registration and Authentication System implemented in C++ and utilizes a MySQL database. 
The system caters to two types of users: regular users and administrators. It enables users to perform registration and authentication processes securely. 
To safeguard sensitive data, such as passwords, the system incorporates a custom hashing algorithm developed in the "Hashing" project.

The MySQL database comprises two identical tables, "Users" and "Administrators," where user data is stored. 
During registration, user data is inserted into the database using SQL queries. During authentication, the system searches for users in the database to validate their credentials.

The project is organized into several classes:

Interface: This class determines the user type (user or admin) and prompts the user to choose one of the provided authentication options.

DB: The DB class handles all interactions with the database, including establishing connections, searching for users, and adding new users.

Hashing: The Hashing class is responsible for hashing user passwords to enhance security.

Authentication: The Authentication class handles user interactions and includes methods for presenting menus and conducting the actual authentication process.

To ensure smooth operation, the project relies on various libraries for working with the MySQL database, such as mysql.h, mysql_driver.h, and cppconn/prepared_statement.h. 
Proper configuration is essential for the project to function correctly, which involves specifying the appropriate include directory paths, adding necessary dynamic libraries to the project, and creating the database itself. 
Detailed instructions and illustrations for these setup steps are provided in the "Setup for project.docx" file.
This Registration and Authentication System project provides a robust and secure solution for managing users' access to the system while safeguarding their sensitive information.