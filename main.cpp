#include "main.h"
#include "Worker.h"
using std::cout; using std::cin; using std::endl; using std::string;

void showMenu()
{
    cout << std::setw(21) << std::left << "N New worker." << "||  " << std::setw(16) << std::left << "E Edit data." << "||  " << std::setw(21) << std::left << "F Find worker." << endl;
    cout << std::setw(21) << std::left << "D Delete worker." << "||  " << std::setw(16) << std::left << "S Save to file." << "||  " << std::setw(21) << std::left << "R Load from file." << endl;
    cout << std::setw(21) << std::left << "V Show all workers." << "||  " << std::setw(16) << std::left << "C Sort data." << "||  " << std::setw(21) << std::left << "Q Quit." << endl;
}
/*******************************************************************************************************************************************************/

bool stringInputValidation(std::string& s, const char* sign, bool edit)
{
    while (1)
    {
        if (edit == false)  // Режим new
        std::cout << "Enter " << sign << ": ";
        else           // Режим edit
        std::cout << "Enter new " << sign << " (press Enter to keep previous value): ";
        std::string str;
        std::getline(cin, str); // извлекаем целую строку, включая пробелы
        if (str.empty() && edit == true) // если в режиме edit нажат Enter, то ничего не делаем, выходим из функции, и переходим к следующему полю
            return 0;
        if (str.length() > 15 && sign != "post")
        {
            cout << "Error. This field must not contain more than 15 letters" << endl;
            continue;
        }
        if (str.length() > 29 && sign == "post")
        {
            cout << "Error. This field must not contain more than 29 letters, including spaces" << endl;
            continue;
        }
        bool bRejected = false;
        // Перебираем каждый символ строки до тех пор, пока не дойдем до конца строки или до отклонения символа
        for (unsigned int nIndex = 0; nIndex < str.length() && !bRejected; ++nIndex)
        {
            // Если текущий символ является буквой, то всё ок
            if (isalpha(str[nIndex]))
                continue;
            // Если пробел, то это не ок
            if (str[nIndex] == ' ')
               cout << "Spaces not allowed. Use _ as delimiter." << endl;
            // В противном случае, отклоняем весь пользовательский ввод
            bRejected = true;
        }
        if (str.empty())
        str = "-     ";
        // Если пользовательский ввод был принят, то мы выходим из цикла while, и программа завершает свое выполнение.
        // В противном случае, мы просим пользователя ввести свое имя еще раз
        if (!bRejected)
        {
            if (sign == "post") // Добавляем пробел в конец, чтобы отделить должность пробелом от символа автозаполнения '-'
                str += " ";
            s = str;
            if (edit == 1)
                return 1;
            return 0;
        }
    }
}
/*******************************************************************************************************************************************************/

bool intInputValidation(int& i, const char* sign, bool edit)
{
    while (1)
    {
        if (edit == false)  // Режим new
            std::cout << "Enter " << sign << ": ";
        else           // Режим edit
            std::cout << "Enter new " << sign << " (-1 to keep previous value): ";
        int num;
        // здесь был std::cin.ignore(32767, '\n') и он вызывал двойной запрос на ввод, как бы игнорируя первый ввод ??? ПОЧЕМУ???
        cin >> num;
        if (std::cin.fail()) // если предыдущее извлечение не выполнилось или произошло переполнение,
            {
                std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
                cout << "Error. Wrong input." << endl;
                continue;
            }
        
        if (num == -1 && edit == true) // если введено -1, то ничего не делаем, выходим из функции, и переходим к следующему полю
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }
        if (num >= 999999 || num < 0)
        {
            cout << "Error. This field must not contain more than 6 digits. Value must be positive." << endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        i = num;
        std::cin.ignore(32767, '\n');
        if (edit == true)
            return 1;
        return 0;
    }
}
/*******************************************************************************************************************************************************/

