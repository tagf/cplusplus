#include "polynom.h"
#include <iostream>
#include <vector>
#include <string>

using namespace NPolynom;
using std::string;
using std::cout;
using std::endl;

void test06() {
    TPolynom<int> A(5);
    TPolynom<float> B;
    std::string init[] = {"abc", "def", "fgh"};
    TPolynom<std::string> S(init, 3);
    // TPolynom<int> N = {1,2,3,4,5};
    TPolynom<std::string> Scopy = S;
    cout << A << B << Scopy << endl;
}

void test134() {
    TPolynom<string> S1("a");
    TPolynom<string> S2("b");
    S1[2] = "well";
    S2[0] = "a";
    S2[2] = "well";
    S2[1] = "lol";
    if (S1 == S2) {
        cout << "bien" << endl;
    }
    cout << S1.Degree();
    cout << S2.Degree();
    
    S2[1] = "";
    if (S1 == S2) {
        cout << "bien" << endl;
    }
    cout << S1.Degree();
    cout << S2.Degree();
    
    S1[1] = "";
    S1[7] = "ok";
    cout << "S1: " << S1 << S1.Degree() << endl;
    
    cout << "S1 + S2: " << S1 + S2 << endl;
    TPolynom<string> S3 = S1 + S2;
    cout << "S1 + S2: " << S3 << S3.Degree() << endl;
    cout << (S1 + S2).Degree() << endl;
}

void testsum() {
    int _A[] = {1, 2, 1};
    int _B[] = {1, 0, -1};
    TPolynom<int> A(_A, 3);
    TPolynom<int> B(_B, 3);
    cout << B[10] << endl;
    cout << A + B << " " << (A + B).Degree() << endl;
    cout << ++B[10] << endl;
    cout << A + B << " " << (A + B).Degree() << endl;

}

void test_eq() {
    cout << "assignment test" << endl;
    int _A[] = {1, 2, 1, 0, 0, -7};
    int _B[] = {1, 0, -1};
    TPolynom<int> A(_A, 6);
    TPolynom<int> B(_B, 3);
    A += B = B;
    B += A = A;
    cout << A << " | " << A.Degree() << endl;
    cout << B << " | " << B.Degree() << endl;
}

void testmul() {
    cout << "MULTIPLICATION" << endl;
    int _A[] = {1, 2, 1};
    int _B[] = {1, 0, -1};
    TPolynom<int> A(_A, 3);
    TPolynom<int> B(_B, 3);
    // A = A*A;
    cout << " " << A*A << (A*A).Degree() << endl;
    A = A*A*A - A*2;
    cout << " " << A << A.Degree() << endl;
}

int main() {
    test06();
    test134();
    testsum();
    testmul();
    test_eq();
}
