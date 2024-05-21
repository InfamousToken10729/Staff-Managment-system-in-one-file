#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
#define el "\n"
#define FileName "EmployeesData.txt"
#define ExcelFileName "EmployeesData.csv"

// ANSI escape codes for color
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

#ifdef _WIN32
#define CLEAR "cls"
#elif __unix__
#define CLEAR "clear"
#elif __APPLE__
#define CLEAR "clear"
#endif

struct CompanyPosition {
    string name;
    string abbreviation;
};

vector<CompanyPosition> Executive_Positions = {
    //Executive positions
    {"Chief Executive Officer", "CEO"},
    {"Chief Operating Officer", "COO"},
    {"Chief Financial Officer", "CFO"},
    {"Chief Marketing Officer", "CMO"},
    {"Chief Technology Officer", "CTO"},
    {"President", "President"},
    {"Vice President", "VP"}
};
vector<CompanyPosition> non_executive_positions = {
    //Managment positions
    {"General Manager", "GM"},
    {"Operaation Manager", "OM"},
    {"Human Resource Manger", "HR"},
    {"Marketing Manager", "MM"},
    {"Finance Manager", "FM"},
    {"Information Technology Manager", "IT"},
    {"Project Manager", "PM"},
    //Operational positions
    {"Sales Representative", "SR"},
    {"Customer Service Representative", "CSR"},
    {"Administrative Assistant", "AA"},
    {"Data Analyst", "DA"},
    {"Quality Control Inspector", "QCI"},
    {"Production Worker", "PW"}
};
vector<CompanyPosition> positions = {
    //Executive positions
    {"Chief Executive Officer", "CEO"},
    {"Chief Operating Officer", "COO"},
    {"Chief Financial Officer", "CFO"},
    {"Chief Marketing Officer", "CMO"},
    {"Chief Technology Officer", "CTO"},
    {"President", "President"},
    {"Vice President", "VP"},
    //Managment positions
    {"General Manager", "GM"},
    {"Operaation Manager", "OM"},
    {"Human Resource Manger", "HR"},
    {"Marketing Manager", "MM"},
    {"Finance Manager", "FM"},
    {"Information Technology Manager", "IT"},
    {"Project Manager", "PM"},
    //Operational positions
    {"Sales Representative", "SR"},
    {"Customer Service Representative", "CSR"},
    {"Administrative Assistant", "AA"},
    {"Data Analyst", "DA"},
    {"Quality Control Inspector", "QCI"},
    {"Production Worker", "PW"}
};

struct address {
    string street_name, near_by_landmarks;
    int building_number = 0; // Initialize building_number
    int floor_number = 0; // Initialize floor_number
    int apartment_number = 0; // Initialize apartment_number

    //functions for saving and retreving data from the .txt file
    void save(ofstream& outFile) {
        outFile << street_name << "\n" << near_by_landmarks << "\n";
        outFile << building_number << "\n" << floor_number << "\n" << apartment_number << "\n";
    }
    void load(ifstream& inFile) {
        getline(inFile, street_name);
        getline(inFile, near_by_landmarks);
        inFile >> building_number;
        inFile.ignore();
        inFile >> floor_number;
        inFile.ignore();
        inFile >> apartment_number;
        inFile.ignore();
    }
};
class Employee {
private:
    // Declare private member variables
    long long ID = 0;
    int age = 0; // Initialize age
    float salary = 0.0f; // Initialize salary
    string name, role;
    address home_address;

public:


    void save(ofstream& outFile) {
        outFile << ID << "\n" << name << "\n" << age << "\n";
        home_address.save(outFile);
        outFile << role << "\n" << salary << "\n";
    }
    void load(ifstream& inFile) {
        inFile >> ID;
        inFile.ignore();  // Ignore newline character
        getline(inFile, name);
        inFile >> age;
        inFile.ignore();  // Ignore newline character
        home_address.load(inFile);
        getline(inFile, role);
        inFile >> salary;
        inFile.ignore();  // Ignore newline character
    }
    // Default constructor
    Employee() {}

    // Parameterized constructor
    Employee(long long id, string n, int a, address home, string r, float s)
        : ID(id), name(n), age(a), home_address(home), role(r), salary(s) {}

    // Copy constructor
    Employee(const Employee& other)
        : ID(other.ID), name(other.name), age(other.age), home_address(other.home_address),
        role(other.role), salary(other.salary) {}


    // Define public getter methods
    long long get_id() const {
        return ID;
    }
    string get_name() const {
        return name;
    }
    int get_age() const {
        return age;
    }
    address get_home_address() const {
        return home_address;
    }
    string get_role() const {
        return role;
    }
    float get_salary() const {
        return salary;
    }

    // Define public setter methods
    void set_id(long long id) {
        ID = id;
    }
    void set_name(string n) {
        name = n;
    }
    void set_age(int a) {
        age = a;
    }
    void set_home_address(address home) {
        home_address = home;
    }
    void set_role(string r) {
        role = r;
    }
    void set_salary(float s) {
        salary = s;
    }

};

class SalaryCalculator {
private:
    float salary, net_salary;
    int working_months;

public:
    SalaryCalculator() {
        salary = 0.0f;
        net_salary = 0.0f;
        working_months = 12;
    }

    void set_salary(float s) {
        salary = s;
    }

    float calculate_salary() {
        net_salary = salary * working_months;
        return net_salary;
    }
};

void saveData(vector<Employee>& employees, const string& filename) {
    ofstream outFile(filename);
    for (Employee& employee : employees) {
        employee.save(outFile);
    }
    outFile.close();
}

// Function to restore data from a file and resave it in the vector
void restoreData(vector<Employee>& employees, const string& filename) {
    ifstream inFile(filename);
    Employee employee;
    while (inFile.peek() != EOF) {
        employee.load(inFile);
        employees.push_back(employee);
    }
    inFile.close();
}

