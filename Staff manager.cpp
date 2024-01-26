#include "main.h"
#include "Worker.h"
#include <Windows.h>
#include <limits>
using std::cout; using std::cin; using std::endl; using std::string;

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251); // функция устанавливает кодовую таблицу(win-cp 1251) для работы с потоком ввода
    SetConsoleOutputCP(1251); // функция устанавливает кодовую таблицу(win-cp 1251) для работы с потоком вывода

    std::vector<Worker> staff;
    char choice;
    do {
        cout << "Choose action :" << endl;
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 'N':
        case 'n':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            newWorker(staff);
            break;
        case 'E':
        case 'e':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            editWorker(staff);
            break;
        case 'F':
        case 'f':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            editWorker(staff, operation_On_Worker::FIND);
            break;
        case 'D':
        case 'd':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            editWorker(staff, operation_On_Worker::DEL);
            break;
        case 'S':
        case 's':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            writeStaffToFile(staff);
            break;
        case 'R':
        case 'r':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            readStaffFromFile(staff);
            break;
        case 'V':
        case 'v':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            printStaff(staff);
            break;
        case 'C':
        case 'c':
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            sortWorkers(staff);
            break;
        case 'Q':
        case 'q':
            if (choice == 'Q')
                choice = 'q';
            break;
        default:
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            cout << "Invalid input. Try again." << endl;
        }
        cout << endl;
    } while (choice != 'q');


    system("pause");
    return 0;
}

/*==================================================================================================================================================================================================================
*******************************************************************************   КОНЕЦ БЛОКА MAIN()   *************************************************************************************************************
==================================================================================================================================================================================================================*/




/*
int rnd(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

rand() % 100
std::ofstream fout("cppstudio.txt");          создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
fout << "Работа с файлами в С++";             запись строки в файл
fout.close();                                 закрываем файл
*/