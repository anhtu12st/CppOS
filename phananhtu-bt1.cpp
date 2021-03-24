#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Grade
{
    char nameOfCourse[40];
    int mark;
};

class Student
{
private:
    int studentID;
    char name[40];
    Grade grades[10];
    int numGrade;

public:
    friend istream &operator>>(istream &in, Student &stu)
    {
        cout << "Student ID? ";
        in >> stu.studentID;
        cout << "Name? ";
        in.ignore();
        in.getline(stu.name, 40);

        cout << "-----\n";
        cout << "How many Grades? ";
        in >> stu.numGrade;

        if (stu.numGrade > 10 || stu.numGrade < 0)
            throw "Invalid numGrade";

        for (int i = 0; i < stu.numGrade; i++)
        {
            if (i != 0)
                cout << "-----\n";
            cout << "Name of Grande " << i + 1 << ": ";
            in.ignore();
            in.getline(stu.grades[i].nameOfCourse, 40);
            cout << "Mark of Grade " << i + 1 << ": ";
            in >> stu.grades[i].mark;
        }
        return in;
    }
    double getAvg()
    {
        double total = 0;
        for (int i = 0; i < numGrade; i++)
        {
            total += grades[i].mark;
        }

        return total / numGrade;
    }
};

int main()
{
    vector<Student> students;
    int numStu;
    cout << "Enter number of Students? ";
    cin >> numStu;

    for (int i = 0; i < numStu; i++)
    {
        Student temp;
        cout << "-----\n";
        cout << "Input details for student " << i + 1 << ":\n";
        cin >> temp;
        students.push_back(temp);
    }

    cout << "=====\n";

    int num = 1;
    while (num > 0 && num <= int(students.size()))
    {
        cout << "Which student average grade? ";
        cin >> num;

        cout << "Average grade for student " << num << ": ";
        cout << setprecision(2) << students[num - 1].getAvg() << endl;
    }

    return 0;
}