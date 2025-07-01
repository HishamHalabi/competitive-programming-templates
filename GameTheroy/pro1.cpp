
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define F first
#define S second
#define all(v) v.begin(), v.end()

const int N =  1e6+1;
vector <vector< int > > divs(N) ;

int Mex(vector<int> v) {
    int n = v.size() ;
    vector <bool > exist(n)  ;

    for  (int i = 0 ; i  < n ; ++i)if(v[i]  <  n )exist[v[i]] = true ;
    for (int i = 0 ; i  < n ; ++i)  {
        if (!exist[i]) return i ;
    }
    return n  ;
}


int gr[N] ;
int grundy (int n)  {

     if  (n == 1)return 0 ;

    int &ret = gr[n] ;
    if(~ret) return ret  ;

    vector <int > temp ;
    for (auto x  : divs[n]) {
        if  (n   / x >  1 ) {
               if((n/x)&1)   temp.push_back(grundy(x));
               else temp.push_back(0) ; 
        }

    }
    return ret = Mex(temp) ;
}

void testCases() {
    int n  ;
    cin >> n   ;



    int xo = 0 ;
    for (int  i = 0  ;     i  < n ; ++i) {
             int v ;
             cin>> v;
             xo^=grundy(v) ;
             //cout<<v <<" "<<grundy(v)<<"\n";
    }

    if(xo)cout<<"1"<<"\n";
    else cout<<"2"<<"\n";




}

int32_t main() {

    for (int  i=1  ; i < N ;++i) {
        for (int j =  i  ;  j  <  N ; j+=i)  {
            divs[j].push_back(i) ;
        }
    }

    memset(gr , -1 , sizeof gr) ;

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        testCases() ;
    }
}
