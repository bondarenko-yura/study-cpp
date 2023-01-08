#include <iostream>
#include <complex>
#include <unordered_map>
#include "vector"
#include "numeric"

using namespace std;

constexpr int COMPILE_TIME_CONSTANT_COUNTER_START = 1;

int line_number = COMPILE_TIME_CONSTANT_COUNTER_START;

template<typename P>

void print_line(P arg) {
    std::cout << (line_number++) << " > " << arg << std::endl;
}

void print_divider(const string &name) {
    if (line_number > COMPILE_TIME_CONSTANT_COUNTER_START) {
        print_line("");
    }
    print_line(name + " ##########################################################################################");
}

string hello_world() {
    return "Hello World!";
}

int sumVector(const vector<int> &nums) { // sumVector will not modify vector because we use const
    // cpp 3+
    int a = 0;
    for (auto it = nums.begin(); it != nums.end(); it++)
        a += *it;

    // cpp 11+
    int b = 0;
    for (int n: nums)
        b += n;

    int c = 0;
    for (auto &n: nums)
        c += n;

    int d = 0;
    for (int i = 0; i < nums.size(); i++)
        d += nums[i];

    int e = accumulate(nums.begin(), nums.end(), 0);

    int f = 0;
    std::for_each(nums.begin(), nums.end(), [&](int n) {
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

void variable_init() {
    double d1 = 2.3;                       // initialize d1 to 2.3
    double d2{2.3};                       // initialize d2 to 2.3
    double d3 = {2.3};                     // initialize d3 to 2.3 (the = is optional with { ... })

    complex<double> z = 1;                 // a complex number with double-precision floating-point scalars
    complex<double> z2{d1, d2};
    complex<double> z3 = {d1, d2};   // the = is optional with { ... }

    vector<int> v{1, 2, 3, 4, 5, 6};      // a vector of ints
}

// what is the type of 'auto' for every line
void autoValue() {
    auto b = true;
    auto ch = 'x';
    auto i = 123;
    auto d = 1.2;
    auto z = sqrt(i);
    auto bb{true};
}

void pointers() {
    int base = 1;
    int *pointerToBase = &base;
    print_line(base);
    print_line(pointerToBase);
    print_line(*pointerToBase);
    base = 2;
    print_line(base);
    print_line(pointerToBase);
    print_line(*pointerToBase);
}

class ArrayList {
public:
    ArrayList(int s) :
        elem { new double[s] },
        sz { s }
        {}    // construct a ArrayList

    double &operator[](int i) {
        return elem[i]; // element access: subscripting
    }

    int size() {
        return sz;
    }

private:
    double *elem;  // pointer to the elements
    int sz;        // the number of elements
};

enum class Color { red, blue, green };

static void print(int a, int b = 2) {
    std::cout << "a=" << a << " b=" << b << std::endl;
}

class MyException : public exception {
public:
    explicit MyException(string& err) : err_(err) {
        print_line("Exception created with error: " + err);
    }

    string GetError() const {
        return this->err_;
    }

    bool operator==(MyException& that) const {
        return GetError() == that.GetError();
    }

private:
    string err_;
};

void willNotThrowException() {
    string error_msg = "Hello error";
    throw MyException(error_msg);
}

class Container {
public:
    virtual double& operator[](int) = 0;       // pure virtual function
    virtual int size() const = 0;              // const member function
    virtual ~Container() {}                    // destructor
};

class VectorContainer : public Container {    // VectorContainer implements Container
public:
    explicit VectorContainer(int s) : v_(vector<double>(s)) { }    // Vector of s elements
    ~VectorContainer() override {}

    double& operator[](int i) override { return v_[i]; }
    int size() const override { return v_.size(); }
private:
    vector<double> v_;
};

class ListContainer : public Container {    // ListContainer implements Container
public:
    explicit ListContainer(int s) : v_(vector<double>(s)) { }    // Vector of s elements
    ~ListContainer() override {}

    double& operator[](int i) override { return v_[i]; }
    int size() const override { return v_.size(); }
private:
    vector<double> v_;
};


void use(Container& c) {
    for (int i = 0; i < c.size(); i++)
        cout << c[i] << " " << endl;
}

static int IDS = 0;

class DemoType {
public:

    explicit DemoType(int id) : id_(id) {
        PrintDetails_("custom constructor");
    }

    DemoType() : id_(IDS++) {
        PrintDetails_("default constructor");
    }

    //    DemoType(const DemoType&) = delete;
    DemoType(const DemoType& t) : id_(t.id_) {
        PrintDetails_("copy constructor");
    }

    //    DemoType(DemoType&&) = delete;
    DemoType(DemoType&&) {
        PrintDetails_("move constructor");
    }

    //    DemoType& operator=(const DemoType&) = delete;
    DemoType& operator=(const DemoType& t) {
        id_ = t.id_;
        PrintDetails_("copy assignment: clean up target and copy");
        return *this;
    }

    //    DemoType& operator=(DemoType&&) = delete;
    DemoType& operator=(DemoType&&) {
        PrintDetails_("move assignment: clean up target and move");
    }

    ~DemoType() {
        PrintDetails_("destructor: clean up");
    }

    int GetId() const { return id_; }

private:
    int unique_id_ = IDS++;
    int id_ = -1;

    void PrintDetails_(const string& prefix) const {
        print_line(prefix + ", id: " + to_string(GetId()) + ", unique_id: " + to_string(unique_id_));
    }
};

void copyAndMove();

DemoType* makeDemoType(int id) {
    return new DemoType{id};
}

DemoType* merge(DemoType& a, DemoType& b) {
    return new DemoType(max(a.GetId(), b.GetId()) + 1);
}

int main() {
    copyAndMove();

    return 0;
}

void copyAndMove() {
    DemoType a0;            // default
    DemoType b0 = a0;       // copy constructor
    assert(&a0 != &b0);

    DemoType a1;            // custom
    DemoType b1;
    b1 = a1;              // copy assigment
    assert(&a1 != &b1);
    assert(a1.GetId() == b1.GetId());

    auto c0 = unique_ptr<DemoType>(makeDemoType(1000)); // only one new object
    auto c1 = unique_ptr<DemoType>(merge(*c0, a0));
}

