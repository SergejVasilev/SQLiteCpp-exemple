#include <iostream>
#include <Windows.h>
#define SQLITECPP_COMPILE_DLL
#include <SQLiteCpp/SQLiteCpp.h>
// работа с базой данных SQLiteCpp 

int main() 
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try
    {
        // Открываем базу данных
        SQLite::Database db("users.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // Создаем таблицу, если она не существует
        db.exec("CREATE TABLE IF NOT EXISTS person (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)");

        // Вставляем данные в таблицу
        db.exec("INSERT INTO person (name, age) VALUES ('ТЕРМИНАТОР', 30)");

        SQLite::Statement query(db, "INSERT INTO person (name, age) VALUES (?, ?)");
        // query.reset();
        query.bind(1, "12345");
        query.bind(2, 15);
        query.exec();


        // Подготавливаем запрос
        SQLite::Statement query_1(db, "SELECT * FROM person");

        // Выполняем запрос и выводим результаты
        while (query_1.executeStep()) {
            std::cout << "id: " << query_1.getColumn(0) << ", name: " << query_1.getColumn(1) << ", age: " << query_1.getColumn(2) << std::endl;
        }


    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}