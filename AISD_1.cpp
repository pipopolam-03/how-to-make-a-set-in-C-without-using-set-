#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <vector>
#include <string>
using namespace std;
const int SIZE = 10;
const string U = "0123456789";


/////////////////////////////////////////////   list functions


struct SetElement {
    int value;
    SetElement* next;
    SetElement(int val, SetElement* n = nullptr) : value(val), next(n) {}
};


struct ListSet {
    SetElement* head;
};


ListSet createListSet() {
    ListSet set;
    set.head = nullptr;
    return set;
}


bool contains(const ListSet& set, int val) {
    SetElement* current = set.head;
    while (current != nullptr) {
        if (current->value == val) {
            return true;
        }
        current = current->next;
    }
    return false;
}


void insert(ListSet& set, int val) {
    if (!contains(set, val)) {
        set.head = new SetElement(val, set.head);
    }
}


void print(const ListSet& set) {
    SetElement* current = set.head;
    while (current != nullptr) {
        cout << current->value;
        current = current->next;
    }
}


void clear(ListSet& set) {
    SetElement* current = set.head;
    while (current != nullptr) {
        SetElement* next = current->next;
        delete current;
        current = next;
    }
    set.head = nullptr;
}

//////////////////////////////////////// array functions

void array_output(int arr[])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i] != -1)
        {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

void array_input(int arr[], int size)
{
    cout << "Введите его элементы: \n";

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
    for (int i = size; i < SIZE; i++)
    {
        arr[i] = -1;
    }
}

void array_randomizer(int arr[], int size)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int alphabet[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < size; i++)
    {
        int index = rand() % (10 - i);
        arr[i] = alphabet[index];
        alphabet[index] = alphabet[9 - i];
    }
    for (int i = size; i < SIZE; i++)
    {
        arr[i] = -1;
    }

}



int array_size(int arr[])
{
    int cnt = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i] != -1)
        {
            cnt++;
        }
    }
    return cnt;
}

int* to_normal(int arr[])
{
    int* normalized = new int[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i] > 9 || arr[i] < 0)
        {
            normalized[i] = -1;
        }
        else
        {
            normalized[i] = arr[i];
        }
    }
    return normalized;
}
int* intersection_array(int arr1[], int arr2[])
{
    int* res = new int[SIZE];
    int cnt = 0;
    int* norm_arr1 = to_normal(arr1);
    int* norm_arr2 = to_normal(arr2);
    int size_1 = array_size(norm_arr1);
    int size_2 = array_size(norm_arr2);

    for (int i = 0; i < size_1; i++)
    {
        for (int j = 0; j < size_2; j++)
        {
            if (norm_arr1[i] == norm_arr2[j])
            {
                res[cnt] = norm_arr1[i];
                cnt++;
                break;
            }
        }
    }

    delete[] norm_arr1;
    delete[] norm_arr2;
    return res;
}

int* unification_array(int arr1[], int arr2[])
{
    int* res = new int[SIZE];
    int cnt = 0;
    int* norm_arr1 = to_normal(arr1);
    int* norm_arr2 = to_normal(arr2);
    int size_1 = array_size(norm_arr1);
    int size_2 = array_size(norm_arr2);

    for (int i = 0; i < size_1; i++)
    {
        bool isUnique = true;

        for (int j = 0; j < cnt; j++)
        {
            if (norm_arr1[i] == res[j])
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            res[cnt] = norm_arr1[i];
            cnt++;
        }
    }

    for (int i = 0; i < size_2; i++)
    {
        bool isUnique = true;

        for (int j = 0; j < cnt; j++)
        {
            if (norm_arr2[i] == res[j])
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            res[cnt] = norm_arr2[i];
            cnt++;
        }
    }

    delete[] norm_arr1;
    delete[] norm_arr2;
    return res;
}



//////////////////////////////////// binary arr and word functions


void make_binary_arr(string str, bool* set) {
    unsigned char i = 0;
    for (char const& c : U) {
        if (str.find(c) != -1) {
            set[i] = 1;
        }
        else { set[i] = 0; }
        i++;
    }
    return;
}

void make_binary_word(string str, int& set) {
    unsigned char i = 0;
    set = 0;
    for (char const& c : U) {
        set *= 2;
        if (str.find(c) != -1) {
            set += 1;
        }
        i++;
    }
    return;
}

void intersection_bin_word(bool* set_one, bool* set_two, bool* set_res) {
    for (unsigned char i = 0; i < 10; i++) {
        if (set_one[i] and set_two[i]) {
            set_res[i] = 1;
        }
        else { set_res[i] = 0; }
    }
    return;
}

void unification_bin_word(bool* set_one, bool* set_two, bool* set_res) {
    for (unsigned char i = 0; i < 10; i++) {
        if (set_one[i] or set_two[i]) {
            set_res[i] = 1;
        }
    }
    return;
}

void binary_arr(string str_one, string str_two, string str_three, string str_four) {

    bool final_set[10], set_one[10], set_two[10], set_three[10], set_four[10];

    make_binary_arr(str_one, set_one);
    make_binary_arr(str_two, set_two);
    make_binary_arr(str_three, set_three);
    make_binary_arr(str_four, set_four);
    intersection_bin_word(set_one, set_two, final_set);
    unification_bin_word(set_three, set_four, final_set);

    cout << "Result(binary array): E = A & B || C || D = ";
    for (int i = 0; i < 10; i++) {
        if (final_set[i]) {
            cout << U[i];
        }
    }
    cout << std::endl;
    return;
}

