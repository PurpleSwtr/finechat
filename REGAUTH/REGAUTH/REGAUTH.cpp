#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <vector>
using namespace std;
string username;
bool deleteLoginAndPassword(const string& login, const string& password) {
    ifstream inputFile("users.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return false;
    }

    string line;
    string currentLogin, currentPassword;
    bool loginFound = false;

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        cout << "Ошибка создания временного файла" << endl;
        return false;
    }

    while (getline(inputFile, line)) {
        if (!loginFound) {
            currentLogin = line;
            loginFound = true;
        }
        else {
            currentPassword = line;
            loginFound = false;
            if (currentLogin != login || currentPassword != password) {
                tempFile << currentLogin << endl;
                tempFile << currentPassword << endl;
            }
        }
    }

    inputFile.close();
    tempFile.close();

    if (remove("users.txt") != 0) {
        cout << "Ошибка удаления файла" << endl;
        return false;
    }

    if (rename("temp.txt", "users.txt") != 0) {
        cout << "Ошибка переименования файла" << endl;
        return false;
    }

    return true;
}
void userid() {


    ifstream inputFile("users.txt"); // имя файла для чтения


    string line;
    int lineNumber = 1;
    bool printLine = true;

    while (getline(inputFile, line)) { // чтение строк из файла
        if (printLine) { // выводим строки только при значении true
            cout << lineNumber << ". " << line << endl;
            lineNumber++;
            printLine = false; // переключаем значение для вывода следующей строки
        }
        else {
            printLine = true; // переключаем значение для пропуска вывода следующей строки
        }
    }

    inputFile.close();
    system("pause");
    return;
}

int countFilledLines(const string& filename) {
    ifstream file("users.txt");
    string line;
    int count = 0;

    while (getline(file, line)) {
        if (!line.empty()) {
            count++;
        }
    }

    return count;
}

void DELuser() {
    system("cls");

    cout << "Удаление аккаунта" << endl << endl;

    string login, password;

    string filename = "users.txt";
    int begin = countFilledLines(filename);

    cout << "Введите логин: ";
    //(cin, login);
    cin >> login;
    cout << "Введите пароль: ";
    //getline(cin, password);
    cin >> password;

    deleteLoginAndPassword(login, password);
    int end = countFilledLines(filename);

    
    if (end < begin) {
        cout << "Запись успешно удалена" << endl;
    }
    if (end == begin){
        cout << "Ошибка при удалении аккаунта" << endl;
    }
    system("pause");
    return;

}

