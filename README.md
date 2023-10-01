# how-to-make-a-set-in-C-without-using-set-
This is my weird university work about data structures in C++. Here I compare four ways to make set and unification and intersrction functions for it - via array, list, machine word and binary array. Just one thing - this code is especially for decimal digits (cause it was my task). But you can rewrite it for other sets - algorithms here are almost all-purpose.

Specifically in this task I must from 4 given (in different ways) sets calculate the fufth one using this formula:

E = A & B || C || D

# Which way is better?
For small input data sets, such as sets of decimal digits (from 1 to 10 elements), arrays and linked lists exhibit the best time performance because their complexity depends on the number of elements in the set.
For larger data sets, bit array and machine word algorithms are more efficient since their complexity is constant. Below you can see time indicators for different tests.

![image](https://github.com/pipopolam-03/how-to-make-a-set-in-C-without-using-set-/assets/69760973/5f4091eb-9122-4c32-b774-fd2f34b355d9)

# Array
In this work it was forbidden to use  <vector>, although I really wanted to, so functions works through ordinary arrays.
How to make set you can see in thw full code. Now you just need to know that all arrays has length=10 (some decimal digits without repeating and -1 in other places).
```
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
```

# List

To be more precise, a linear singly linked list. It is done in a standard way:

```
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

void insert(ListSet& set, int val) {
    if (!contains(set, val)) {
        set.head = new SetElement(val, set.head);
    }
}
```

Operations for it looks like this:

```
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
```
# Binary array and machine word

```
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

////
final_set = final_set | set_three | set_four;     - for bin word
////
```

