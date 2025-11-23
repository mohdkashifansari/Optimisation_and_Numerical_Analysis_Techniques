#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {

    int n;
    std::cout << "Dimension n = ";
    std::cin >> n;
    std::cout<< std::endl;

    double** A;
    A = new double*[n];
    for(int i = 0; i < n; i++) {
        A[i] = new double[n];
    }

    // Clean up memory
    for(int i = 0; i < n; i++) {
        delete[] A[i];
    }
    delete[] A;

    std:: vector<double> b(n);
    std:: vector<std:: vector<double> > B(n, std:: vector<double>(n, 0.0));

    //for(int i = 0; i < n; i++) {
    //    B[i].resize(n);
    //}

    return 0;
}