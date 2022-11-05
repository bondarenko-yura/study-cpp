#include <iostream>
#include "vector"
#include "numeric"

using namespace std;

constexpr int COMPILE_TIME_CONSTANT_COUNTER_START = 1;

int line_number = COMPILE_TIME_CONSTANT_COUNTER_START;

template <typename P>

void print_line(P arg) {
    std::cout << (line_number++) << " > " << arg << std::endl;
}

void print_divider(const string& name) {
    if (line_number > COMPILE_TIME_CONSTANT_COUNTER_START) {
        print_line("");
    }
    print_line(name + " ##########################################################################################");
}

string hello_world() {
    return "Hello World!";
}

int sumVector(const vector<int>& nums) { // sumVector will not modify vector because we use const
    // cpp 3+
    int a = 0;
    for (auto it = nums.begin(); it != nums.end(); it++)
        a += *it;

    // cpp 11+
    int b = 0;
    for (int n : nums)
        b += n;

    int c = 0;
    for (auto& n : nums)
        c += n;

    int d = 0;
    for (int i = 0; i < nums.size(); i++)
        d += nums[i];

    int e = accumulate(nums.begin(), nums.end(), 0);

    int f = 0;
    std::for_each(nums.begin(), nums.end(), [&] (int n) {
        f += n;
    });

    // cpp 17+
    int g = std::reduce(nums.begin(), nums.end());

    // check output
    print_line(a == b && a == c && a == d && a == e && a == f && a == g ? "are same" : "not same");
    return a;
}

struct Employee {
    string name;
    int age;

    void print_line() const {
        ::print_line("self " + name + " " + to_string(age));
    }
};

int main() {
    print_divider("Class");
    auto employee = new Employee{"Yurii", 30};
    print_line("global " + employee->name + " " + to_string(employee->age));
    employee->print_line();
    vector<int> vector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    sumVector(vector);

    print_divider("Variables");
    double d1 = 2.3;
    double d2 {2.3};
    double d3 = {2.3};
    print_line(to_string(d1) + " " + to_string(d2) + " " + to_string(d3));

    print_divider("Math operations");
    int a = 1;
    print_line(a++);
    print_line(++a);
    print_line(a + 2);
    print_line(a - 2);
    print_line(a & 1);

    print_divider("HW");
    print_line(hello_world());
    return 0;
}

