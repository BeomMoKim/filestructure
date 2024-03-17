#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Student {
private:
    int stuID;
    string name;
    string address;
    tm firstEnrollDate;
    int credits;
    vector<int> enrolledCourses;

public:
    Student(int stuId, string studentName, string studentAddress, tm firstEnrollDate, int credits) :
        stuID(stuId), name(studentName), address(studentAddress), firstEnrollDate(firstEnrollDate), credits(credits) {}

    int getId() const { return stuID; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    tm getFirstEnrollmentDate() const { return firstEnrollDate; }
    int getCredits() const { return credits; }

    void setId(int studentId) { stuID = studentId; }
    void setName(string studentName) { name = studentName; }
    void setAddress(string studentAddress) { address = studentAddress; }
    void setFirstEnrollmentDate(tm enrollmentDate) { firstEnrollDate = enrollmentDate; }
    void setCreditsEarned(int earnedCredits) { credits = earnedCredits; }
    vector<int> getEnrolledCourses() const { return enrolledCourses; }

    Student& operator=(const Student& other) {
        if (this != &other) {
            stuID = other.stuID;
            name = other.name;
            address = other.address;
            firstEnrollDate = other.firstEnrollDate;
            credits = other.credits;
        }
        return *this;
    }

    void enrollCourse(int courseId, int creditHours, char grade) {
        enrolledCourses.push_back(courseId);
        credits += creditHours;
    }
};

class CourseRegistration {
private:
    int courseID;
    int studentID;
    int creditHours;
    char grade;

public:
    CourseRegistration(int courseID, int studentId, int creditHours, char grade) :
        courseID(courseID), studentID(studentId), creditHours(creditHours), grade(grade) {}

    int getCourseId() const { return courseID; }
    int getStudentId() const { return studentID; }
    int getCreditHours() const { return creditHours; }
    char getGrade() const { return grade; }

    void setCourseId(int courseId) { this->courseID = courseId; }
    void setStudentId(int studentId) { this->studentID = studentId; }
    void setCreditHours(int creditHours) { this->creditHours = creditHours; }
    void setGrade(char grade) { this->grade = grade; }
};

tm generateRandomDate() {
    time_t now = time(NULL);
    struct tm date;
    localtime_s(&date, &now);
    return date;
}

char generateRandomGrade() {
    vector<string> grades = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F" };
    return grades[rand() % grades.size()][0];
}

int main() {
    srand(time(NULL));

    vector<Student> students;
    for (int i = 0; i < 15; ++i) {
        Student student(i + 1, "Student" + to_string(i + 1), "Address" + to_string(i + 1), generateRandomDate(), 0);
        students.push_back(student);
    }

    vector<CourseRegistration> courses;
    for (int i = 0; i < 3; ++i) {
        int courseId = i + 1;
        vector<int> enrolledStudents;
        for (int j = 0; j < 5; ++j) {
            int studentIndex = rand() % 15;
            while (find(enrolledStudents.begin(), enrolledStudents.end(), studentIndex) != enrolledStudents.end()) {
                studentIndex = rand() % 15;
            }
            enrolledStudents.push_back(studentIndex);

            students[studentIndex].enrollCourse(courseId, 3, generateRandomGrade());

            CourseRegistration registration(courseId, students[studentIndex].getId(), 3, generateRandomGrade());
            courses.push_back(registration);
        }
    }

    cout << "Course Registration Information:" << endl;
    for (const auto& course : courses) {
        cout << "Course ID: " << course.getCourseId() << ", Student ID: " << course.getStudentId()
            << ", Credit Hours: " << course.getCreditHours() << ", Grade: " << course.getGrade() << endl;
    }

    cout << "\nStudent Information:" << endl;
    for (const auto& student : students) {
        cout << "ID: " << student.getId() << ", Name: " << student.getName() << ", Address: " << student.getAddress()
            << ", CreditsEarned: " << student.getCredits() << endl;
        cout << "Enrolled Courses: ";
        for (int courseId : student.getEnrolledCourses()) {
            cout << courseId << " ";
        }
        cout << endl<< endl;
    }

    return 0;
}