// Function to save the data into an excel file for ease of use to the user
void saveExcel(const vector<Employee>& employees, const string& filename) {
    SalaryCalculator salary_calculator;
    ofstream outFile(filename);
    outFile << "Employee Number,ID,Name,Age,Street Name,Nearby Landmark,Building Number,Floor Number,Apartment Number,Role,Salary,Yearly Salary\n";
    // Write the headers
    for (size_t i = 0; i < employees.size(); ++i) {
        const Employee& employee = employees[i];
        salary_calculator.set_salary(employee.get_salary());
        outFile << i + 1 << ","
            << employee.get_id() << ","
            << employee.get_name() << ","
            << employee.get_age() << ","
            << employee.get_home_address().street_name << ","
            << employee.get_home_address().near_by_landmarks << ","
            << employee.get_home_address().building_number << ","
            << employee.get_home_address().floor_number << ","
            << employee.get_home_address().apartment_number << ","
            << employee.get_role() << ","
            << fixed << setprecision(2) << employee.get_salary() << ","
            << fixed << setprecision(2) << salary_calculator.calculate_salary() << "\n";
    }
    outFile.close();
}

// Define the Database class
class Database
{
protected:
    static vector<Employee> Employees_data; // Initialize the static member
    address display_address_temp;

public:

    //Setting function
    void add_employee(Employee new_Employee) {
        Employees_data.push_back(new_Employee);
        display_address_temp = new_Employee.get_home_address();

    }

    //Search functions
    int find_employee_by_id(long long search_id) {
        for (int i = 0; i < Employees_data.size(); i++) {
            if (Employees_data[i].get_id() == search_id) {
                return i; // return the index of the Employee object
            }
        }
        return -1; // return -1 if no employee found
    }
    int find_employee_by_name(string search_name) {
        // Convert search_name to lower case
        transform(search_name.begin(), search_name.end(), search_name.begin(),
            [](unsigned char c) { return tolower(c); });

        for (int i = 0; i < Employees_data.size(); i++) {
            string employee_name = Employees_data[i].get_name();
            // Convert employee_name to lower case
            transform(employee_name.begin(), employee_name.end(), employee_name.begin(),
                [](unsigned char c) { return tolower(c); });

            if (employee_name == search_name) {
                return i; // return the index of the Employee object
            }
        }
        return -1; // return -1 if no employee found
    }
    int find_employee_by_role(string search_role) {
        // Convert search_role to lower case
        transform(search_role.begin(), search_role.end(), search_role.begin(),
            [](unsigned char c) { return tolower(c); });

        for (int i = 0; i < Employees_data.size(); i++) {
            string employee_role = Employees_data[i].get_role();
            // Convert employee_role to lower case
            transform(employee_role.begin(), employee_role.end(), employee_role.begin(),
                [](unsigned char c) { return tolower(c); });

            if (employee_role == search_role) {
                return i; // return the index of the Employee object
            }
        }
        return -1; // return -1 if no employee with the specified role was found
    }
    vector<Employee> find_employees_with_high_wage() {
        // Create a new vector to store employees with high wage
        vector<Employee> employees_with_highwage;

        // Loop through all employees
        for (int i = 0; i < Employees_data.size(); i++) {
            // Check if the employee's salary is higher than 20,000
            if (Employees_data[i].get_salary() >= 20000) {
                // If so, add the employee to the high wage vector
                employees_with_highwage.push_back(Employees_data[i]);
            }
        }

        // Return the vector of employees with high wage
        return employees_with_highwage;
    }

    //Retrive data function
    Employee retrive_data(int index) {
        Employee retrived_data = Employees_data[index];
        return retrived_data;
    }

    //Delete function
    void delete_employee(int index) {
        Employees_data.erase(Employees_data.begin() + index);
    }

    //Edit functions
    void edit_employee_details(int id) {
        int index = find_employee_by_id(id);
        if (index != -1) {
            cout << "Enter new name: ";
            string new_name;
            getline(cin, new_name);
            cout << "Enter new role: ";
            string new_role;
            getline(cin, new_role);
            cout << "Enter new age: ";
            int new_age;
            cin >> new_age;
            cout << "Enter new salary: ";
            float new_salary;
            cin >> new_salary;
            cout << "Enter new home address: ";
            address new_home_address;
            if (cin.rdbuf()->in_avail())
                cin.ignore(numeric_limits<streamsize>::max(), '\n');


            // Update employee data
            Employees_data[index].set_name(new_name);
            Employees_data[index].set_age(new_age);
            Employees_data[index].set_home_address(new_home_address);
            Employees_data[index].set_role(new_role);
            Employees_data[index].set_salary(new_salary);
        }
    }
    void set_new_ID(long long id, int index) {
        Employees_data[index].set_id(id);
    }
    void set_new_name(string name, int index) {
        Employees_data[index].set_name(name);
    }
    void set_new_age(int age, int index) {
        Employees_data[index].set_age(age);
    }
    void set_new_address(address home_address, int index) {
        Employees_data[index].set_home_address(home_address);
    }
    void set_new_role(string role, int index) {
        Employees_data[index].set_role(role);
    }
    void set_new_salary(float salary, int index) {
        Employees_data[index].set_salary(salary);
    }

    //save data to external files
    void save_data_to_file() {
        saveData(Employees_data, FileName);
    }
    void save_data_to_excel() {
        saveExcel(Employees_data, ExcelFileName);
    }

    //Retrive data from external files
    void restore_data_from_file() {
        restoreData(Employees_data, FileName);
    }


};

class Input_Handler {
private:
    string input;
public:
    string get_input() {
        input = "0"; //reset input value
        getline(cin, input);
        return input;
    }
};

class Out_Put_Handler {
    Database data;
    Employee display_employee_data;
    address display_address_data;
    SalaryCalculator salary_calculator;
public:
    void display_menu() {
        system(CLEAR);
        cout << "Staff Management System" << el << el;
        cout << "====================================================" << el;
        cout << YELLOW << "\t\t   Main Menu" << RESET << el;
        cout << "====================================================" << el;
        cout << GREEN << "1. Add New Employee." << RESET << el;
        cout << BLUE << "2. Edit Employee data." << RESET << el;
        cout << CYAN << "3. Search Employee. " << RESET << el;
        cout << MAGENTA << "4. Search Employee with high wage. (20,000 per month or higher) " << RESET << el;
        cout << RED << "5. Delete Employee data." << RESET << el;
        cout << GREEN << "6. Save Employee data to external files." << RESET << el;
        cout << RED << "7. Exit Program." << RESET << el;
    }

