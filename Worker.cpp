#include "Worker.h"
#include "main.h"

using std::cout; using std::cin; using std::endl; using std::string;

Worker::Worker(int id, std::string surname, std::string name, std::string patronymic, std::string post, int hours, int payPerHour) : \
m_id(id), m_surname(surname), m_name(name), m_patronymic(patronymic), m_post(post), m_hours(hours), m_payPerHour(payPerHour), m_salary(m_hours* m_payPerHour)
{

}

void Worker::m_print() const
{
    cout << std::setw(m_id_w) << std::left << m_id << std::setw(m_surname_w) << std::left << m_surname << std::setw(m_name_w) \
        << std::left << m_name << std::setw(m_patronymic_w) << std::left << m_patronymic << std::setw(m_post_w) << std::setfill('-') << std::left \
        << m_post << ' ' << std::setw(m_pph_w) << std::setfill(' ') << std::left << m_payPerHour << std::setw(m_hours_w) << std::left << m_hours \
        << std::setw(m_salary_w) << std::left << m_salary << endl;
}

void Worker::m_writeToFile(std::fstream& fout)
{
    fout << std::setw(m_id_w) << std::left << m_id << std::setw(m_surname_w) << std::left << m_surname << std::setw(m_name_w) \
        << std::left << m_name << std::setw(m_patronymic_w) << std::left << m_patronymic << std::setw(m_post_w) << std::left \
        << m_post << std::setw(m_pph_w) << std::left << m_payPerHour << std::setw(m_hours_w) << std::left << m_hours \
        << std::setw(m_salary_w) << std::left << m_salary << endl;
}

void Worker::m_readFromFile(std::ifstream& fin)
{
    fin >> m_id >> m_id >> m_surname >> m_name >> m_patronymic >> m_post >> m_payPerHour >> m_hours >> m_salary;
}
