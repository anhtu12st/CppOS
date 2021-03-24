#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


struct Ticket
{
  char flightName[40];
  int value;
};

class People
{
protected:
  char name[40];
  int ID;
};

class Customer : public People
{
private:
  int quantity;
  Ticket tickets[10];

public:
  friend istream &operator>>(istream &in, Customer &customer)
  {
    cout << "Name? ";
    in.ignore();
    in.getline(customer.name, 40);
    cout << "ID? ";
    in >> customer.ID;
    cout << "How many tickets? ";
    in >> customer.quantity;

    for (int i = 0; i < customer.quantity; i++)
    {
      cout << "Input fightName for ticket " << i + 1 << "? ";
      in.ignore();
      in.getline(customer.tickets[i].flightName, 40);
      cout << "Input value for ticket " << i + 1 << "? ";
      in >> customer.tickets[i].value;
    }

    return in;
  }

  int getSumValue()
  {
    int sum = 0;
    for (int i = 0; i < quantity; i++)
    {
      sum += tickets[i].value;
    }
    return sum;
  }
};

int main()
{
  vector<Customer> customers;
  int numCustomers;
  cout << "Enter number of customers: ";
  cin >> numCustomers;
  for (int i = 0; i < numCustomers; i++)
  {
    Customer temp;
    cout << "Input detail for customer " << i + 1 << ": \n";
    cin >> temp;
    customers.push_back(temp);
  }

  int num = 1;
  while (num > 0 && num <= int(customers.size()))
  {
    cout << "Which customer with sum value? ";
    cin >> num;
    cout << customers[num - 1].getSumValue() << endl;
  }

  return 0;
}