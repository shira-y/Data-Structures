//shira yaish, 327242939
//targil 2
#include "College.h"
#include "Course.h"
#include "HashTable.h"
#include "StringHash.h"
#include "IntHash.h"

void College::addCourse()
{
    string name;
    int num;
    cout << "enter course name" << endl;
    cin >> name;
    cout << "enter course id" << endl;
    cin >> num;

    Course newCourse(name, num);
    courses.insert(num, newCourse);
}

void College::removeCourse()
{
    int num;
    cout << "enter course id" << endl;
    cin >> num;

    courses.remove(num);
}

void College::addStudent()
{
    string name;
    cout << "enter students name" << endl;
    cin >> name;
    list<int> lst;

    students.insert(name, lst);
}

void College::removeStudent()
{
    string name;
    cout << "enter students name" << endl;
    cin >> name;

    students.remove(name);
}

void College::registration()
{
    string name;
    cout << "enter students name" << endl;
    cin >> name;
    int num;
    cout << "enter course id" << endl;
    cin >> num;

    try {
        // Checks if the course exists
        int courseIndex = courses.search(num);
        if (courseIndex == -1) {
            throw "Course not found.";
        }

        // Checks if the student exists
        int studentIndex = students.search(name);
        if (studentIndex == -1) {
            throw "Student not found.";
        }

        // Adds the course to the student's course list
        list<int>& coursesList = students.entryData(studentIndex);
        coursesList.push_back(num);
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
}

void College::removeReg()
{
    string name;
    cout << "enter students name" << endl;
    cin >> name;
    int num;
    cout << "enter course id" << endl;
    cin >> num;

    try {
        // Checks if the student exists
        int studentIndex = students.search(name);
        if (studentIndex == -1) {
            throw "Student not found.";
        }

        // Removes the course from the student's list
        list<int>& coursesList = students.entryData(studentIndex);
        coursesList.remove(num);
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
}

void College::print()
{
    string name;
    cout << "enter students name" << endl;
    cin >> name;

    try {
        int studentIndex = students.search(name);
        if (studentIndex == -1) {
            throw "key does not exist in table";
        }

        list<int>& lst = students.entryData(studentIndex);
        for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
        {
            int k = *it;
            int courseIndex = courses.search(k);
            if (courseIndex != -1)
            {
                Course& c = courses.entryData(courseIndex);
                cout << c.getName() << ' ';
            }
        }
        cout << endl;
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
}

void College::printStudentsTable() {
    students.print();
}

void College::printCoursesTable() {
    courses.print();
}