#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <sstream>

using namespace std;

enum class GradeLevel { FRESHMAN = 1, SOPHOMORE = 2, JUNIOR = 3, SENIOR = 4 };

typedef double GPA_t; 
using Str = std::string;

struct Student {
Str name;
GradeLevel grade;
GPA_t gpa;
};

namespace StudentUtils {
    
void formatName(Str &name) {
for (char &c : name) {
c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
}
}

Str gradeToString(GradeLevel g) {
switch (g) {
case GradeLevel::FRESHMAN:  return "Freshman";
case GradeLevel::SOPHOMORE: return "Sophomore";
case GradeLevel::JUNIOR:    return "Junior";
case GradeLevel::SENIOR:    return "Senior";
default: return "Unknown";
}
}
    
Str formatGPA(GPA_t gpa) {
std::ostringstream oss;
oss << std::fixed << std::setprecision(2) << gpa;
return oss.str();
}
   
void displayStudentInfo(const Student &s) {
Str upper = s.name;
formatName(upper);
cout << "Student Record:\n";
cout << "  Name       : " << upper << "\n";
cout << "  Grade Level: " << gradeToString(s.grade) << "\n";
cout << "  GPA        : " << formatGPA(s.gpa) << "\n";
}
}

namespace Input {
Str readName() {
cout << "Enter student name: ";
Str name;
cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline
getline(cin, name);
return name;
}

GradeLevel readGrade() {
while (true) {
cout << "Enter grade level (1=Freshman, 2=Sophomore, 3=Junior, 4=Senior): ";
int x;
if (cin >> x && x >= 1 && x <= 4) return static_cast<GradeLevel>(x);
cout << "Oops! Please enter a number 1-4.\n";
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
}

GPA_t readGPA() {
while (true) {
cout << "Enter GPA (0.00 - 4.00): ";
GPA_t g;
if (cin >> g && g >= 0.0 && g <= 4.0) return g;
cout << "Invalid GPA. Try a value from 0.00 to 4.00.\n";
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
}
}

// BONUS
bool nameLessCI(const Student &a, const Student &b) {
Str A = a.name, B = b.name;
StudentUtils::formatName(A);
StudentUtils::formatName(B);
return A < B;
}

int main() {
cout << "=== Student Records Manager ===\n";

vector<Student> students; 
while (true) {
cout << "\nAdd a student record? (y/n): ";
char ans; if (!(cin >> ans)) return 0;
if (ans == 'n' || ans == 'N') break;
if (ans != 'y' && ans != 'Y') { cout << "Please type y or n.\n"; continue; }

Student s{};
s.name  = Input::readName();
s.grade = Input::readGrade();
s.gpa   = Input::readGPA();
students.push_back(s);
}

if (students.empty()) {
cout << "\nNo records entered. Goodbye!\n";
return 0;
}

cout << "\nSort records alphabetically by name? (y/n): ";
char sortChoice; if (cin >> sortChoice) {
if (sortChoice == 'y' || sortChoice == 'Y') {
sort(students.begin(), students.end(), nameLessCI);
}
}

cout << "\n--- Displaying Student Records ---\n";
for (const auto &st : students) {
StudentUtils::displayStudentInfo(st);
cout << "------------------------------\n";
}

return 0;
}