    // Display employee(s) details
    void display_employee_details(int index) {
        system(CLEAR);

        // Retrieve the employee data using the provided index
        display_employee_data = data.retrive_data(index);

        // Retrieve the address data from the employee data
        display_address_data = display_employee_data.get_home_address();

        // Print the employee details in a table-like structure with lines separating each information
        cout << "----------------------------------------" << el;
        cout << left << setw(20) << "ID:" << display_employee_data.get_id() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Name:" << display_employee_data.get_name() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Age:" << display_employee_data.get_age() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Street:" << display_address_data.street_name << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Nearby landmarks:" << display_address_data.near_by_landmarks << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Building Number:" << display_address_data.building_number << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Floor Number:" << display_address_data.floor_number << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Apartment Number:" << display_address_data.apartment_number << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Role:" << display_employee_data.get_role() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Salary:" << fixed << setprecision(2) << display_employee_data.get_salary() << el << "----------------------------------------" << el;
        salary_calculator.set_salary(display_employee_data.get_salary());
        cout << left << setw(20) << "Yearly Salary:" << fixed << setprecision(2) << salary_calculator.calculate_salary() << el << "----------------------------------------" << el;
    }
    void display_employee_details(vector<Employee> employees) {
        system(CLEAR);
        cout << "----------------------------------------" << el;
        // Loop through the employees vector and print the details of each employee
        for (int i = 0; i < employees.size(); i++) {
            // Print the title for each employee
            cout << "Employee " << (i + 1) << el;
            cout << "------------------" << el;

            // Print the employee details in a table-like structure
            cout << left << setw(20) << "ID:" << employees[i].get_id() << el;
            cout << "----------------------------------------" << el;
            cout << left << setw(20) << "Name:" << employees[i].get_name() << el;
            cout << "----------------------------------------" << el;
            cout << left << setw(20) << "Age:" << employees[i].get_age() << el;
            cout << "----------------------------------------" << el;

            // Get the address data from the employee
            address display_address_data = employees[i].get_home_address();

            // Print the address details
            cout << left << setw(20) << "Street:" << display_address_data.street_name << el;
            cout << "----------------------------------------" << el;
            cout << left << setw(20) << "Nearby landmarks:" << display_address_data.near_by_landmarks << el;
            cout << "----------------------------------------" << el;
            cout << left << setw(20) << "Building Number:" << display_address_data.building_number << el;
            cout << "----------------------------------------" << el;
            cout << left << setw(20) << "Floor Number:" << display_address_data.floor_number << el;
            cout << "----------------------------------------" << el;
            cout << left << setw(20) << "Apartment Number:" << display_address_data.apartment_number << el;
            cout << "----------------------------------------" << el;

            // Print the remaining employee details
            cout << left << setw(20) << "Role:" << employees[i].get_role() << el;
            cout << "----------------------------------------" << el;
            cout << left << setw(20) << "Salary:" << fixed << setprecision(2) << employees[i].get_salary() << el;

            // Separate each employee with two lines
            cout << "========================================" << el;
            cout << el;
        }
    }
    void display_employee_for_save(Employee display_data) {
        system(CLEAR);
        cout << "----------------------------------------" << el;
        cout << left << setw(20) << "ID:" << display_data.get_id() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Name:" << display_data.get_name() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Age:" << display_data.get_age() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Street:" << display_data.get_home_address().street_name << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Nearby landmarks:" << display_data.get_home_address().near_by_landmarks << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Building Number:" << display_data.get_home_address().building_number << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Floor Number:" << display_data.get_home_address().floor_number << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Apartment Number:" << display_data.get_home_address().apartment_number << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Role:" << display_data.get_role() << el << "----------------------------------------" << el;
        cout << left << setw(20) << "Salary:" << fixed << setprecision(2) << display_data.get_salary() << el << "----------------------------------------" << el;
    }
};

