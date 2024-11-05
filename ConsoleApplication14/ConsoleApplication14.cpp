#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employee {
protected:
    string firstName;
    string lastName;
public:
    Employee(string Fname, string Lname) : firstName(Fname), lastName(Lname) {}

    
    string GetFirst() const {
        return firstName;
    }
    void SetFirst(string Fname) {
        if (Fname.length() > 0) {
            firstName = Fname;
        }
        else {
            cout << "Please write first name" << endl;
        }
    }

    
    string GetLast() const {
        return lastName;
    }
    void SetLast(string Lname) {
        if (Lname.length() > 0) {
            lastName = Lname;
        }
        else {
            cout << "Please write last name" << endl;
        }
    }

    virtual double calculateSalary() = 0;
    virtual void display() = 0;

    
};

class Worker : public Employee {
private:
    int HoursNumber;
    float HourlyRate;
public:
    Worker(string Fname, string Lname, int HoursN, float HoursR) : Employee(Fname, Lname),
        HoursNumber(HoursN), HourlyRate(HoursR) {}

   
    int GetHoursNumber() const {
        return HoursNumber;
    }
    void SetHoursNumber(int HoursN) {
        if (HoursN > 0) {
            HoursNumber = HoursN;
        }
        else {
            cout << "Hours cannot be zero or negative" << endl;
        }
    }

 
    float GetHourlyRate() const {
        return HourlyRate;
    }
    void SetHourlyRate(float HoursR) {
        if (HoursR > 0) {
            HourlyRate = HoursR;
        }
        else {
            cout << "Hourly rate cannot be zero or negative" << endl;
        }
    }

    double calculateSalary() override {
        double salary = 0.0;
        if (HoursNumber <= 40) {
            return HoursNumber * HourlyRate;
        }
        else {
            salary = 40 * HourlyRate + (HoursNumber - 40) * 2.0 * HourlyRate;
        }
        return salary;
    }

    void display() override {
        cout << "Ad: " << firstName << ", Soyad: " << lastName
            << ", Saatliq Maas: " << HourlyRate
            << ",  Islediyi saat: " << HoursNumber
            << ", Heftelik maas: " << calculateSalary() << endl;
    }
};

class SalaryWorker : public Employee {
protected:
    double salary;
    double bonus;
public:
    SalaryWorker(string Fname, string Lname, double _salary, double _bonus)
        : Employee(Fname, Lname), salary(_salary), bonus(_bonus) {}

    
    double GetSalary() const {
        return salary;
    }
    void SetSalary(double _salary) {
        if (_salary > 0) {
            salary = _salary;
        }
        else {
            cout << "Salary cannot be zero or negative" << endl;
        }
    }

    
    double GetBonus() const {
        return bonus;
    }
    void SetBonus(double _bonus) {
        if (_bonus >= 0) {
            bonus = _bonus;
        }
        else {
            cout << "Bonus cannot be negative" << endl;
        }
    }

    virtual double CalculateBonus() = 0;

    double calculateSalary() override {
        return salary + CalculateBonus();
    }

    void display() override {
        cout << "Ad: " << firstName << ", Soyad: " << lastName
            << ", Maas: " << salary << ", Bonus: " << CalculateBonus()
            << ", Umumi maas: " << calculateSalary() << endl;
    }
};

class SalesMan : public SalaryWorker {
private:
    double planPercentage;
public:
    SalesMan(string Fname, string Lname, double _salary, double _bonus, double planPer)
        : SalaryWorker(Fname, Lname, _salary, _bonus), planPercentage(planPer) {}

   
    double GetPlanPercentage() const {
        return planPercentage;
    }
    void SetPlanPercentage(double planPer) {
        if (planPer >= 0 && planPer <= 100) {
            planPercentage = planPer;
        }
        else {
            cout << "Error" << endl;
        }
    }

    double CalculateBonus() override {
        return bonus * planPercentage / 100;
    }
};

class Manager : public SalaryWorker {
private:
    int ClientCount;
public:
    Manager(string Fname, string Lname, double _salary, double _bonus, int ClientC)
        : SalaryWorker(Fname, Lname, _salary, _bonus), ClientCount(ClientC) {}

    int GetClientCount() const {
        return ClientCount;
    }
    void SetClientCount(int ClientC) {
        if (ClientC >= 0) {
            ClientCount = ClientC;
        }
        else {
            cout << "Client count cannot be negative" << endl;
        }
    }

    double CalculateBonus() override {
        if (ClientCount < 100) {
            return bonus;
        }
        else if (ClientCount <= 200) {
            return bonus * 2;
        }
        else {
            return bonus * 3;
        }
    }
};

int main() {
    
    vector<Employee*> employees;

    
    employees.push_back(new Worker("Murad", "Veliyev", 45, 10));
    employees.push_back(new SalesMan("Ilyas", "Agayev", 3000, 500, 10));
    employees.push_back(new Manager("Akif", "Musazade", 5000, 800, 250));

    
    for (size_t i = 0; i < 3; i++)
    {
        employees[i]->display();
    }

    
    return 0;
}
