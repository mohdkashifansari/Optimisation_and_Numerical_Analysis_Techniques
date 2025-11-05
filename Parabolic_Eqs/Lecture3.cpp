#include <iostream>

double get(double * A , int i, int j, int dim) {
    return A[i*dim + j];
}

int main() {
    int n;
    std::cout << "Dimension: ";
    std::cin >> n;
    double** a= new double*[n];
    for (int i=0; i<n; i++) {
        a[i] = new double[n];
    }
    a[1][2] = 3.14;
    std::cout << a[1] << std::endl;
   
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;

    // int a =1;
    // int* p= &a;
    // *p +=1;
    // std::cout << a << std::endl;

    // char a[5];// = "abcd";
    // std::cout << a << std::endl;


    return 0;
}
// heap and stack memory allocation