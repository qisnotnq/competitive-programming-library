#include <vector> // std::vector

template <class String>
std::vector<size_t> knuth_morris_pratt(const String &text, const String &pattern) {

    const size_t N = text.size();
    const size_t M = pattern.size();
    int i, j;

    // lps[i] is the length of the longest proper prefix and suffix of pattern[:i + 1].
    std::vector<size_t> lps(M);
    lps[0] = 0;
    i = 1;
    j = 0;
    while (i < M) {
        if (pattern[i] == pattern[j]) {
            lps[i++] = ++j;
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            lps[i++] = 0;
        }
    }

    std::vector<size_t> result;
    i = 0;
    j = 0;
    while (i < N) {
        if (text[i] == pattern[j]) {
            ++i;
            if (j < M - 1) {
                ++j;
            } else {
                result.push_back(i - M);
                j = lps[M - 1];
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }

    return result;
}
