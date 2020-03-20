#include <iostream> // std::cout, std::endl
#include <string> // std::string
#include <vector> // std::vector

using young_diagram = std::vector<int>;

void pretty_print(young_diagram lambda) {
    std::cout << std::endl;
    for (int a: lambda) {
        std::cout << std::string(a, 'O') << std::endl;
    }
    std::cout << std::endl;
}

young_diagram conjugate(young_diagram lambda) {
    young_diagram lambda_conjugate(lambda[0]);
    int m = lambda.size();
    int j = 0;
    for (int i = m; i > 0; --i) {
        int d = lambda[i - 1] - (i < m ? lambda[i] : 0);
        int stop = j + d;
        for (; j < stop; ++j) {
            lambda_conjugate[j] = i;
        }
    }
    return lambda_conjugate;
}
