#pragma once
#include "Worker.h"
enum class read_write_mode { REWRITE, PUSH_BACK, PUSH_FRONT, MAX_OPTIONS };
enum class operation_On_Worker { EDIT, FIND, DEL, MAX_OPTIONS };
void newWorker(std::vector<Worker>& staff);
void editWorker(std::vector<Worker>& staff, operation_On_Worker operation = operation_On_Worker::EDIT);
void printStaffTableHead();
void printStaff(std::vector<Worker>& staff);
void writeStaffToFile(std::vector<Worker>& staff);
void readStaffFromFile(std::vector<Worker>& staff); 
int findDuplicateIDs(const std::vector<Worker>& staff, int workersCount, const bool edit = false, const int id = -1);
void showMenu();
int nStrings(std::ifstream& fin);
bool stringInputValidation(std::string& s, const char* sign, bool edit = false);
bool intInputValidation(int& i, const char* sign, bool edit = false);
void sortWorkers(std::vector<Worker>& staff);
operation_On_Worker FindMode_action_user_define();
const bool extendedWarnings = 0;