void newWorker(std::vector<Worker>& staff)
{
    cout << "Adding new worker:" << endl;
    int id; string Surname; string Name; string Patronymic; string Post; int Hours; int PayPerHour;
    intInputValidation(id, "ID");
    stringInputValidation(Name, "name");
    stringInputValidation(Surname, "surname");
    stringInputValidation(Patronymic, "patronymic");
    stringInputValidation(Post, "post");
    intInputValidation(Hours, "hours");
    intInputValidation(PayPerHour, "pay per hour");
    staff.push_back(Worker(id, Surname, Name, Patronymic, Post, Hours, PayPerHour));
}
/*******************************************************************************************************************************************************/

void editWorker(std::vector<Worker>& staff, operation_On_Worker operation)
{
    int id;
    while (1) // пользователь вводит ID работника для редактирования
    {
        cout << "Enter ID of worker that you want to " << (operation == operation_On_Worker::DEL ? "delete (-1 to delete all workers): " : operation == operation_On_Worker::FIND ? "find: " : "edit: ");
        int local_id;
        std::cin >> local_id;
        if (operation == operation_On_Worker::DEL && local_id == -1)
        {
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            staff.clear();
            cout << "All workers succesfully deleted" << endl;
            return;
        }
        if (std::cin.fail() || local_id < 0 || local_id > 999999) // если предыдущее извлечение не выполнилось или произошло переполнение,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            cout << "Error. Wrong input." << endl;
            continue;
        }
        id = local_id;
        break;
    }
    int index = -1; // значение по умолчанию на случай если работников с таким ID найдено не будет
    int copiesID = findDuplicateIDs(staff, static_cast<int>(staff.size()), true, id) + 1; // CopiesID - сколько всего экземпляров данного ID в векторе   
    if (copiesID > 1)  // обработка случая если работников с таким id несколько 
    {
        cout << static_cast<int>(copiesID) << " copies of ID " << id << " found!" << endl;
        std::vector<int> indexesOfWorkersWithChoosenID;
        for (int i = 0; i < staff.size(); ++i)
        {
            if (staff[i].getId() == id)
            indexesOfWorkersWithChoosenID.push_back(i);
        }
        
        printStaffTableHead();                                                 // Печатаем всех работников
        for (int i = 0; i < indexesOfWorkersWithChoosenID.size(); ++i)         // с заданным ID
        {
            cout << std::setw(Worker::m_number_w) << std::left << i + 1;
            staff[indexesOfWorkersWithChoosenID[i]].m_print();
        }
        
        if (operation == operation_On_Worker::FIND) // Если включен режим поиска, то выполняется функция выбора действия с найденными работниками
            operation = FindMode_action_user_define();
        if (operation == operation_On_Worker::FIND)
            return;
        
        while (1)
        {
            cout << "Choose one of the listed workers with ID " << id << (operation == operation_On_Worker::DEL ? " to delete" : " to edit") << ". Enter # of worker: " << endl;
            int num;
            cin >> num;
            if (std::cin.fail()) // если предыдущее извлечение не выполнилось или произошло переполнение,
            {
                std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
                cout << "Error. Wrong input." << endl;
                continue;
            }
            if (num > indexesOfWorkersWithChoosenID.size() || num < 1)
            {
                cout << "Error. This field must not contain more than 3 digits. Value must be positive." << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            index = indexesOfWorkersWithChoosenID[num - 1];
            std::cin.ignore(32767, '\n');
            break;
        }
    }
    if (copiesID == 1) // обработка случая, если работник с таким ID только один
    {
        for (int i = 0; i < staff.size(); ++i) // попытка найти работника с введенным ID
        {
            if (staff[i].getId() == id)
            {
                index = i;
                if (operation == operation_On_Worker::FIND)
                {
                    printStaffTableHead();  // выводим шапку таблицы
                    cout << std::setw(Worker::m_number_w) << std::left << "";
                    staff[index].m_print();     // выводим строку работника с данным ID
                    operation = FindMode_action_user_define();
                    if (operation == operation_On_Worker::FIND)
                        return;
                }
                break;
            }
        }
    }
    if (index == -1) // если работник с таким ID не найден
    {
        cout << "Worker with ID " << id << " not found" << endl;
        return;
    }
    // Блок редактирования работника с заданным ID
    if (operation == operation_On_Worker::EDIT)
            cout << "Editing worker with ID " << id << ":" << endl;
            printStaffTableHead();  // выводим шапку таблицы
            cout << std::setw(Worker::m_number_w) << std::left << "";
            staff[index].m_print();     // выводим строку работника с данным ID
            if (operation == operation_On_Worker::EDIT)
            {
                int id_local; string Surname; string Name; string Patronymic; string Post; int Hours; int PayPerHour;
                if (intInputValidation(id_local, "ID", 1))
                    staff[index].setId(id_local);
                if (stringInputValidation(Name, "name", 1))
                    staff[index].setName(Name);
                if (stringInputValidation(Surname, "surname", 1))
                    staff[index].setSurname(Surname);
                if (stringInputValidation(Patronymic, "patronymic", 1))
                    staff[index].setPatronymic(Patronymic);
                if (stringInputValidation(Post, "post", 1))
                    staff[index].setPost(Post);
                if (intInputValidation(Hours, "hours", 1))
                    staff[index].setHours(Hours);
                if (intInputValidation(PayPerHour, "pay per hour", 1))
                    staff[index].setPayPerHour(PayPerHour);
                staff[index].recalculateSalary();
            }
            else
            {
                staff.erase(staff.begin() + index);
                cout << "Worker with ID " << id << " succesfully deleted." << endl;
            }
}
/*******************************************************************************************************************************************************/

