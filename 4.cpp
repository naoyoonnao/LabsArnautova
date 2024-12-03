
#include <iostream>
#include <string>
using namespace std;
const int n = 15;
struct FIO {
    string Name;
    string Surname;
};
struct Student {
    FIO FullName;
    int passes;
    string Group;
    string Faculty;
};
Student list[n] = { 
    {{"Name1","Surname1"},3,"Group4","Faculty1"},
    {{"Name2","Surname2"},5,"Group1","Faculty1"},
    {{"Name3","Surname3"},7,"Group2","Faculty1"},
    {{"Name4","Surname4"},3,"Group3","Faculty1"},
    {{"Name5","Surname5"},10,"Group4","Faculty1"},
    {{"Name6","Surname6"},16,"Group1","Faculty1"},
    {{"Name7","Surname7"},4,"Group2","Faculty1"},
    {{"Name8","Surname8"},9,"Group3","Faculty1"},
    {{"Name9","Surname9"},8,"Group4","Faculty1"},
    {{"Name10","Surname10"},0,"Group4","Faculty1"},
    {{"Name11","Surname11" },3,"Group2","Faculty1"},
    {{"Name12","Surname12"},4,"Group1","Faculty1"},
    {{"Name13","Surname13"},7,"Group2","Faculty1"},
    {{"Name14","Surname14"},12,"Group4","Faculty1"},
    {{"Name15","Surname15"},9,"Group1","Faculty1"}};

Student* ptr = &list[0];

int main() {
    for (int i = 0; i < n; i++, cout << endl) {
        cout << (ptr + i)->FullName.Name << "\t" << (ptr + i)->FullName.Surname << "\t" << (ptr + i)->passes << "\t" << (ptr + i)->Group << "\t" << (ptr + i)->Faculty;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((ptr + j)->passes < (ptr + j + 1)->passes) {
                Student temp = *(ptr + j);
                *(ptr + j) = *(ptr + j + 1);
                *(ptr + j + 1) = temp;
            }
        }
    }
    cout << endl << endl;
    for (int i = 0; i < 10; i++, cout << endl) {
        cout << (ptr + i)->FullName.Name << "\t" << (ptr + i)->FullName.Surname << "\t" << (ptr + i)->passes << "\t" << (ptr + i)->Group << "\t" << (ptr + i)->Faculty;
    }

    return 0;
}