class Employee_Validator {
    int search_result = 0;
    Database search;

public:
    //Validate Inputs
    int validate_id(const string& ID_check) {
        try {
            long long ID = stoll(ID_check);  // Convert input to long long
            if (ID < 0 || ID > 10000000000) {
                return 1;  // Invalid input (large number)
            }
            // Assuming `find_employee_by_id` exists in the `Database` class
            if (search.find_employee_by_id(ID) != -1) {
                return 2;  // ID found
            }
            return 0;  // No error
        }
        catch (const invalid_argument&) {
            if (check_exit(ID_check) == true) {
                return -1;  // User entered "exit"
            }
            return 1;  // Invalid input
        }
        catch (const out_of_range&) {
            return 1;  // Invalid input (out of range)
        }
    }
    int validate_name(string name_check) {
        if (check_exit(name_check) == true) {
            return -1;
        }
        else if (search.find_employee_by_name(name_check) != -1) {
            return 2;
        }
        else {
            return 0;
        }
    }
    int validate_age(const string& age_check) {
        try {
            int age = stoi(age_check);  // Convert input to integer
            if (age < 16 || age > 120) {
                return 1;  // Invalid input (outside valid range)
            }
            else {
                return 0;  // No error
            }
        }
        catch (const invalid_argument&) {
            if (check_exit(age_check) == true) {
                return -1;  // User entered "exit"
            }
            return 1;  // Invalid input
        }
        catch (const out_of_range&) {
            return 1;  // Invalid input (out of range)
        }
    }
    int validate_home_address(const string& check_street, const string& check_nearby_landmark,
        const string& check_building_number, const string& check_floor_num,
        const string& check_appart_num) {
        try {
            // Convert building number to an integer
            int building_number = stoi(check_building_number);

            // Convert floor number to an integer
            int floor_number = stoi(check_floor_num);

            // Convert apartment number to an integer
            int apartment_number = stoi(check_appart_num);

            return 0;  // No error
        }
        catch (const invalid_argument&) {
            if (check_exit(check_building_number) == true || check_exit(check_floor_num) == true || check_exit(check_appart_num) == true == true) {
                return -1;  // User entered "exit"
            }
            return 1;  // Invalid input
        }
        catch (const out_of_range&) {
            return 1;  // Invalid input (out of range)
        }
    }
    int validate_role(const string& role_check) {
        if (check_exit(role_check) == true) {
            return -1; // Return to main menu
        }

        // Convert user input to lowercase for case-insensitive comparison
        string lowercase_input = role_check;
        transform(lowercase_input.begin(), lowercase_input.end(), lowercase_input.begin(), ::tolower);

        for (const auto& position : positions) {
            // Convert both position name and abbreviation to lowercase for comparison
            string lowercase_position_name = position.name;
            string lowercase_position_abbreviation = position.abbreviation;
            transform(lowercase_position_name.begin(), lowercase_position_name.end(), lowercase_position_name.begin(), ::tolower);
            transform(lowercase_position_abbreviation.begin(), lowercase_position_abbreviation.end(), lowercase_position_abbreviation.begin(), ::tolower);

            if (lowercase_position_name == lowercase_input || lowercase_position_abbreviation == lowercase_input) {
                // Check if the role is an executive role
                for (const auto& executive_position : Executive_Positions) {
                    string lowercase_executive_position_name = executive_position.name;
                    string lowercase_executive_position_abbreviation = executive_position.abbreviation;
                    transform(lowercase_executive_position_name.begin(), lowercase_executive_position_name.end(), lowercase_executive_position_name.begin(), ::tolower);
                    transform(lowercase_executive_position_abbreviation.begin(), lowercase_executive_position_abbreviation.end(), lowercase_executive_position_abbreviation.begin(), ::tolower);

                    if (lowercase_executive_position_name == lowercase_input || lowercase_executive_position_abbreviation == lowercase_input) {
                        // Call find_employee_by_role and check if an employee exists
                        search_result = search.find_employee_by_role(role_check);
                        if (search_result != -1) {
                            return 2; //Role found
                        }

                    }
                }
                return 0; // Validation passed successfully
            }
        }
        return 1; // Return error
    }
    int validate_salary(string salary_check) {
        try {
            long long salary = stoll(salary_check);  // Convert input to long long
            if (salary < 0 || salary > 10000000) {
                return 1;  // Invalid input (large number)
            }
            // Assuming `find_employee_by_id` exists in the `Database` class
            return 0;  // No error
        }
        catch (const invalid_argument&) {
            if (check_exit(salary_check) == true) {
                return -1;  // User entered "exit"
            }
            return 1;  // Invalid input
        }
        catch (const out_of_range&) {
            return 1;  // Invalid input (out of range)
        }
    }

    //Validate specific roles
    int validate_executive_role(const string& role_check) {
        if (check_exit(role_check) == true) {
            return -1; // Return to main menu
        }

        // Convert user input to lowercase for case-insensitive comparison
        string lowercase_input = role_check;
        transform(lowercase_input.begin(), lowercase_input.end(), lowercase_input.begin(), ::tolower);

        for (const auto& executive_position : Executive_Positions) {
            // Convert both position name and abbreviation to lowercase for comparison            
            string lowercase_executive_position_abbreviation = executive_position.abbreviation;
            transform(lowercase_executive_position_abbreviation.begin(), lowercase_executive_position_abbreviation.end(), lowercase_executive_position_abbreviation.begin(), ::tolower);

            if (lowercase_executive_position_abbreviation == lowercase_input) {
                // Call find_employee_by_role and check if an employee exists
                search_result = search.find_employee_by_role(role_check);
                if (search_result != -1) {
                    return 2; //Role found
                }
                else if (search_result == -1) {
                    return 3; //No employee where found with such role
                }
            }
        }
        return 1; // Return error
    }
    int validate_non_executive_role(const string& role_check) {
        if (check_exit(role_check) == true) {
            return -1; // Return to main menu
        }

        // Convert user input to lowercase for case-insensitive comparison
        string lowercase_input = role_check;
        transform(lowercase_input.begin(), lowercase_input.end(), lowercase_input.begin(), ::tolower);

        for (const auto& non_executive_position : non_executive_positions) {
            // Convert both position name and abbreviation to lowercase for comparison
            string lowercase_non_executive_position_abbreviation = non_executive_position.abbreviation;
            transform(lowercase_non_executive_position_abbreviation.begin(), lowercase_non_executive_position_abbreviation.end(), lowercase_non_executive_position_abbreviation.begin(), ::tolower);

            if (lowercase_non_executive_position_abbreviation == lowercase_input) {
                // Call find_employee_by_role and check if an employee exists
                search_result = search.find_employee_by_role(role_check);
                if (search_result != -1) {
                    return 2; //Role found
                }
                return 0; // Validation passed successfully
            }
        }
        return 1; // Return error
    }

    //validate specific inputs
    int validate_int(string check_int) {
        try {
            long long input_to_int = stoll(check_int);  // Convert input to long long
            if (input_to_int < 0 || input_to_int > 1000000) {
                return 1;  // Invalid input (large number)
            }
            return 0;  // No error
        }
        catch (const invalid_argument&) {
            if (check_exit(check_int) == true) {
                return -1;  // User entered "exit"
            }
            return 1;  // Invalid input
        }
        catch (const out_of_range&) {
            return 1;  // Invalid input (out of range)
        }
    }
    bool check_exit(const string& input) {
        // Create a copy of the input string
        string lower_input = input;

        // Convert the copy to lower case
        transform(lower_input.begin(), lower_input.end(), lower_input.begin(), ::tolower);

        // Check if the lower case string is "exit"
        if (lower_input == "exit") {
            return true;
        }
        else {
            return false;
        }
    }
    bool highwage_stat(const vector<Employee>& employees) {
        // Check if the vector is empty
        if (employees.empty()) {
            return false;
        }
        else {
            return true;
        }
    }
};

vector<Employee> Database::Employees_data;

class Menu : public Out_Put_Handler {

protected:
    Input_Handler user_input;
    Employee_Validator validate_input;
    Database employee_database;
    Employee New_employee, collected_data, Edited_employee;

    //Addresss
    address new_employee_addresss, edit_employee_addresss, collected_data_address;

    //temp variables
    string temp_street_name, temp_near_by_landmarks, temp_building_num, temp_floor_num, temp_apart_num, input;

