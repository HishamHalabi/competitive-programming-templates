
#include <bits/stdc++.h>
using namespace std;




#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// Template definition for ordered_set
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define F first
#define S second
#define int long long
#define all(a) a.begin() , a.end()
#define ld long double


struct  item  {
    bool operator<(const item& other) const {
        return 2 < 3;
    }
};

#define ll int
ll random_int(ll l , ll r){
    static mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(l,r)(rng);
}



template<int mod>
struct Mint {
  int x;
  Mint() : x(0) {}
  Mint(ll x_) : x(x_ % mod) { if (x < 0) x += mod; }
  Mint& operator += (Mint b) { if ((x += b.x) >= mod) x -= mod; return *this;}
  Mint& operator -= (Mint b) { if ((x -= b.x) < 0) x += mod; return *this;}
  Mint& operator *= (Mint b) { x = (ll)(x) * b.x % mod; return *this;}
  Mint pow(ll e) const {
		Mint r = 1;
		for (Mint b = *this; e; b *= b, e >>= 1)
			if (e & 1) r *= b;
    return r;
  }
  Mint inv() { return pow(mod - 2); }
  Mint& operator /= (Mint b) { return *this *= b.inv(); }
  friend Mint operator +  (Mint a, Mint b) { return a += b;     }
  friend Mint operator -  (Mint a, Mint b) { return a -= b;     }
  friend Mint operator /  (Mint a, Mint b) { return a /= b;     }
  friend Mint operator *  (Mint a, Mint b) { return a *= b;     }
  friend bool operator == (Mint a, Mint b) { return a.x == b.x; }
  friend bool operator != (Mint a, Mint b) { return a.x != b.x; }
};

typedef Mint<998244353> mint;

int Bit(int mask , int bitIndx){ //val[bit]
   return  (mask >> bitIndx) & 1LL == 1LL;
}

void Set(int &mask , int bitIndx , int val){
  if (!val)
    mask = mask & ~(1LL << bitIndx);
  else
    mask = mask | (1LL << bitIndx);
}



void testCase()   {
   int n    ;
   cin >> n ;


   if (n%2 == 0)  {
       for (int i  = 1; i <=n ;  i+=2)  {
           cout<<i <<" "<<i+1<<" "<<i<<" "<<i<<" "<<i+1<<" "<<i+1<<" "<<i <<" "<<i+1<<" " ;
       }
       cout <<"\n";
       return  ;
   }
   cout <<"1 1 2 1 2 3 1 3 2 2 3 3 ";
   for (int i  = 4; i <=n ;  i+=2)  {
           cout<<i <<" "<<i+1<<" "<<i<<" "<<i<<" "<<i+1<<" "<<i+1<<" "<<i <<" "<<i+1<<" " ;
   }
   cout <<"\n";


}

int32_t main() {
    ios_base::sync_with_stdio(0) ;
    cin.tie(0 ) ;


     long long tc  =1;
     cin >> tc ;
     while(tc-- )   {
          testCase() ;
     }
}