void binary_word(string str_one, string str_two, string str_three, string str_four) {

    int final_set, set_one, set_two, set_three, set_four;
    make_binary_word(str_one, set_one);
    make_binary_word(str_two, set_two);
    make_binary_word(str_three, set_three);
    make_binary_word(str_four, set_four);

    final_set = set_one & set_two;
    final_set = final_set | set_three | set_four;


    cout << "Result(machine word): E = A & B || C || D = ";
    for (int i = 0; i < 10; i++) {
        bool fl = (bool(1 & final_set));
        if (fl) {
            cout << U[9 - i];
        }
        final_set = final_set >> 1;
    }
    cout << endl;
    return;
}


void make_arr(string str, int* arr) {
    unsigned char i = 0;
    for (char const& c : str) {
        arr[i++] = c - '0';
    }
    return;
}

void arr(string str_one, string str_two, string str_three, string str_four) {
    int* result;

    int A[SIZE], B[SIZE], C[SIZE], D[SIZE];
    make_arr(str_one, A);
    make_arr(str_two, B);
    make_arr(str_three, C);
    make_arr(str_four, D);
    result = to_normal(unification_array(unification_array(intersection_array(A, B), C), D));

    int size_result = array_size(result);

    cout << "Result(array):  E = A & B || C || D = ";
    for (int i = 0; i < size_result; i++)
    {
        cout << result[i];
    }
    cout << endl;
    delete[] result;
    return;
}

void make_lst(string str, ListSet* lst) {
    unsigned char i = 0;
    for (char const& c : str) {
        int temp = c - '0';
        insert(*lst, temp);
    }
    return;
}

void lst(string str_one, string str_two, string str_three, string str_four) {

    ListSet listA = createListSet();
    ListSet listB = createListSet();
    ListSet listC = createListSet();
    ListSet listD = createListSet();

    make_lst(str_one, &listA);
    make_lst(str_two, &listB);
    make_lst(str_three, &listC);
    make_lst(str_four, &listD);

    ListSet intersectionAB = createListSet();
    SetElement* currentA = listA.head;
    while (currentA != nullptr) {
        if (contains(listB, currentA->value)) {
            insert(intersectionAB, currentA->value);
        }
        currentA = currentA->next;
    }

    ListSet unionCD = listC;
    SetElement* currentD = listD.head;
    while (currentD != nullptr) {
        if (!contains(unionCD, currentD->value)) {
            insert(unionCD, currentD->value);
        }
        currentD = currentD->next;
    }

    ListSet result = intersectionAB;
    SetElement* current = unionCD.head;
    while (current != nullptr) {
        if (!contains(result, current->value)) {
            insert(result, current->value);
        }
        current = current->next;
    }


    cout << "Result(list): E = A & B || C || D = ";

    print(result);
    cout << '\n';

    return;
}

string string_randomizer() {
    string result;
    for (int i = 0; i < 10; ++i) {
        if (rand() % 2) {
            result += U[i];
        }
    }
    result += "\0";
    return result;
}




int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int flag = 0, temp = 0, size = 0; // for list
    string str_one, str_two, str_three, str_four; // for binary

    cout << "Choose how you want to define sets:\n1 - Manually\n2 - Randomly\n3 - Use predefined sets\n";
    cin >> flag;
    while (flag != 1 and flag != 2 and flag != 3)
    {
        cout << "Invalid input. Please try again\n";
        cout << "1 - Manually\n2 - Randomly\n3 - Use predefined sets\n";
        cin >> flag;
    }

    if (flag == 1)
    {
        cout << "Enter sets line by line, without spaces: \n";
        cin >> str_one;
        cin >> str_two;
        cin >> str_three;
        cin >> str_four;
    }
    else if (flag == 2)
    {
        str_one = string_randomizer();
        str_two = string_randomizer();
        str_three = string_randomizer();
        str_four = string_randomizer();
    }
    else if (flag == 3)
    {
        str_one = "1347";
        str_two = "23";
        str_three = "13579";
        str_four = "78";
    }

    cout << "A = " << str_one << endl;
    cout << "B = " << str_two << endl;
    cout << "C = " << str_three << endl;
    cout << "D = " << str_four << endl;

    auto time_1 = chrono::high_resolution_clock::now();
    binary_arr(str_one, str_two, str_three, str_four);
    auto time_2 = chrono::high_resolution_clock::now();
    auto dt = chrono::duration_cast<chrono::duration<double>>(time_2 - time_1);
    cout << "Time (binary array): " << dt.count() << endl;

    time_1 = chrono::high_resolution_clock::now();
    binary_word(str_one, str_two, str_three, str_four);
    time_2 = chrono::high_resolution_clock::now();
    dt = chrono::duration_cast<chrono::duration<double>>(time_2 - time_1);
    cout << "Time (machine word): " << dt.count() << endl;

    time_1 = chrono::high_resolution_clock::now();
    lst(str_one, str_two, str_three, str_four);
    time_2 = chrono::high_resolution_clock::now();
    dt = chrono::duration_cast<chrono::duration<double>>(time_2 - time_1);
    cout << "Time (list): " << dt.count() << endl;

    time_1 = chrono::high_resolution_clock::now();
    arr(str_one, str_two, str_three, str_four);
    time_2 = chrono::high_resolution_clock::now();
    dt = chrono::duration_cast<chrono::duration<double>>(time_2 - time_1);
    cout << "Time (array): " << dt.count() << endl;

    return 0;
}
