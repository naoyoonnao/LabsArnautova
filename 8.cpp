#include <iostream>
#include <string>
using namespace std;

struct TStudent {
    string firstName;
    string lastName;
    double averageScore;

    friend ostream& operator<<(ostream& out, const TStudent& student);
    friend istream& operator>>(istream& in, TStudent& student);
};

ostream& operator<<(ostream& out, const TStudent& student) {
    out << student.firstName << " " << student.lastName << ", Average Score: " << student.averageScore;
    return out;
}

istream& operator>>(istream& in, TStudent& student) {
    cout << "Enter first name: ";
    getline(in, student.firstName);
    cout << "Enter last name: ";
    getline(in, student.lastName);
    cout << "Enter average score: ";
    in >> student.averageScore;
    in.ignore();
    return in;
}

struct TFaculty {
    string name;
    string profile;

    friend ostream& operator<<(ostream& out, const TFaculty& faculty);
    friend istream& operator>>(istream& in, TFaculty& faculty);
};

ostream& operator<<(ostream& out, const TFaculty& faculty) {
    out << "Faculty: " << faculty.name << ", Profile: " << faculty.profile;
    return out;
}

istream& operator>>(istream& in, TFaculty& faculty) {
    cout << "Enter faculty name: ";
    getline(in, faculty.name);
    cout << "Enter faculty profile: ";
    getline(in, faculty.profile);
    return in;
}

class TStudentGroup {
private:
    TFaculty faculty;
    string groupName;
    TStudent* students;
    int studentCount;

public:
    TStudentGroup() : students(nullptr), studentCount(0) {}

    TStudentGroup(const TFaculty& faculty_, const string& groupName_)
        : faculty(faculty_), groupName(groupName_), students(nullptr), studentCount(0) {
    }

    ~TStudentGroup() {
        delete[] students;
    }

    const string& getGroupName() const { return groupName; }
    const TFaculty& getFaculty() const { return faculty; }

    bool isPartOfFaculty(const string& facultyName) const {
        return faculty.name == facultyName;
    }

    double calcAverageScoreByName(const string& name) const {
        double totalScore = 0;
        int count = 0;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].firstName == name) {
                totalScore += students[i].averageScore;
                count++;
            }
        }
        return count > 0 ? totalScore / count : 0.0;
    }

    void addStudent(const TStudent& student) {
        TStudent* newStudents = new TStudent[studentCount + 1];
        for (int i = 0; i < studentCount; ++i) {
            newStudents[i] = students[i];
        }
        newStudents[studentCount] = student;
        delete[] students;
        students = newStudents;
        ++studentCount;
    }

    bool removeStudent(const string& firstName, const string& lastName) {
        int index = -1;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].firstName == firstName && students[i].lastName == lastName) {
                index = i;
                break;
            }
        }
        if (index == -1) return false;

        TStudent* newStudents = new TStudent[studentCount - 1];
        for (int i = 0, j = 0; i < studentCount; ++i) {
            if (i != index) {
                newStudents[j++] = students[i];
            }
        }
        delete[] students;
        students = newStudents;
        --studentCount;
        return true;
    }

    int countAboveAverageStudents() const {
        if (studentCount == 0) return 0;
        double totalScore = 0;
        for (int i = 0; i < studentCount; ++i) {
            totalScore += students[i].averageScore;
        }
        double groupAverage = totalScore / studentCount;

        int count = 0;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].averageScore > groupAverage) {
                count++;
            }
        }
        return count;
    }

    double getStudentAverage(const string& firstName, const string& lastName) const {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].firstName == firstName && students[i].lastName == lastName) {
                return students[i].averageScore;
            }
        }
        return 0.0;
    }

    friend ostream& operator<<(ostream& out, const TStudentGroup& group);
    friend istream& operator>>(istream& in, TStudentGroup& group);
};

ostream& operator<<(ostream& out, const TStudentGroup& group) {
    out << "Group: " << group.groupName << "\n" << group.faculty << "\nStudents:\n";
    for (int i = 0; i < group.studentCount; ++i) {
        out << group.students[i] << "\n";
    }
    return out;
}

istream& operator>>(istream& in, TStudentGroup& group) {
    cout << "Enter group name: ";
    getline(in, group.groupName);
    cout << "Enter faculty details:\n";
    in >> group.faculty;

    string answer;
    do {
        cout << "Add a student:\n";
        TStudent student;
        in >> student;
        group.addStudent(student);
        cout << "Add another student? (y/n): ";
        getline(in, answer);
    } while (!answer.empty() && answer[0] == 'y');
    return in;
}

int main() {
    TStudentGroup group;
    cin >> group;

    cout << "Group details:\n" << group;

    cout << "\nEnter a student to add:\n";
    TStudent newStudent;
    cin >> newStudent;
    group.addStudent(newStudent);

    cout << "\nUpdated group details:\n" << group;

    cout << "\nEnter a student to remove (first and last name):\n";
    string firstName, lastName;
    cout << "First name: ";
    getline(cin, firstName);
    cout << "Last name: ";
    getline(cin, lastName);

    if (group.removeStudent(firstName, lastName)) {
        cout << "Student removed successfully.\n";
    }
    else {
        cout << "Student not found.\n";
    }

    cout << "\nFinal group details:\n" << group;

    return 0;
}