void registerUser() {
    system("cls");
    cout << "Регистрация" << endl << endl;;

    string username, password;
    cout << "Введите желаемый логин: ";
    cin >> username;

    // Проверяем существует ли пользователь с таким логином
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line == username) {
            file.close();
            system("cls");

            cout << "Такой логин уже существует." << endl;
            system("pause");

            return;
        }
    }
    file.close();

    cout << "Введите пароль: ";
    cin >> password;

    // Записываем логин и пароль пользователя в файл
    ofstream outFile("users.txt", ios::app);
    outFile << username << endl;
    outFile << password << endl;
    outFile.close();
    system("cls");

    cout << "Пользователь успешно зарегистрирован." << endl;
    system("pause");

}
void write(void)
{
    system("cls");
    string line_msg;
    string ardesat_file;
    string adresat_name;
    string line;
    string filename;
    string message;
    ifstream inputFile("users.txt"); // имя файла для чтения
    ofstream OutputTempFile("names.txt");
    string input_msg;
    
    SYSTEMTIME clock;
    int lineNumber = 1;
    bool printLine = true;

    while (getline(inputFile, line)) { // чтение строк из файла
        if (printLine) { // выводим строки только при значении true
            cout << lineNumber << ". " << line << endl;
            OutputTempFile << line << endl;

            lineNumber++;
            printLine = false; // переключаем значение для вывода следующей строки
        }
        else {
            printLine = true; // переключаем значение для пропуска вывода следующей строки
        }

    }
        inputFile.close();
        OutputTempFile.close();
    cout << endl << "Введите никнейм кому хотите написать: " << endl;

    ifstream file("names.txt");
    cin >> input_msg;

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    bool match_found = false;
    while (getline(file, line_msg)) {
        if (line_msg == input_msg) {
            match_found = true;

            break;
        }
    }
    
            file.close();
    

    if (match_found) {
        filename = input_msg + ".txt";
        system("cls");
        cout << "Введите сообщение для " << input_msg << " : ";
        

        cin.ignore();
        getline(cin, message);
        ofstream OutputTempFile(filename, ios::app);
        

        // Ввод предложения с клавиатуры

        system("cls");

        if (OutputTempFile.is_open()) {
            // Запись предложения в файл
            GetLocalTime(&clock);
            OutputTempFile << username << " " << clock.wHour << ":" << clock.wMinute << " " << message << "\n";

            // Закрытие файла
            OutputTempFile.close();
            cout << endl << "Сообщение отправлено!" << endl;
        }
        else {
            cerr << "Не удалось открыть файл для записи!";
        }
        system("pause");
    }
    else {
        cout << "Совпадение не найдено!" << endl;
    }
    

}
void readmessage(void)
{
    string msgfilename;
    msgfilename = username + ".txt";
    ifstream file(msgfilename); // Путь к файлу для чтения

    unordered_set<string> words; // Хранилище уникальных слов
    string line, word;

    if (file.is_open()) {
        // Считываем строки из файла
        while (getline(file, line)) {
            stringstream ss(line); // Преобразовываем строку в поток для чтения слов

            // Ищем первое слово каждой строки
            if (ss >> word) {
                words.insert(word); // Добавляем в хранилище уникальных слов
            }
        }

        file.close(); // Закрываем файл
    }
    else {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    // Выводим уникальные первые слова на экран
    system("cls");
    cout << "Ваши чаты: " << endl;
    for (const auto& w : words) {
        cout << w << endl;
    }

    // Пользователь выбирает первое слово для дальнейшего вывода связанных сообщений
    string selectedWord;
    cout << endl << "Выберите чат: " << endl;

    cin >> selectedWord;
    system("cls");

    // Выводим связанные сообщения на экран
    file.open(msgfilename); // Повторно открываем файл для чтения связанных сообщений
    if (file.is_open()) {
        cout << "Чат с пользователем: " << selectedWord << endl << endl;

        while (getline(file, line)) {
            istringstream iss(line);
            string word;
            iss >> word; // считываем первое слово
            if (word == selectedWord) {
                while (iss >> word) { // считываем и выводим остальные слова
                    cout << word << " ";
                }
            cout << endl<< endl;
            }

        }
        file.close(); // Закрываем файл
    }
    else {
        cout << "Не удалось открыть файл." << endl;
        return;
    }
    system("pause");
    return;
}
void massageroom(void)
{
    int massage_cnt = 0;
    int choice_msg;
    string input_msg;
    string msgfilename;
    msgfilename += username + ".txt";
    

    ifstream files(msgfilename);

    
    string msgline;
    while (getline(files, msgline)) {
        massage_cnt++;
    }
    files.close();
    


    do {
        system("cls");
    cout << "Вы вошли как: " << username <<  " У вас (" << massage_cnt << ") сообщений" << endl;

        cout << "1. Написать сообщение" << endl;
        cout << "2. Прочитать сообщения" << endl;
        cout << "3. Удалить сообщение" << endl;
        cout << "4. Выход из аккаунта" << endl << endl;
        cout << "Выберите действие: ";
        bool valid = false;

        while (!valid) {
            cin >> input_msg;

            try {
                choice_msg = stoi(input_msg);
                valid = true;
            }
            catch (const exception& e) {
                system("cls");
                cout << "Ошибка! Введите число ещё раз." << endl;
                system("pause");
                system("cls");
                cout << "1. Написать сообщение" << endl;
                cout << "2. Прочитать сообщения" << endl;
                cout << "3. Удалить сообщение" << endl;
                cout << "4. Выход из аккаунта" << endl << endl;
                cout << "Выберите действие: ";

            }
        }
        switch (choice_msg) {
        case 1: // НАПИСАТЬ
            write();
            break;
        case 2: // ПРОЧИТАТЬ
            readmessage();
            break;
        case 3: // УДАЛИТЬ
            break;
        case 4:
            system("cls");
            cout << "Выход из аккаунта" << endl;
            break;
        default:
            system("cls");

            cout << "Неправильный выбор." << endl;
            system("pause");

            break;
        }
    } while (choice_msg != 4);
}
void authenticateUser() {
    system("cls");
    cout << "Аутентификация" << endl << endl;;
    string password;
    cout << "Введите логин: ";
    cin >> username;
    cout << "Введите пароль: ";
    cin >> password;
    ifstream file("users.txt");
    
    string line;
    
    while (getline(file, line)) {
        if (line == username && getline(file, line) && line == password) {
            file.close();
            system("cls");

            
            cout << "Авторизация успешна." << endl;
            massageroom();
            system("pause");
            return;

        }
    }
    file.close();
    system("cls");

    cout << "Неверный логин или пароль." << endl;
    system("pause");

}
int main() {
    system("color F0");
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string input;
    int choice;
    do {
    
        system("cls");
        
            
        
        
            cout << "Меню:" << endl;
            cout << "1. Регистрация" << endl;
            cout << "2. Авторизация" << endl;
            cout << "3. Удалить Аккаунт" << endl;
            cout << "4. Список" << endl;
            cout << "5. Выход" << endl << endl;
            cout << "Выберите действие: ";
            bool valid = false;

            while (!valid) {
                cin >> input;

                try {
                    choice = stoi(input);
                    valid = true;
                }
                catch (const exception& e) {
                    system("cls");
                    cout << "Ошибка! Введите число ещё раз." << endl;
                    system("pause");
                    system("cls");
                    cout << "Меню:" << endl;
                    cout << "1. Регистрация" << endl;
                    cout << "2. Авторизация" << endl;
                    cout << "3. Удалить Аккаунт" << endl;
                    cout << "4. Список" << endl;
                    cout << "5. Выход" << endl << endl;
                    cout << "Выберите действие: ";

                }
            }


            switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                authenticateUser();
                break;
            case 3:
                DELuser();
                break;
            case 4:
                system("cls");
                userid();
                break;
            case 5:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неправильный выбор." << endl;
                break;
            }
        
     } while (choice != 5);
        return 0;
    
}

