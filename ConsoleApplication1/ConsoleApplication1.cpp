#include <iostream>
#include <list>
#include <string.h>

using namespace std;

int comparisonCount;
int uniqueCount;

class SList {
public:
    list<char*> myList;
    //int comparisonCount = 0;
    //int uniqueCount = 0;

    SList() {
        int comparisonCount = 0;
        int uniqueCount = 0;
    }

    bool isInList(char* str) {
        for (char* s : myList) {
            comparisonCount++;
            if (s == str) {
                return true;
            }
        }
        return false;
    }

    void addToList(char* str) {
        if (!isInList(str)) {
            myList.push_back(str);
            uniqueCount++;
        }
    }

    void concatenate(SList& other) {
        for (char* s : other.myList) {
            addToList(s);
        }
    }
};

class HashTable {
private:
    int q;
    
public:
    SList* table;
    HashTable(int q) : q(q) {
        table = new SList[q];
    }

    ~HashTable() {
        delete[] table;
    }

    int hashFunction(char* str) {
        int hash = 0;
        for (; *str; str++)
            hash = (hash * 31 + *str) % q;
        return hash;
    }

    void addUniqueString(char* str) {
        int index = hashFunction(str);
        table[index].addToList(str);
    }

    void concatenateAll() {
        for (int i = 1; i < q; i++) {
            table[0].concatenate(table[i]);
        }
    }

    void printElements() {
        for (int i = 0; i < q; ++i) {
            cout << "Slot " << i << " contain strings: ";
            for (char* str : table[i].myList) {
                cout << str << ", ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    int n = 100; 
    char lower = 'a';
    char upper = 'z';
    int q = 107; 
    
    srand(time(NULL));

    char** arr = new char* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new char[10];
        for (int j = 0; j < 9; j++) {
            arr[i][j] = lower + rand() % (upper - lower + 1);
        }
        arr[i][9] = '\0';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            cout << arr[i][j] << "";
        }
        cout << endl;
    }

    HashTable ht(q);

    for (int i = 0; i < n; i++) {
        ht.addUniqueString(arr[i]);
    }

    ht.printElements();

    cout << "Sravneniy = " << comparisonCount << std::endl;
    cout << "Uniq str = " << uniqueCount << std::endl;

    

    return 0;
}
