//f(x) = 0
#include <bits/stdc++.h>
using namespace std;
#define int long long 


#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct SlopeTrick {
    using ll = long long;
    const ll INF = 4e18; // Safe infinity to avoid overflow when adding bounds
    
    ll addL = 0, addR = 0, min_f = 0;
    priority_queue<ll> L; 
    priority_queue<ll, vector<ll>, greater<ll>> R;

    // Helper functions to get absolute positions of the internal boundaries
    ll topL() { return L.empty() ? -INF : L.top() + addL; }
    ll topR() { return R.empty() ? INF : R.top() + addR; }

    // Helper functions to push relative values into the priority queues
    void pushL(ll x) { L.push(x - addL); }
    void pushR(ll x) { R.push(x - addR); }

    SlopeTrick() {}

    // f(x) += c 
    // Shifts the entire function up vertically by a constant cost
    void add_c(ll c) {
        min_f += c;
    }

    // f(x) += max(0, x - a)
        void add_R(ll a) {
        if (!L.empty() && a < topL()) {
            min_f += topL() - a;
            pushL(a);
            ll x = L.top() + addL; L.pop();
            pushR(x);
        } else {
            pushR(a);
        }
    }

    // f(x) += max(0, a - x)
     void add_L(ll a) {
        if (!R.empty() && a > topR()) {
            min_f += a - topR();
            pushR(a);
            ll x = R.top() + addR; R.pop();
            pushL(x);
        } else {
            pushL(a);
        }
    }

    // f(x) += |x - a|
       void add_abs(ll a) {
        if (L.empty() && R.empty()) {
            pushL(a); pushR(a); return;
        }
        ll max_L = topL(), min_R = topR();
        if (a < max_L) {
            min_f += max_L - a;
            L.pop(); pushL(a); pushL(a); pushR(max_L);
        } else if (a > min_R) {
            min_f += a - min_R;
            R.pop(); pushR(a); pushR(a); pushL(min_R);
        } else {
            pushL(a); pushR(a);
        }
    }

    // f(x) = f(x - c)
    // Shifts the entire function horizontally to the right by 'c' units
    void shift(ll c) {
        addL += c; addR += c;
    }

    // f(x) = min_{y <= x} f(y)
    // Clears right slopes, making the function monotonically non-increasing
    void clear_R() {
        while (!R.empty()) R.pop();
    }

    // f(x) = min_{y >= x} f(y)
    // Clears left slopes, making the function monotonically non-decreasing
    void clear_L() {
        while (!L.empty()) L.pop();
    }

    // f(x) = min_{x - l <= y <= x + r} f(y)
    // Slides/expands the minimum plateau: shifts left slope left by 'l', right slope right by 'r'
    void slide(ll l, ll r) {
        addL -= l; addR += r;
    }

    // returns min f(x)
     ll get_min() {
        return min_f;
    }

    // returns pair<left_bound, right_bound>
    // Returns the range [x_1, x_2] where the function achieves its minimum value
    pair<ll, ll> get_min_range() { 
        return {topL(), topR()}; 
    }

    // O(log N) Smart Evaluation
    ll eval(ll x) {
        ll res = min_f;
        vector<ll> rec;
        // Evaluate if x is to the left of the minimum plateau
        while (!L.empty() && topL() > x) { 
            res += topL() - x; 
            rec.push_back(L.top()); L.pop(); 
        }
        for (ll v : rec) L.push(v);
        rec.clear();
        
        // Evaluate if x is to the right of the minimum plateau
        while (!R.empty() && topR() < x) { 
            res += x - topR(); 
            rec.push_back(R.top()); R.pop(); 
        }
        for (ll v : rec) R.push(v);
        return res;
    }

    // f(x) = f(x) + other(x)
    // Merges two independent functions using Small-to-Large optimization: O(log^2 N) overall
    void merge(SlopeTrick& other) {
        if (L.size() + R.size() < other.L.size() + other.R.size()) {
            swap(addL, other.addL); swap(addR, other.addR);
            swap(min_f, other.min_f); swap(L, other.L); swap(R, other.R);
        }
        min_f += other.min_f;
        while (!other.L.empty()) { 
            add_L(other.L.top() + other.addL); 
            other.L.pop(); 
        }
        while (!other.R.empty()) { 
            add_R(other.R.top() + other.addR); 
            other.R.pop(); 
        }
    }
};
signed main () { 
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);

     int n , k; 
     if (!(cin >> n >> k)) return 0;  
     
     SlopeTrick slp;
     vector<int> a(n + 1);
     
     for (int i = 1; i <= n; ++i) cin >> a[i];   
    
     slp.add_abs(a[1]); 
     for (int i = 2; i <= n; ++i) {
         slp.slide(k, k);  
         slp.add_abs(a[i]);
     }
     
     cout << slp.get_min() << "\n";    
     return 0;
}When TO think 




Is functions Slope Trickable ? 
  Quick test : 
      look at the last part (i'll give the 12 operation and how to change the old function by them)
   
  Poor test :  
    1.s Continuous and Piecewise Linear  :he graph of the function is made entirely of connected straight line segments (like     a jagged valley).
    2.convex (slope non increasing from lft to rgt)
    3.slope of this parts is integer 
------------------------------------------------------------------------

Solution : 
     1. look f(x)  is the function we change function one by one till finaly be the result that we need to study best on
 it  
     2. Keep Track of important Xs that hv best

 How to update ?  
     1.we store the points that slope changing at if slope changes by by 3 for ex we store the x 3 times in the queue
     2. 2 PQs one for <0 and other for  >0 so hence the function is convex
                             we always interested in best f(x) in rng f (x  Max(lft pq)   : Min (rght pq)) 
                             we keep Lvalue  ,R value as f(lft)  ,f(rght)   because we need them to update f(x) easily based on only slope and entering point
                                                       //change in x will determine change on y based on slope !!


    

     So we only need to DO like for each x make f(x)  ..... , with updating info upove so we did the task  
     u have function of combination basic 12 type of functions with +  ,  - btw them 
     here's how to go from fx  to f(x) +  c for example  (f(x) is valid )
