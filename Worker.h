#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <filesystem>
#include <iterator>
#include <utility>
#include <algorithm>
using std::cout; using std::cin; using std::endl; using std::string;

class Worker
{
private:
    int m_id;
    std::string m_surname;
    std::string m_name;
    std::string m_patronymic;
    std::string m_post;
    int m_hours;
    int m_payPerHour;
    int m_salary;
public:
    Worker(int id = 0, std::string surname = "", std::string name = "", std::string patronymic = "", std::string post = "", int hours = 0, int payPerHour = 0);
    // Геттеры:
    const int getId() const { return m_id; }
    const std::string getSurname() const { return m_surname; }
    const std::string getName() const  { return m_name; }
    const std::string getPatronymic() const  { return m_patronymic; }
    const std::string getPost() const { return m_post; }
    const int getHours() const { return m_hours; }
    const int getPayPerHour() const { return m_payPerHour; }
    const int getSalary() const { return m_salary; }
    // Сеттеры:
    void setId(const int& id) { m_id = id; }
    void setSurname(const string& surname) { m_surname = surname; }
    void setName(const string& name) { m_name = name; }
    void setPatronymic(const string& patronymic) { m_patronymic = patronymic; }
    void setPost(const string& post) { m_post = post; }
    void setHours(const int& hours) { m_hours = hours; }
    void setPayPerHour(const int& pph) { m_payPerHour = pph; }
    void recalculateSalary() { m_salary = m_hours * m_payPerHour; }
    // Другие функции:
    void m_print() const;
    void m_writeToFile(std::fstream& fout);
    void m_readFromFile(std::ifstream& fin);
    // Размеры полей таблицы:
    static const int m_number_w = 7;
    static const int m_id_w = 8;
    static const int m_surname_w = 16;
    static const int m_name_w = 16;
    static const int m_patronymic_w = 16;
    static const int m_post_w = 27;
    static const int m_hours_w = 7;
    static const int m_pph_w = 8;
    static const int m_salary_w = 10;
    // Компараторы сортировки:
    static bool sortByID(Worker& a, Worker& b)         { return a.getId() < b.getId(); }
    static bool sortBySurname(Worker& a, Worker& b)    { return a.getSurname() < b.getSurname(); }
    static bool sortByPost(Worker& a, Worker& b)       { return a.getPost() < b.getPost(); }
    static bool sortByHours(Worker& a, Worker& b)      { return a.getHours() < b.getHours(); }
    static bool sortByPayPerHour(Worker& a, Worker& b) { return a.getPayPerHour() < b.getPayPerHour(); }
    static bool sortBySalary(Worker& a, Worker& b)     { return a.getSalary() < b.getSalary(); }
    static bool sortByID_descending(Worker& a, Worker& b)         { return a.getId() > b.getId(); }
    static bool sortBySurname_descending(Worker& a, Worker& b)    { return a.getSurname() > b.getSurname(); }
    static bool sortByPost_descending(Worker& a, Worker& b)       { return a.getPost() > b.getPost(); }
    static bool sortByHours_descending(Worker& a, Worker& b)      { return a.getHours() > b.getHours(); }
    static bool sortByPayPerHour_descending(Worker& a, Worker& b) { return a.getPayPerHour() > b.getPayPerHour(); }
    static bool sortBySalary_descending(Worker& a, Worker& b)     { return a.getSalary() > b.getSalary(); }

};