#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Manacher's algorithm on transformed string (with separator '$')
vector<int> manacher(const string& t) {
    int n = t.size();
    vector<int> P(n, 0);
    int center = 0, right = 0;

    for (int i = 0; i < n; i++) {
        int mirror = 2 * center - i;

        if (i < right)
            P[i] = min(right - i, P[mirror]);

        // Try to expand palindrome centered at i
        while (i + P[i] + 1 < n && i - P[i] - 1 >= 0 && t[i + P[i] + 1] == t[i - P[i] - 1])
            P[i]++;

        // Update center and right boundary
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }
    return P;
}

// Build transformed string with separators
string buildTransformed(const string& s) {
    string t = "$";
    for (char c : s) {
        t.push_back(c);
        t.push_back('$');
    }
    return t;
}

// Count palindromes centered at each position in original string
vector<int> countPalindromeCenters(const string& s) {
    string t = buildTransformed(s);
    vector<int> P = manacher(t);

    int n = s.size();
    vector<int> cnt(n, 0);

    for (int i = 0; i < (int)P.size(); i++) {
        int radius = P[i];
        if (radius == 0) continue;

        // Number of palindromes centered at i (in transformed string)
        // Each expansion adds one palindrome (radius counts max expansion)
        // The number of palindromes centered at i is (radius + 1)/2

        int center_count = (radius + 1) / 2;

        if (i % 2 == 1) {
            // Odd index in transformed string -> corresponds to character in original string
            int center_s = (i - 1) / 2;
            if (center_s >= 0 && center_s < n)
                cnt[center_s] += center_count;
        } else {
            // Even index in transformed string -> between characters -> add to left index
            int left_center = (i / 2) - 1;
            if (left_center >= 0 && left_center < n)
                cnt[left_center] += center_count;
        }
    }
    return cnt;
}

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    vector<int> counts = countPalindromeCenters(s);

    cout << "Palindrome centers counts:\n";
    for (int i = 0; i < (int)s.size(); i++) {
        cout << "Index " << i << " ('" << s[i] << "'): " << counts[i] << " palindromes centered\n";
    }

    return 0;
}