void printStaffTableHead() // Печать шапки таблицы работников
{
        cout << std::setw(Worker::m_number_w) << std::left << "#" << std::setw(Worker::m_id_w) << std::left << "ID" << std::setw(Worker::m_surname_w) << std::left << "Surname" << std::setw(Worker::m_name_w) << std::left << "Name" \
        << std::setw(Worker::m_patronymic_w) << std::left << "Patronymic" << std::setw(Worker::m_post_w) << std::left << "Post" << ' ' << std::setw(Worker::m_pph_w) << std::left << "h/pay" \
        << std::setw(Worker::m_hours_w) << std::left << "Hours" << std::setw(Worker::m_salary_w) << std::left << "Salary" << endl;
}
/*******************************************************************************************************************************************************/

void printStaff(std::vector<Worker>& staff) // Печать работников
{
    if (staff.size() == 0)
    {
        cout << "No workers added yet." << endl;
        return;
    }
    printStaffTableHead();
    for (int i = 0; i < staff.size(); ++i)
    {
        cout << std::setw(Worker::m_number_w) << std::left << i + 1;
        staff[i].m_print();
    }
}
/*******************************************************************************************************************************************************/

void writeStaffToFile(std::vector<Worker>& staff) // Вывод работников в структурированный файл
{
    cout << "Enter full path (without quotes) where to save your file. e.g: \"C:/temp/staff.txt\", \nor enter file name (e.g) \"new_staff.txt\" to save in program folder, \nor press enter to save to staff.txt in program folder" << endl;
    string file;
    std::getline(cin, file);
    std::fstream fout;
    if (file.empty())
        fout.open("staff.txt", std::ios::in | std::ios::app);
    else
    fout.open(file, std::ios::in | std::ios::app);
    if (!fout.is_open())
    {
        if (file.empty())
            cout << "Cannot open staff.txt in " << std::filesystem::current_path() << endl;
        else
        cout << "Cannot open \"" << file << "\" for writing";
        return;
    }
    // если файл успешно открыт, выполняется остальной код:
    read_write_mode operation;
    std::vector<Worker> staffCopyFromSaveTo; // Копия вектора работников для случая PUSH_FRONT
    while (1)
    {
        if (fout.peek() == EOF)
        {
            operation = read_write_mode::REWRITE;
            break;
        }
        cout << "1 - rewrite file, 2 - append to end, 3 - insert in front" << endl;
        int chooseLoadFileMode;
        cin >> chooseLoadFileMode;
        if (std::cin.fail() || chooseLoadFileMode < 1 || chooseLoadFileMode > static_cast<int>(read_write_mode::MAX_OPTIONS)) // если предыдущее извлечение не выполнилось или произошло переполнение,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
            cout << "Error. Wrong input." << endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
        operation = static_cast<read_write_mode>(chooseLoadFileMode - 1);
        break;
    }
    
    switch (operation)
    {
    case read_write_mode::REWRITE:
        //fout.clear();
        fout.close();
        if (file.empty())
            fout.open("staff.txt", std::ios::in | std::ios::out | std::ios::trunc);
        else
            fout.open(file, std::ios::in | std::ios::out | std::ios::trunc);
        if (!fout.is_open())
        {
            if (file.empty())
                cout << "Cannot open staff.txt in " << std::filesystem::current_path() << endl;
            else
                cout << "Cannot open \"" << file << "\" for writing" << endl;
            return;
        }
                
        fout << std::setw(Worker::m_number_w) << std::left << "#" << std::setw(Worker::m_id_w) << std::left << "ID" << std::setw(Worker::m_surname_w) << std::left << "Surname" << std::setw(Worker::m_name_w) << std::left << "Name" \
            << std::setw(Worker::m_patronymic_w) << std::left << "Patronymic" << std::setw(Worker::m_post_w) << std::left << "Post" << std::setw(Worker::m_pph_w) << std::left << "h/pay" \
            << std::setw(Worker::m_hours_w) << std::left << "Hours" << std::setw(Worker::m_salary_w) << std::left << "Salary" << endl;
        break;

    case read_write_mode::PUSH_BACK:
        fout.close();
        if (file.empty())
            fout.open("staff.txt", std::ios::in | std::ios::out | std::ios::app);
        else
            fout.open(file, std::ios::in | std::ios::out | std::ios::app);
        if (!fout.is_open())
        {
            if (file.empty())
                cout << "Cannot open staff.txt in " << std::filesystem::current_path() << endl;
            else
                cout << "Cannot open \"" << file << "\" for writing" << endl;
            return;
        }
        break;

    case read_write_mode::PUSH_FRONT:
        fout.seekg(0, std::ios::beg);
        string str;
        std::getline(fout, str);

        if (str[0] == '#')
        {
            fout.seekg(str.size(), std::ios::beg);
        }
        else
        {
            cout << "For inserting data, file must start with #" << endl;
            return;
        }
        int id, payPerHour, hours, salary;
        string surname, name, patronymic, post;
        fout.seekp(fout.tellg(), std::ios::beg);

        while (fout >> id >> id >> surname >> name >> patronymic >> post >> payPerHour >> hours >> salary)
        {
            staffCopyFromSaveTo.push_back(Worker(id, surname, name, patronymic, post, payPerHour, hours));
        }
        
        fout.close();
        if (file.empty())
            fout.open("staff.txt", std::ios::in | std::ios::out | std::ios::trunc);
        else
            fout.open(file, std::ios::in | std::ios::out | std::ios::trunc);
        if (!fout.is_open())
        {
            if (file.empty())
                cout << "Cannot open staff.txt in " << std::filesystem::current_path() << endl;
            else
                cout << "Cannot open \"" << file << "\" for writing" << endl;
            return;
        }

        fout << std::setw(Worker::m_number_w) << std::left << "#" << std::setw(Worker::m_id_w) << std::left << "ID" << std::setw(Worker::m_surname_w) << std::left << "Surname" << std::setw(Worker::m_name_w) << std::left << "Name" \
            << std::setw(Worker::m_patronymic_w) << std::left << "Patronymic" << std::setw(Worker::m_post_w) << std::left << "Post" << std::setw(Worker::m_pph_w) << std::left << "h/pay" \
            << std::setw(Worker::m_hours_w) << std::left << "Hours" << std::setw(Worker::m_salary_w) << std::left << "Salary" << endl;
        break;
    }

    int i = 0; // Количество строк в файле в который записываем
    if (operation == read_write_mode::PUSH_BACK) // Подсчет i, а также вставка переноса строки если она отсутствует в конце файла (для последующей корректной записи в файл с новой строки) 
    {
        std::ifstream fin_calc_rows;
        if (file.empty())
            fin_calc_rows.open("staff.txt");
        else
            fin_calc_rows.open(file);
        if (!fin_calc_rows.is_open())
        {
            if (file.empty())
                cout << "Cannot open staff.txt in " << std::filesystem::current_path() << endl;
            else
                cout << "Cannot open \"" << file << "\" for writing";
            return;
        }
        i = nStrings(fin_calc_rows) - 1;
        fin_calc_rows.seekg(-1, std::ios::end);
        if (fin_calc_rows.peek() != '\n')
        {
            fout.put('\n');
            cout << "!!!\n";
        }
    }

        for (Worker& n : staff) // Записываем работников в файл
        {
            fout << std::setw(Worker::m_number_w) << std::left << i + 1;
            n.m_writeToFile(fout);
            ++i;
        }
        if(operation == read_write_mode::PUSH_FRONT) // Добавляем работников из копии в конец файла, если установлен PUSH_FRONT
        for (int j = 0; j < staffCopyFromSaveTo.size(); ++j)
        {
            fout << std::setw(Worker::m_number_w) << std::left << staff.size() + j + 1;
            staffCopyFromSaveTo[j].m_writeToFile(fout);
        }
        
        fout.close();
        if (file.empty())
        cout << "staff.txt succesfully saved to " << std::filesystem::current_path() << endl;
        else
        cout << "File succesfully saved to \"" << file << "\"" << endl;
}
/*******************************************************************************************************************************************************/