    int validate_state = 0;

public:
    void select_option() {
        int option;
        // Validate user input
        while (!(cin >> option) || option < 1 || option > 7) {
            cout << "Invalid choice. Please enter a valid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Switch case to handle different options
        switch (option) {
        case 1: {
            cout << "Add New Employee selected";
            execute_option(1);
            break;
        }
        case 2: {
            cout << "Edit Employee Data selected";
            execute_option(2);
            break;
        }
        case 3: {
            cout << "Search Employee selected";
            execute_option(3);
            break;
        }
        case 4: {
            cout << "Search Employee with High Wage selected";
            execute_option(4);
            break;
        }
        case 5: {
            cout << "Delete Employee Data selected";
            execute_option(5);
            break;
        }
        case 6: {
            execute_option(6);
            break;
        }
        case 7: {
            execute_option(7);
            break; }
        }
    }
    void execute_option(int choice) {
        switch (choice) {
            //Add new employee
        case 1: {
            system(CLEAR);
            cin.ignore();
            cout << "Adding new Employee Data" << el;
            New_employee = collect_data();

            cout << "Employee Data " << el;
            display_employee_for_save(New_employee);
            cout << "Are you sure you want to save this data?" << el;
            cout << GREEN << "Y/yes" << el;
            cout << RED << "N/no" << RESET << el;

            string option;
            while (true) {
                getline(cin, option);
                transform(option.begin(), option.end(), option.begin(), ::tolower); // convert to lowercase

                if (option == "y" || option == "yes") {
                    //saving new employee data in database
                    employee_database.add_employee(New_employee);

                    //Confirmation to return to the main menu by pressing enter
                    cout << "Employee data saved successfully!" << el << "press enter to return to the menu." << el;
                    string status;
                    getline(cin, status);
                    break;
                }
                else if (option == "n" || option == "no") {
                    break;
                }
                else {
                    cout << "Invalid choice. Please enter Y/yes or N/no.\n";
                }
            }
            break;
        }

              //Edit Employee Data 
        case 2: {
            system(CLEAR);
            cout << "Editing Employee Data: " << el;

            //look for the ID to edit
            cin.ignore();
            cout << "Enter employee ID you want to edit or tpye \"exit\" to return to the main menu" << el;
            while (1) {
                validate_state = 0; //reset validate_state
                input = user_input.get_input();
                validate_state = validate_input.validate_id(input);
                if (validate_state == 0) {
                    cout << "ID not found, please enter a valid id or type \"exit\" to return to the main menu" << el;
                }
                else if (validate_state == -1) {
                    display_menu();
                    select_option();
                }
                else if (validate_state == 1) {
                    cout << "Invalid input, please enter a valid ID or exit to return to the main menu!" << el;
                }
                else if (validate_state == 2) {
                    cout << "ID Found!" << el;
                    break;
                }
            }

            //get employee index
            int index = employee_database.find_employee_by_id(stoll(input));

            //display edit options
            system(CLEAR);
            cout << "what do you want to edit?" << el;
            cout << "1. ID" << el;
            cout << "2. Name" << el;
            cout << "3. Age" << el;
            cout << "4. Address" << el;
            cout << "5. Role" << el;
            cout << "6. Salary" << el;
            cout << "7. All info" << el;
            cout << "8. Return to main menu" << el;

            int edit_option;

            while (!(cin >> edit_option) || edit_option < 1 || edit_option > 8) {
                cout << "Invalid choice. Please enter a valid input.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (edit_option) {

                //Edit Employee ID
            case 1: {
                system(CLEAR);
                cin.ignore();
                cout << "Editing Employee ID" << el;
                long long ID = collect_ID();
                employee_database.set_new_ID(ID, index);
                break;
            }

                  //Edit Employee Name
            case 2: {
                system(CLEAR);
                cin.ignore();
                cout << "Editing Employee Name" << el;
                string name = collect_name();
                employee_database.set_new_name(name, index);
                break;
            }

                  //Edit Employee Age
            case 3: {
                system(CLEAR);
                cin.ignore();
                cout << "Editing Employee Age" << el;
                int age = collect_age();
                employee_database.set_new_age(age, index);
                break;
            }

                  //Edit Employee Address
            case 4: {
                system(CLEAR);
                cin.ignore();
                cout << "Editing Employee Address" << el;
                address new_employee_addresss = collect_address();
                employee_database.set_new_address(new_employee_addresss, index);
                break;
            }

                  //Edit Employee Role
            case 5: {
                system(CLEAR);
                cin.ignore();
                cout << "Editing Employee Role" << el;
                string role = collect_role();
                employee_database.set_new_role(role, index);
                break;
            }

                  //Edit Employee Salary
            case 6: {
                system(CLEAR);
                cin.ignore();
                cout << "Editing Employee Salary" << el;
                float salary = collect_salary();
                employee_database.set_new_salary(salary, index);
                break;
            }

                  //Edit All Employee Info
            case 7: {
                system(CLEAR);
                cin.ignore();
                cout << "Editing All Employee Info" << el;
                //getting edited employee data
                Edited_employee = collect_data();
                //sending edited data to database to be saved
                employee_database.set_new_ID(Edited_employee.get_id(), index);
                employee_database.set_new_name(Edited_employee.get_name(), index);
                employee_database.set_new_age(Edited_employee.get_age(), index);
                employee_database.set_new_address(Edited_employee.get_home_address(), index);
                employee_database.set_new_role(Edited_employee.get_role(), index);
                employee_database.set_new_salary(Edited_employee.get_salary(), index);
                break;
            }

                  //Return to main menu                  
            case 8: {
                display_menu();
                select_option();
                break;
            }
            }
            break;
        }

              //search employee
        case 3: {
            system(CLEAR);
            cout << "Searching Employee data" << el;
            cout << "Search Employee by: " << el;
            cout << "1. ID" << el;
            cout << "2. Name" << el;
            cout << "3. Role \"executive role ONLY\" " << el;
            cout << "4. Return to main menu" << el;

            int search_option;
            while (!(cin >> search_option) || search_option < 1 || search_option > 4) {
                cout << "Invalid choice. Please enter a valid input." << el;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (search_option) {

                //search employee by ID
            case 1: {
                system(CLEAR);
                cin.ignore();
                cout << "Enter employee ID you want to search or type \"exit\" to return to the main menu" << el;
                while (true) {
                    validate_state = 0; //reset validate_state
                    input = user_input.get_input();
                    validate_state = validate_input.validate_id(input);
                    if (validate_state == 0) {
                        cout << "ID not found, please enter a valid id or type \"exit\" to return to the main menu" << el;
                    }
                    else if (validate_state == -1) {
                        display_menu();
                        select_option();
                    }
                    else if (validate_state == 1) {
                        cout << "Invalid input, please enter a valid ID or exit to return to the main menu!" << el;
                    }
                    else if (validate_state == 2) {
                        break;
                    }
                }
                int index = employee_database.find_employee_by_id(stoll(input));
                display_employee_details(index);
                cout << "press enter to return to the menu." << el;
                string status;
                getline(cin, status);
                break;

            }

                  //search employee by Name
            case 2: {
                system(CLEAR);
                cin.ignore();
                cout << "Enter employee Name you want to search or tpye \"exit\" to return to the main menu" << el;
                while (true) {
                    validate_state = 0; //reset validate_state
                    input = user_input.get_input();
                    validate_state = validate_input.validate_name(input);
                    if (validate_state == 0) {
                        cout << "Name not found, please enter a valid name or type \"exit\" to return to the main menu" << el;
                    }
                    else if (validate_state == -1) {
                        display_menu();
                        select_option();
                    }
                    else if (validate_state == 1) {
                        cout << "Invalid input, please enter a valid Name or type \"exit\" to return to the main menu!" << el;
                    }
                    else if (validate_state == 2) {
                        cout << "Name have been found!" << el;
                        break;
                    }
                }
                int index = employee_database.find_employee_by_name(input);
                display_employee_details(index);
                cout << "press enter to return to the menu." << el;
                string status;
                getline(cin, status);
                break;
            }

                  //search employee by Role
            case 3: {
                system(CLEAR);
                cin.ignore();
                cout << "---------------------------------------------------" << el;
                cout << "| Title                            | Abbreviation |" << el;
                cout << "---------------------------------------------------" << el;

                // Display Executive Positions
                cout << "Executive Roles:" << el;
                for (const auto& pos : Executive_Positions) {
                    cout << "| " << left << setw(32) << pos.name << " | " << setw(12) << pos.abbreviation << " |" << el;
                }
                cout << "---------------------------------------------------" << el;
                cout << "Enter employee role you want to search or type \"exit\" to return to the main menu" << el;
                while (true) {
                    validate_state = 0; //reset validate_state
                    input = user_input.get_input();

                    // Check if the role is a non-executive role
                    validate_state = validate_input.validate_non_executive_role(input);
                    if (validate_state == 0 /*Role entered is a non-executive role*/) {
                        cout << "Role entered is a non-executive role, please enter an executive role or type \"exit\" to return to the main menu" << el;
                        continue;
                    }

                    // Check if the role is an executive role
                    validate_state = validate_input.validate_executive_role(input);
                    if (validate_state == 3) {
                        cout << "No employee with such role where found, please enter a valid executive role or type \"exit\" to return to the main menu" << el;
                    }
                    else if (validate_state == -1) {
                        display_menu();
                        select_option();
                    }
                    else if (validate_state == 1) {
                        cout << "Invalid input, please enter a valid executive role or type \"exit\" to return to the main menu!" << el;
                    }
                    else if (validate_state == 2) {
                        cout << "Role has been found!" << el;
                        break;
                    }
                }
                cout << validate_state << el;
                cout << input << el;
                int index = employee_database.find_employee_by_role(input);
                display_employee_details(index);
                cout << "Press enter to return to the menu." << el;
                string status;
                getline(cin, status);
                break;
            }

                  //return to main menu
            case 4: {
                display_menu();
                select_option();
                break;
            }
            }

            break;

        }

              //search employee with high wage
        case 4: {
            cout << "Searching Employee with High Wage" << el;
            vector<Employee> high_wage_employees = employee_database.find_employees_with_high_wage();
            validate_state = validate_input.highwage_stat(high_wage_employees);
            if (validate_state == 1) {
                display_employee_details(high_wage_employees);
            }
            else if (validate_state == 0) {
                cout << "No employee with high wage found!" << el;
            }
            cout << "press enter to return to the menu." << el;
            string status;
            cin.ignore();
            getline(cin, status);


            break;
        }

              //delete employee data
        case 5: {
            system(CLEAR);
            cin.ignore();
            cout << "Deleting Employee data" << el;
            cout << "Enter employee ID you want to delete or type \"exit\" to return to the main menu" << el;
            while (1) {
                validate_state = 0; //reset validate_state
                input = user_input.get_input();
                validate_state = validate_input.validate_id(input);
                if (validate_state == 0) {
                    cout << RED << "ID not found, please enter a valid id or type \"exit\" to return to the main menu" << RESET << el;
                }
                else if (validate_state == -1) {
                    display_menu();
                    select_option();
                }
                else if (validate_state == 1) {
                    cout << RED << "Invalid input, please enter a valid ID or exit to return to the main menu!" << RESET << el;
                }
                else if (validate_state == 2) {
                    break;
                }
            }
            system(CLEAR);
            //get index of employee to be deleted
            int index = employee_database.find_employee_by_id(stoll(input));
            //print employee data to be deleted
            display_employee_details(index);

            //confirmation to delete employee data
            cout << "Are you sure you want to delete employee with id: " << input << "?" << el;
            cout << RED << "Warning: This action CANNOT be reverted!" << RESET << el;
            string option;
            cout << "Y/yes" << el << "N/no" << el;
            while (true) {
                getline(cin, option);
                transform(option.begin(), option.end(), option.begin(), ::tolower); // convert to lowercase

                if (option == "y" || option == "yes") {
                    employee_database.delete_employee(employee_database.find_employee_by_id(stoll(input)));
                    cout << "Employee data deleted successfully!" << el << "press enter to return to the menu." << el;
                    string status;
                    getline(cin, status);
                    break;
                }
                else if (option == "n" || option == "no") {
                    display_menu();
                    select_option();
                    break;
                }
                else {
                    cout << "Invalid choice. Please enter Y/yes or N/no.\n";
                }
            }
            break;
        }

              //save employee data to external files
        case 6: {
            system(CLEAR);
            cout << "Are you sure you want to save employee data to external files?" << el;
            cout << GREEN << "Y/yes" << el;
            cout << RED << "N/no" << RESET << el;
            string option;
            cin.ignore();
            while (true) {
                getline(cin, option);
                transform(option.begin(), option.end(), option.begin(), ::tolower);

                if (option == "y" || option == "yes") {
                    employee_database.save_data_to_file();
                    employee_database.save_data_to_excel();
                    cout << "Employee data saved to external files successfully!" << el << "press enter to return to the menu." << el;
                    string status;
                    getline(cin, status);
                    break;
                }
                else if (option == "n" || option == "no") {
                    display_menu();
                    select_option();
                    break;
                }
                else {
                    cout << "Invalid choice. Please enter Y/yes or N/no.\n";
                }
            }
            break;
        }

              //exit program
        case 7: {
            exit_system();
            display_menu();
            select_option();
        }
        }

        //return to the main menu after option have been executed
        display_menu();
        select_option();
    }
    void exit_system() {
        // Clear the console and display the exit message
        system(CLEAR);
        cout << "Staff Management Program" << el << el;
        cout << "Are you sure you want to exit the program?" << el << RED << "Y/yes" << el << GREEN << "N/no" << RESET << el;

        string option;

        // Validate the user's choice
        while (true) {
            cin >> option;
            transform(option.begin(), option.end(), option.begin(), ::tolower); // Convert to lowercase

            if (option == "y" || option == "yes" || option == "n" || option == "no") {
                break;
            }
            else {
                cout << "Invalid choice. Please enter a valid input." << el;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Switch case to handle the user's choice
        if (option == "n" || option == "no") {
            // If the user chooses not to exit, return to the main menu
            return;
        }
        else if (option == "y" || option == "yes") {
            // If the user chooses to exit, display the credits and exit the program
            employee_database.save_data_to_file();
            employee_database.save_data_to_excel();
            system(CLEAR);
            cout << "Program made by:" << el << "Mahmoud Ahmed\tID: 234051" << el << "Ahmed Hussein\tID: 225381" << el << el << "press enter to exit the program" << el;
            string status;
            cin.ignore();
            getline(cin, status);
            exit(1);
        }
    }

    //collect employee data
    Employee collect_data() {
        Employee collected_data;
        collected_data.set_id(collect_ID());
        collected_data.set_name(collect_name());
        collected_data.set_age(collect_age());
        collected_data.set_home_address(collect_address());
        collected_data.set_role(collect_role());
        collected_data.set_salary(collect_salary());
        return collected_data;
    }
    //collect and validate ID
    long long collect_ID() {
        cout << "Enter ID or type \"exit\" to return to the main menu!" << el;
        while (1) {
            validate_state = 0; //reset validate_state
            input = user_input.get_input();
            validate_state = validate_input.validate_id(input);
            if (validate_state == 0) {
                break;
            }
            else if (validate_state == -1) {
                display_menu();
                select_option();
            }
            else if (validate_state == 1) {
                cout << RED << "Invalid input, please enter a valid ID or exit to return to the main menu!" << RESET << el;
            }
            else if (validate_state == 2) {
                cout << RED << "ID is already taken, please enter a new ID!" << RESET << el;
            }
        }
        long long ID = stoll(input);
        return ID;
    }
    //collect and validate Name
    string collect_name() {
        cout << "Enter Employee Name or type \"exit\" to return to the main menu!" << el;
        while (1) {
            validate_state = 0; //reset validate_state
            input = user_input.get_input();

            // Check if the input is empty
            if (input.empty()) {
                cout << RED << "Input cannot be empty, please enter a Name!" << RESET << el;
                continue;
            }

            validate_state = validate_input.validate_name(input);
            if (validate_state == 0) {
                break;
            }
            else if (validate_state == -1) {
                display_menu();
                select_option();
            }
            else if (validate_state == 2) {
                cout << RED << "Name already exist, please enter a new Name!" << RESET << el;
            }
        }
        string name = input;
        return name;
    }
    //collect and validate Age
    int collect_age() {
        cout << "Enter Employee Age or type \"exit\" to return to the main menu!" << el;
        while (1) {
            validate_state = 0; //reset validate_state
            input = user_input.get_input();
            validate_state = validate_input.validate_age(input);
            if (validate_state == 0) {
                break;
            }
            else if (validate_state == -1) {
                display_menu();
                select_option();
            }
            else if (validate_state == 1) {
                cout << RED << "Invalid input, please enter a valid Age or type exit to return to the main menu!" << RESET << el;
            }
            else if (validate_state == 2) {
                cout << RED << "Age already exist, please enter a new Name!" << RESET << el;
            }
        }
        int age = stoi(input);
        return age;
    }
    //collect and validate Address
    address collect_address() {
        address collected_data_address;
        string temp_street_name, temp_near_by_landmarks, temp_building_num, temp_floor_num, temp_apart_num;
        int validate_state = 0;
        string input;

        cout << "Enter Employee Home Address or type \"exit\" to return to the main menu!" << el;

        temp_street_name = get_input("Enter street name: ");
        temp_near_by_landmarks = get_input("Enter near by land mark: ");
        temp_building_num = get_input("Enter Building Number: ", true);
        temp_floor_num = get_input("Enter Floor Number: ", true);
        temp_apart_num = get_input("Enter Apartment Number: ", true);

        validate_state = validate_input.validate_home_address(temp_street_name, temp_near_by_landmarks, temp_building_num, temp_floor_num, temp_apart_num);
        if (validate_state == 1) {
            cout << RED << "Invalid input, please enter a valid address data or type exit to return to the main menu!" << RESET << el;
        }

        collected_data_address.street_name = temp_street_name;
        collected_data_address.near_by_landmarks = temp_near_by_landmarks;
        collected_data_address.building_number = stoi(temp_building_num);
        collected_data_address.floor_number = stoi(temp_floor_num);
        collected_data_address.apartment_number = stoi(temp_apart_num);

        return collected_data_address;
    }
    //gets inputs for address
    string get_input(string prompt, bool isNumber = false) {
        string input;
        cout << prompt << el;
        while (true) {
            input = user_input.get_input();

            if (input.empty()) {
                cout << RED << "Input cannot be empty, please enter again!" << RESET << el;
                continue;
            }

            if (validate_input.check_exit(input)) {
                display_menu();
                select_option();
            }

            if (isNumber && validate_input.validate_int(input) == 1) {
                cout << RED << "Invalid input, please enter a valid number!" << RESET << el;
                continue;
            }

            break;
        }
        return input;
    }
    //collect and validate Role
    string collect_role() {
        //display the positions in a table
        cout << "---------------------------------------------------" << el;
        cout << "| Title                            | Abbreviation |" << el;
        cout << "---------------------------------------------------" << el;
        // Display Executive Positions
        cout << "Executive Roles:" << el;
        for (const auto& pos : Executive_Positions) {
            cout << "| " << left << setw(32) << pos.name << " | " << setw(12) << pos.abbreviation << " |" << el;
        }
        cout << "---------------------------------------------------" << el;
        // Display Management and Operational Positions
        cout << "Management and Operational Roles:" << el;
        for (const auto& pos : non_executive_positions) {
            cout << "| " << left << setw(32) << pos.name << " | " << setw(12) << pos.abbreviation << " |" << el;
        }
        cout << "---------------------------------------------------" << el;
        cout << "Enter Employee Role Abbreviation or type \"exit\" to return to the main menu!" << el;
        //Role Validation proccess
        while (1) {
            validate_state = 0; //reset validate_state
            input = user_input.get_input();
            validate_state = validate_input.validate_role(input);

            // Check if the input is empty
            if (input.empty()) {
                cout << RED << "Input cannot be empty, please enter a valid role!" << RESET << el;
                continue;
            }

            if (validate_state == 0) {
                break;
            }
            else if (validate_state == -1) {
                display_menu();
                select_option();
            }
            else if (validate_state == 1) {
                cout << RED << "Invalid input, please enter a valid Role or type \"exit\" to return to the main menu!" << RESET << el;
            }
            else if (validate_state == 2) {
                cout << RED << "Executive role is taken by another employee, please reneter your role, or type \"exit\" to return to the main menu!" << RESET << el;
            }
        }
        //save validated role
        string role = input;
        transform(role.begin(), role.end(), role.begin(), ::toupper);
        return role;
    }
    //collect and validate Salary
    float collect_salary() {
        cout << "Enter Employee Salary or type \"exit\" to return to the main menu!" << el;
        while (1) {
            validate_state = 0; //reset validate_state
            input = user_input.get_input();
            validate_state = validate_input.validate_salary(input);
            if (validate_state == 0) {
                break;
            }
            else if (validate_state == -1) {
                display_menu();
                select_option();
            }
            else if (validate_state == 1) {
                cout << RED << "Invalid input, please enter a valid salary or type \"exit\" to return to the main menu!" << RESET << el;
            }
            else if (validate_state == 2) {
                cout << RED << "Executive role is taken by another employee, please reneter your role, or type \"exit\" to retunr to the main menu!" << RESET << el;
            }
        }
        float salary = stof(input);
        return salary;
    }
};
 
class Staff_Managment_System : public Database, public Menu {
    Database initialize;
    Out_Put_Handler menu_call;
public:
    void run() {
        initialize.restore_data_from_file();
        while (1) {
            display_menu();
            select_option();
        }
    }

};

int main() {

    // Clear the screen
    system(CLEAR);

    // Use ASCII art for the title
    cout << RED << R"(
   _____ _         __  __ 
  / ____| |       / _|/ _|
 | (___ | |_ __ _| |_| |_ 
  \___ \| __/ _` |  _|  _|
  ____) | || (_| | | | |  
 |_____/ \__\__,_|_| |_|                                         
)" << RESET << el;

    cout << RED << R"(
  __  __                                              _   
 |  \/  |                                            | |  
 | \  / | __ _ _ __   __ _  __ _ _ __ ___   ___ _ __ | |_ 
 | |\/| |/ _` | '_ \ / _` |/ _` | '_ ` _ \ / _ \ '_ \| __|
 | |  | | (_| | | | | (_| | (_| | | | | | |  __/ | | | |_ 
 |_|  |_|\__,_|_| |_|\__,_|\__, |_| |_| |_|\___|_| |_|\__|
                            __/ |                         
                           |___/                          
)" << RESET << el;

    cout << RED << R"(
   _____           _                 
  / ____|         | |                
 | (___  _   _ ___| |_ ___ _ __ ___  
  \___ \| | | / __| __/ _ \ '_ ` _ \ 
  ____) | |_| \__ \ ||  __/ | | | | |
 |_____/ \__, |___/\__\___|_| |_| |_|
          __/ |                      
         |___/                                                              
)" << RESET << el;

    cout << R"(
The Staff Management Program is a program designed to streamline the process of managing staff data.
This simple yet robust program allows users to input, edit, and delete employee information with ease.

One of the key features of this program is its ability to save data in both .txt and .csv formats.
This ensures that users can access and manipulate the data outside the program, providing an additional layer of convenience.

Understanding that users may sometimes forget to save their latest data, the program includes an auto-save feature.
When exiting the program via the main menu, the most recent data is automatically saved to the external files, ensuring no information is lost.

Designed with user experience in mind, the program is capable of handling multiple errors without crashing, providing a smooth and uninterrupted experience.

The program also includes a powerful search feature. This allows users to locate employees using their full name stored in the system.
Additionally, users can utilize this feature to identify who currently holds a specific executive role.
)" << el;

    cout << "Program made by: " << "\n";
    cout << BLUE << "Mahmoud Ahmed \t ID: 234051" << RESET << "\n";
    cout << GREEN << "Ahmed Hussein \t ID: 225381" << RESET << "\n";
    cout << "Press enter to launch the program." << "\n";
    string status;
    getline(cin, status);

    Staff_Managment_System system;
    system.run();

    return 0;
}
