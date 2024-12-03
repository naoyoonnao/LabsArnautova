#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class AbstractArray {
protected:
    T* array;
    size_t size;

public:
    AbstractArray() : array(nullptr), size(0) {}

    AbstractArray(size_t initialSize) : size(initialSize) {
        array = new T[size];
    }

    virtual ~AbstractArray() {
        delete[] array;
    }

    size_t getSize() const {
        return size;
    }

    virtual void addElement(const T& element) = 0;
    virtual void removeElement(size_t index) = 0;

    virtual void input() = 0;
    virtual void output() const = 0;
};

struct TStudent {
    string firstName;
    string lastName;
    double averageScore;

    friend ostream& operator<<(ostream& out, const TStudent& student) {
        out << student.firstName << " " << student.lastName << ", Average Score: " << student.averageScore;
        return out;
    }

    friend istream& operator>>(istream& in, TStudent& student) {
        cout << "Enter first name: ";
        getline(in, student.firstName);
        cout << "Enter last name: ";
        getline(in, student.lastName);
        cout << "Enter average score: ";
        in >> student.averageScore;
        in.ignore();
        return in;
    }
};

class StudentGroup : public AbstractArray<TStudent> {
public:
    StudentGroup() : AbstractArray() {}

    StudentGroup(size_t initialSize) : AbstractArray(initialSize) {}

    void addElement(const TStudent& student) override {
        TStudent* newArray = new TStudent[size + 1];
        for (size_t i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        newArray[size] = student;
        delete[] array;
        array = newArray;
        ++size;
    }

    void removeElement(size_t index) override {
        if (index >= size) {
            cout << "Invalid index!\n";
            return;
        }

        TStudent* newArray = new TStudent[size - 1];
        for (size_t i = 0, j = 0; i < size; ++i) {
            if (i != index) {
                newArray[j++] = array[i];
            }
        }
        delete[] array;
        array = newArray;
        --size;
    }

    void input() override {
        cout << "Enter number of students: ";
        size_t count;
        cin >> count;
        cin.ignore();

        for (size_t i = 0; i < count; ++i) {
            TStudent student;
            cin >> student;
            addElement(student);
        }
    }

    void output() const override {
        cout << "Student Group:\n";
        for (size_t i = 0; i < size; ++i) {
            cout << array[i] << endl;
        }
    }
};

int main() {
    StudentGroup group;

    cout << "Input student group:\n";
    group.input();

    cout << "\nGroup details:\n";
    group.output();

    cout << "\nAdding a new student:\n";
    TStudent newStudent;
    cin >> newStudent;
    group.addElement(newStudent);

    cout << "\nUpdated group details:\n";
    group.output();

    cout << "\nEnter index of student to remove (starts from 0): ";
    size_t index;
    cin >> index;
    group.removeElement(index);

    cout << "\nFinal group details:\n";
    group.output();

    return 0;
}
