#include<iostream>
#include<vector>
#include <iomanip>
using namespace std;
class grade
{
public:
  int mark;
  char nameofcourse[40];
  friend istream& operator >> (istream &in,  grade &x){
    cout << "Name of course?";
    in >> x.nameofcourse;
    cout << "Mark of course?";
    in >> x.mark;
    return in;
  }
};
class student
{
protected:
  int studentID;
  grade a[10];
  char name[40];
  int number;

public:
  double average(){
    double avg = 0;
    for (int i = 0; i < this->number; i++)
    {
      avg += a[i].mark;
    }
    return avg / number;
  }
  friend istream& operator >> (istream &in,  student &student){
    cout << "Studen ID?:";
    in >> student.studentID;
    cout << "name?:";
    in >> student.name;
    cout << "How many grade?";
    in >> student.number;
    for (int i = 0; i < student.number;i++){
      in >> student.a[i];
    }
    return in;
  }
};
int main(){
  cout << "How many student?:";
  int number;
  cin >> number;
  vector<student> University;
  for (int i = 0; i < number;i++){
    cout << "Input detals of student" << i + 1 << endl;
    student stu;
    cin >> stu;
    University.push_back(stu);
  }
  int a=1;
  while(a>0 && a<=int(University.size())){
    cout << "which student avg garde: ";
    cin >> a;
    cout << University[a - 1].average() << endl;
  }
}