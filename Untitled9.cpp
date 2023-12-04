#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

// Constants
const int MAX_ENTRIES = 20;
const int DAYS_IN_WEEK = 5;
const int WORKING_HOURS_THRESHOLD = 6;
const int REGULAR_HOURS = 9;
const int REGULAR_RATE = 100;
const int OVERTIME_RATE = 200;

// Global arrays to store employee data
string days[] = {"SUN", "MON", "TUE", "WED", "THU"};
string names[MAX_ENTRIES] = {"Noura", "Aziz", "Deem", "Omar"};
int hours[MAX_ENTRIES][DAYS_IN_WEEK] = {
    {8, 7, 7, 5, 9},
    {9, 9, 10, 12, 5},
    {6, 10, 11, 10, 9},
    {8, 11, 5, 8, 12}
};
int employeeCount = 4;  // Initial number of employees

int main() {
    // Print the initial table
    cout << setw(4) << " ";
    for (int i = 0; i < DAYS_IN_WEEK; ++i) {
        cout << setw(4) << days[i];
    }
    cout << "\n";

    for (int i = 0; i < employeeCount; ++i) {
        cout << setw(4) << names[i];
        for (int j = 0; j < DAYS_IN_WEEK; ++j) {
            cout << setw(4) << hours[i][j];
        }
        cout << "\n";
    }

    // Modify working hours
    for (int i = 0; i < employeeCount; ++i) {
        for (int j = 0; j < DAYS_IN_WEEK; ++j) {
            if (hours[i][j] < WORKING_HOURS_THRESHOLD) {
                // Display a message about modified working hours
                cout << "The hours for " << names[i] << " on " << days[j] << " was changed to be " << WORKING_HOURS_THRESHOLD << "\n";
                hours[i][j] = WORKING_HOURS_THRESHOLD;
            }
        }
    }

    // Print the modified table
    cout << setw(4) << " ";
    for (int i = 0; i < DAYS_IN_WEEK; ++i) {
        cout << setw(4) << days[i];
    }
    cout << "\n";

    for (int i = 0; i < employeeCount; ++i) {
        cout << setw(4) << names[i];
        for (int j = 0; j < DAYS_IN_WEEK; ++j) {
            cout << setw(4) << hours[i][j];
        }
        cout << "\n";
    }

    // Print the day with the highest and lowest total working hours
    int totalHours[DAYS_IN_WEEK] = {0};

    for (int i = 0; i < employeeCount; ++i) {
        for (int j = 0; j < DAYS_IN_WEEK; ++j) {
            totalHours[j] += hours[i][j];
        }
    }

    int maxDayIndex = max_element(totalHours, totalHours + DAYS_IN_WEEK) - totalHours;
    int minDayIndex = min_element(totalHours, totalHours + DAYS_IN_WEEK) - totalHours;

    // Display the results for the day with the highest and lowest total working hours
    cout << "The day with the highest total working hours: " << days[maxDayIndex] << "\n";
    cout << "The day with the lowest total working hours: " << days[minDayIndex] << "\n";
    string employeeName;
    int employeeIndex;
    // Main loop for user interaction
    while (true) {
        cout << "------------------------------------------------------\n";
        cout << "Choose one of the following options:\n";
        cout << "1. Add a new Employee.\n";
        cout << "2. Enquire about an Employee.\n";
        cout << "3. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                // Add a new employee
                if (employeeCount >= MAX_ENTRIES) {
                    // Display a message when the maximum number of entries is reached
                    cout << "Maximum number of entries reached.\n";
                    break;
                }

                // Get input for the new employee
                cout << "Enter the Employee Name: ";
                cin >> names[employeeCount];

                cout << "Enter the working hours of the week: ";
                for (int i = 0; i < DAYS_IN_WEEK; ++i) {
                    cin >> hours[employeeCount][i];
                }

                // Increment the employee count
                ++employeeCount;
                // Display a message about the new entry
                cout << "New Entry Added.\n";

                // Print the updated table
                cout << setw(4) << " ";
                for (int i = 0; i < DAYS_IN_WEEK; ++i) {
                    cout << setw(4) << days[i];
                }
                cout << "\n";

                for (int i = 0; i < employeeCount; ++i) {
                    cout << setw(4) << names[i];
                    for (int j = 0; j < DAYS_IN_WEEK; ++j) {
                        cout << setw(4) << hours[i][j];
                    }
                    cout << "\n";
                }
                break;
            case 2:
                // Inquire about an employee

                // Get input for the employee name
                cout << "Enter the name of an employee: ";
                cin >> employeeName;

                employeeIndex = -1;

                // Find the index of the employee (case-insensitive)
                for (int i = 0; i < employeeCount; ++i) {
                    if (strcasecmp(names[i].c_str(), employeeName.c_str()) == 0) {
                        employeeIndex = i;
                        break;
                    }
                }

                if (employeeIndex != -1) {
                    int totalHours = 0;
                    int maxDayIndex = max_element(hours[employeeIndex], hours[employeeIndex] + DAYS_IN_WEEK) - hours[employeeIndex];

                    // Calculate total working hours for the employee
                    for (int i = 0; i < DAYS_IN_WEEK; ++i) {
                        totalHours += hours[employeeIndex][i];
                    }

                    // Display results for the employee
                    cout << names[employeeIndex] << " has worked " << totalHours << " hours in the week.\n";
                    cout << "The day that " << names[employeeIndex] << " has the highest working hours is " << days[maxDayIndex] << "\n";

                    int salary = 0;
                    // Calculate the salary for the employee
                    for (int i = 0; i < DAYS_IN_WEEK; ++i) {
                        if (hours[employeeIndex][i] <= REGULAR_HOURS) {
                            salary += hours[employeeIndex][i] * REGULAR_RATE;
                        } else {
                            salary += REGULAR_HOURS * REGULAR_RATE + (hours[employeeIndex][i] - REGULAR_HOURS) * OVERTIME_RATE;
                        }
                    }

                    cout << names[employeeIndex] << " Salary: " << salary << " SAR in the week.\n";
                } else {
                    // Display a message when the employee does not exist
                    cout << "Sorry, the employee does not exist.\n";
                }
                break;
            case 3:
                // Exit the program
                cout << "Thank you for using our system.\n";
                return 0;
            default:
                // Invalid choice
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

