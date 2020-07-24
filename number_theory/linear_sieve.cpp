#include <map> // std::map
#include <vector> // std::vector

std::vector<int> linear_sieve_prime(int N) {

    std::vector<bool> is_prime(N, true);
    std::vector<int> primes;
    
    for (int i = 2; i < N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int p: primes) {
            int n = i * p;
            if (n >= N) {
                break;
            }
            is_prime[n] = false;
            if (i % p == 0) {
                break;
            }
        }
    }

    return primes;
}

std::vector<int> naive_prime(int N) {

    std::vector<int> primes = {2};

    for (int n = 3; n < N; n += 2) {
        bool is_prime = true;
        for (int p: primes) {
            if (p * p > n) {
                break;
            }
            if (n % p == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(n);
        }
    }

    return primes;
}

std::vector<std::map<int, int>> linear_sieve_factorize(int N) {

    std::vector<bool> is_prime(N, true);
    std::vector<int> primes;
    std::vector<std::map<int, int>> factors(N);
    
    for (int i = 2; i < N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            ++factors[i][i];
        }
        for (int p: primes) {
            int n = i * p;
            if (n >= N) {
                break;
            }
            is_prime[n] = false;
            factors[n] = factors[i];
            ++factors[n][p];
            if (i % p == 0) {
                break;
            }
        }
    }

    return factors;
}

std::vector<int> linear_sieve_totient(int N) {

    std::vector<bool> is_prime(N, true);
    std::vector<int> primes;
    std::vector<int> totient(N, 0);

    totient[1] = 1;

    for (int i = 2; i < N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            totient[i] = i - 1;
        }
        for (int p: primes) {
            int n = i * p;
            if (n >= N) {
                break;
            }
            is_prime[n] = false;
            if (i % p == 0) {
                totient[n] = totient[i] * p;
                break;
            } else {
                totient[n] = totient[i] * (p - 1);
            }
        }
    }

    return totient;
}

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

std::vector<int> naive_totient(int N) {
    std::vector<int> totient(N, 0);
    totient[1] = 1;
    for (int i = 2; i < N; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (gcd(i, j) == 1) {
                ++totient[i];
            }
        }
    }
    return totient;
}

std::vector<std::vector<int>> linear_sieve_divisors(int N) {

    std::vector<bool> is_prime(N, true);
    std::vector<int> primes;
    std::vector<std::vector<int>> divisors(N);

    divisors[1] = {1};
    
    for (int i = 2; i < N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            divisors[i] = {1, i};
        }
        for (int p: primes) {
            int n = i * p;
            if (n >= N) {
                break;
            }
            is_prime[n] = false;
            divisors[n] = divisors[i];
            if (i % p == 0) {
                int j = i / p;
                int pow_p = p;
                while (j % p == 0) {
                    j /= p;
                    pow_p *= p;
                }
                for (int d: divisors[i]) {
                    if (d % pow_p == 0) {
                        divisors[n].push_back(d * p);
                    }
                }
                break;
            } else {
                for (int d: divisors[i]) {
                    divisors[n].push_back(d * p);
                }
            }
        }
    }

    return divisors;
}

vector<int> number_of_divisors(int N) {
 
    vector<bool> is_prime(N, true);
    vector<int> primes;
    vector<int> n_divisors(N);
    
    n_divisors[1] = 1;
    
    FOR(i, 2, N + 1) {
        if (is_prime[i]) {
            primes.pb(i);
            n_divisors[i] = 2;
        }
        for (int p: primes) {
            ll n = i * p;
            if (n >= N) {
                break;
            }
            is_prime[n] = false;
            if (i % p == 0) {
                ll j = i / p;
                ll e = 1;
                while (j % p == 0) {
                    j /= p;
                    e += 1;
                }
                n_divisors[n] = n_divisors[i] / (e + 1) * (e + 2);
                break;
            } else {
                n_divisors[n] = n_divisors[i] * 2;
            }
        }
    }
                
    return n_divisors;
}

int main() {

    /*
    auto totient = naive_totient(100);
    PRINTA(totient, 0, totient.size());

    auto totient2 = linear_sieve_totient(100);
    PRINTA(totient2, 0, totient2.size());

    for (int n = 1; n < 100; ++n) {
        printf("phi(%d) = %d, phi2(%d) = %d\n", n, totient[n], n, totient2[n]);
        assert(totient[n] == totient2[n]);
    }

    auto factors = linear_sieve_factorize(100);
    for (int n = 1; n < 100; ++n) {
        printf("%d = ", n);
        for (const auto &[p, e]: factors[n]) {
            printf("%d^%d ", p, e);
        }
        printf("\n");
    }

    int N;
    cin >> N;
    */

    // enumerate primes
    /*
    auto start = chrono::system_clock::now();
    auto primes = linear_sieve_prime(N);
    auto end = chrono::system_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "liearn_sieve_prime(" << N << ") took time" << diff.count() << endl;

    start = chrono::system_clock::now();
    auto primes2 = naive_prime(N);
    end = chrono::system_clock::now();
    diff = end - start;
    cout << "naive_prime(" << N << ") took time" << diff.count() << endl;

    assert(primes.size() == primes2.size());

    for (int i = 0; i < primes.size(); ++i) {
        assert(primes[i] == primes2[i]);
        //printf("primes[%d] = %d\n", i, primes[i]);
    }
    */

    return 0;
}
