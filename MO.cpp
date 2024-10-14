/*
   صل عل محمد
   if (u == Abdel-Aziz Mostafa )   love u <3 ;
  دايما احلم ربنا المنان

*/

#include <bits/stdc++.h>
using namespace std;

template <typename  t>
ostream  &operator <<(ostream &os ,vector<t> & v){
    int s=v.size();
    for (int i=0;i<s;i++)
        os<<v[i]<<" ";
    cout<<"\n";
    return os;
}

template <typename  t>
ostream  &operator <<(ostream &os  ,multiset<t> & v){
    for (auto &val:  v)
        cout<<val.first<<" "<<val.second<<"|" ;
    cout<<"\n";
    return os;
}


#define int long long
#define F first
#define S second


const int N  = 2e5 +7 , sq= 300  ;

struct  query  {
       int  l ,  r, idx;
       bool operator< (query& other)  {
               if(other.l/sq  != l/sq)
                       return    l  < other.l ;
               return  ((l/sq)&1) ?  r > other.r  :  r<other.r;
       }
};

#define  item int
struct MO  {
       int sz , l = 0 , r=-1  , res = 0 /*empty*/;
       vector   <query > qu ;
       vector <int > nums , ans;

       MO (int n  , vector < int  > nums , vector <query >  qu) {
               sz = n  ;
               this->nums =  nums ;
               this->qu =  qu ;
               ans.resize(qu.size()) ;
               sort(this->qu.begin() , this->qu.end()) ;
               work() ;
       }

       void add(int x)   {
               res+=nums[x];
       }

       void del(int x)  {
               res-=nums[x];
       }

       void work()  {

              for (auto &[lq,rq , idx] : qu) {
                         while(r<rq)    add(++r)  ;
                         while(l > lq)  add(--l) ;

                        while(l  < lq)   del(l++) ;
                        while(r  > rq)   del(r--) ;
                        ans[idx] =  res;
              }
       }

       int query(int idx)  {
             return ans[idx] ;
       }

};
void  ICPC ()  {
    int  n ;
    cin >> n ;

    vector<int > a(n)  ;

    for (int  i = 0 ; i  < n ; ++i)  {
              cin>>a[i];
    }

    int q;
    cin  >> q;

    vector < query >  qu ;

    for (int  i = 0 ; i <q;  ++i)  {
              int  l , r  ;
              cin >>  l >> r;
              l--   , r --  ;

              qu.push_back({l , r, i}) ;
    }

    MO ob(n , a, qu)  ;

    for (int  i = 0 ; i  < q ; ++i)  {
              cout<<ob.query(i) <<"\n";
    }

}


int32_t main(){




    int tc=1;
    while(tc--)  {
        // cout<<"Case #"<<i++<<": ";
        ICPC() ;
    }


}