int nStrings(std::ifstream& fin) // функция вычисляет количество не пустых строк в загружаемом файле
{
    if (!fin.good())
        return 0;
    fin.seekg(0, std::ios::beg);
    string s;
    int nStrings{ 0 };
    while (std::getline(fin, s))
    {
        for (char n : s)
        {
            if (n != ' ')
            {
                ++nStrings;
                break;
            }
        }
    }
    fin.clear();
    fin.seekg(0, std::ios::beg);
    return nStrings;
}
/*******************************************************************************************************************************************************/

void readStaffFromFile(std::vector<Worker>& staff) // Загрузка списка работников из структурированного файла
{
    read_write_mode mode = read_write_mode::REWRITE; // REWRITE - clear Worker vector before loading from file, PUSH_BACK - append file to Worker vector at end,  PUSH_FRONT - insert in front
    cout << "Enter full path to open file. e.g: \"C:/temp/staff.txt\", \nor type name of file in program folder e.g \"staff_new.txt\", \nor press enter to open staff.txt in program folder" << endl;
    string file;
    std::getline(cin, file); // Пользователь вводит имя файла
    std::ifstream fin;
    if (file.empty())
    fin.open("staff.txt");
    else
        fin.open(file);
    if (!fin)
    {
        if (file.empty())
            cout << "Cannot open staff.txt in " << std::filesystem::current_path() << endl;
        else
        cout << "Cannot open \"" << file << "\"" << endl;
        return;
    }
    int workersCount = nStrings(fin) - 1;  // Количество загружаемых рабочих = количество строк в файле минус строка с шапкой
        while (1)
        {
            if (staff.size() == 0)
                break;
            cout << "1 - rewrite data with data from file, 2 - append at end, 3 - insert in front" << endl;
            int chooseLoadFileMode;
            cin >> chooseLoadFileMode;
            if (std::cin.fail() || chooseLoadFileMode < 1 || chooseLoadFileMode > static_cast<int>(read_write_mode::MAX_OPTIONS)) // если предыдущее извлечение не выполнилось или произошло переполнение,
            {
                std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
                cout << "Error. Wrong input." << endl;
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
            mode = static_cast<read_write_mode>(chooseLoadFileMode - 1);
                break;
        }
        string tempStr;
    std::getline(fin, tempStr);  // Игнорируем шапку таблицы

    switch (mode)
    {
    case read_write_mode::REWRITE:
        if (staff.size() > 0)
            staff.clear();
        for (int i = 0; i < workersCount; ++i)
        {
            staff.push_back(Worker());
            staff[i].m_readFromFile(fin);
        }
        break;
    case read_write_mode::PUSH_BACK:
        for (int i = static_cast<int>(staff.size()), staffOldSize = static_cast<int>(staff.size()); i < staffOldSize + workersCount; ++i)
        {
            staff.push_back(Worker());
            staff[i].m_readFromFile(fin);
        }
        break;
    case read_write_mode::PUSH_FRONT:
        std::vector<Worker> staffCopy = std::move(staff);
        staff.clear();
        for (int i = 0; i < workersCount; ++i)
        {
            staff.push_back(Worker());
            staff[i].m_readFromFile(fin);
        }
        staff.insert(staff.end(), std::make_move_iterator(staffCopy.begin()), std::make_move_iterator(staffCopy.end()));
        break;
    }
    fin.close();
    findDuplicateIDs(staff, workersCount) ? cout << "File succesfully loaded (with warnings)." << endl : cout << "File succesfully loaded" << endl;
    for (Worker& n: staff)
         n.recalculateSalary();    
}
/*******************************************************************************************************************************************************/

int findDuplicateIDs(const std::vector<Worker>& staff, int workersCount, const bool edit, const int id) // Функция поиска повторяющихся ID. Аргументы по умолчанию edit=0 и id=-1 передаются только в режиме edit.  
{
    std::vector<int> arrID; // Копия ID всех работников
    for (int i = 0; i < workersCount; ++i) 
        arrID.push_back(staff[staff.size() - workersCount + i].getId());
    std::vector<int> duplicates; // Уникальные номера ID, имеющие повторения
    for (int i = 0; i < arrID.size(); ++i)
    {
        auto duplicateIDcount{ std::count(arrID.begin(), arrID.end(), arrID[i]) - 1 };  // Поиск повторений ID в копии вектора работников (общее кол-во экземпляров минус 1)
        if (duplicateIDcount > 0 && !std::count(duplicates.begin(), duplicates.end(), arrID[i]))   // Если есть повторения ID в копии вектора работников, но экземпляр ID еще не добавлен в базу дубликатов
        {
            if (edit == false)
                cout << "Warning! " << duplicateIDcount + 1 << " copies of ID " << arrID[i] << " found in loaded file. IDs must be unique." << endl;
            else if (extendedWarnings == 1)
                cout << "Warning! " << duplicateIDcount + 1 << " copies of ID " << arrID[i] << " found in worker list. IDs must be unique." << endl;
            duplicates.push_back(arrID[i]); // добавляем экземпляр ID в базу дубликатов
        }
    }
    if (duplicates.size() > 0 && edit == false && extendedWarnings == 1)
        cout << "Please edit IDs in your file and import data again, or program may not work properly." << endl;
    if (duplicates.size() > 0 && edit == true)
    {
        if (extendedWarnings == 1)
        cout << "Please change duplicate IDs, or program may not work properly." << endl;
        return static_cast<int>(std::count(arrID.begin(), arrID.end(), id)) - 1; // возврат количества ДУБЛИКАТОВ id переданного функцией edit в базе дубликатов
    }
    return static_cast<int>(duplicates.size());
}
/*******************************************************************************************************************************************************/

void sortWorkers(std::vector<Worker>& staff)
{
    while (1)
    {
        cout << "Select sort method\n";
        cout << "Sort in ascending order: 1 - ID, 2 - surname, 3 - post, 4 - h/pay, 5 - hours, 6 - salary" << endl;
        cout << "Sort in descending order: 10 - ID, 20 - surname, 30 - post, 40 - h/pay, 50 - hours, 60 - salary" << endl;
        int num;
        cin >> num;
        if (std::cin.fail()) // если предыдущее извлечение не выполнилось или произошло переполнение,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
            cout << "Error. Wrong input." << endl;
            continue;
        }
        if (num != 1 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6 && num != 10 && num != 20 && num != 30 && num != 40 && num != 50 && num != 60)
        {
            cout << "Error. Only 1, 2, 3, 4, 5, 6 (or 10, 20, 30, 40, 50, 60 for descending order) allowed." << endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(32767, '\n');
        switch (num)
        {
        case 1:
            std::sort(staff.begin(), staff.end(), Worker::sortByID);
            cout << "Sorted by ID " << staff.size() << " elements in ascending order" << endl;
            break;
        case 2:
            std::sort(staff.begin(), staff.end(), Worker::sortBySurname);
            cout << "Sorted by surname " << staff.size() << " elements in ascending order" << endl;
            break;
        case 3:
            std::sort(staff.begin(), staff.end(), Worker::sortByPost);
            cout << "Sorted by post " << staff.size() << " elements in ascending order" << endl;
            break;
        case 5:
            std::sort(staff.begin(), staff.end(), Worker::sortByHours);
            cout << "Sorted by hours " << staff.size() << " elements in ascending order" << endl;
            break;
        case 4:
            std::sort(staff.begin(), staff.end(), Worker::sortByPayPerHour);
            cout << "Sorted by h/pay " << staff.size() << " elements in ascending order" << endl;
            break;
        case 6:
            std::sort(staff.begin(), staff.end(), Worker::sortBySalary);
            cout << "Sorted by salary " << staff.size() << " elements in ascending order" << endl;
            break;
        case 10:
            std::sort(staff.begin(), staff.end(), Worker::sortByID_descending);
            cout << "Sorted by ID " << staff.size() << " elements in descending order" << endl;
            break;
        case 20:
            std::sort(staff.begin(), staff.end(), Worker::sortBySurname_descending);
            cout << "Sorted by surname " << staff.size() << " elements in descending order" << endl;
            break;
        case 30:
            std::sort(staff.begin(), staff.end(), Worker::sortByPost_descending);
            cout << "Sorted by post " << staff.size() << " elements in descending order" << endl;
            break;
        case 50:
            std::sort(staff.begin(), staff.end(), Worker::sortByHours_descending);
            cout << "Sorted by hours " << staff.size() << " elements in descending order" << endl;
            break;
        case 40:
            std::sort(staff.begin(), staff.end(), Worker::sortByPayPerHour_descending);
            cout << "Sorted by h/pay " << staff.size() << " elements in descending order" << endl;
            break;
        case 60:
            std::sort(staff.begin(), staff.end(), Worker::sortBySalary_descending);
            cout << "Sorted by salary " << staff.size() << " elements in descending order" << endl;
            break;
        }
        return;
    }
}
/*******************************************************************************************************************************************************/

operation_On_Worker FindMode_action_user_define()
{
    while (1)
    {
        cout << "1 - edit worker, 2 - delete worker, 0 - return to main menu" << endl;
        int chooseAction;
        // здесь был std::cin.ignore(32767, '\n') и он вызывал двойной запрос на ввод, как бы игнорируя первый ввод ??? ПОЧЕМУ???
        cin >> chooseAction;
        if (std::cin.fail() || chooseAction < 0 || chooseAction > 2) // если предыдущее извлечение не выполнилось или произошло переполнение, или введено значение вне диапазона
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
            cout << "Error. Wrong input." << endl;
            continue;
        }
        if (chooseAction == 1) // если введено 1, то то переходим на режим редактирования
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return operation_On_Worker::EDIT;
        }
        else if (chooseAction == 2) // если введено 2, то переходим на режим удаления
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return operation_On_Worker::DEL;
        }
        else // если введено 0, то ничего не делаем, выходим в главное меню
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return operation_On_Worker::FIND;
        }
    }
}
