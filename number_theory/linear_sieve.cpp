#include <bits/stdc++.h>

#ifdef DEBUG
#define PRINT(x)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#x<<" = "<<(x)<<endl;
#define PRINTA(a,first,last)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#a<<"["<<(first)<<", "<<(last)<<")"<<endl;\
    for (int i=(first);i<(last);++i){cout<<#a<<"["<<i<<"] = "<<(a)[i]<<endl;}
#define PRINTP(p)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#p<<" = ("<<(p.first)<<", "<<(p.second)<<")"<<endl;
#define PRINTI(a,i)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#a<<"["<<#i<<"] = "<<#a<<"["<<(i)<<"] = "<<(a)[i]<<endl;
#else
#define PRINT(x)
#define PRINTA(a,first,last)
#define PRINTP(p)
#define PRINTI(a,i)
#endif

#define FOR(i,a,b) for (int i=(a);i<(b);++i)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);--i)
#define REP(i,n) for (int i=0;i<(n);++i)
#define RREP(i,n) for (int i=(n)-1;i>=0;--i)
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()

using namespace std;

vector<int> linear_sieve(int N) {

    vector<bool> is_prime(N, true);
    vector<int> primes;
    
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

vector<map<int, int>> linear_sieve_factorize(int N) {

    vector<bool> is_prime(N, true);
    vector<int> primes;
    vector<map<int, int>> factors(N);
    
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

vector<int> linear_sieve_totient(int N) {

    vector<bool> is_prime(N, true);
    vector<int> primes;
    vector<int> totient(N, 0);

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

vector<int> naive_totient(int N) {
    vector<int> totient(N, 0);
    totient[1] = 1;
    for (int i = 2; i < N; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("gcd(%d, %d) = %d\n", i, j, gcd(i, j));
            if (gcd(i, j) == 1) {
                ++totient[i];
            }
        }
    }
    return totient;
}

int main() {

    auto primes = linear_sieve(100);
    PRINTA(primes, 0, primes.size());

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

    return 0;
}
