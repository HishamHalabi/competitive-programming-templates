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
#define  item int
/*
    case processing   : write dif codes depending on constarints
    batch  //   :   push updates while they are  < sq and answer by iterating over them if they exeed sq update them once 
    heavy && light  :  simple graph such that if u change any node update heavy ones and when answer some light node just brute force 
    Blocks and query (seg tree )  
    Just Blocks and imagine simple arrays :  first time to out of array ( what i to out form block?? )

*/
struct   SQRT {
      //update Neutral  , merge , item
/*
    if u wuold like to change sq value remeber those data that of size  n  /sq and we make them sq
*/

      int sz , sq ;
      vector < item > blocks;
      vector < item  > nums ;

      item single (int v)  {
                return v;
      }

      item merge(int a,  int b)  {
              return min(a,b);
      }

      item Neutral_elemnt = 2e18 ;         // the only use of this is as init so y can del

      SQRT(int sz , vector < int >  values)  {
               this->sz = sz ;
               nums = values ;
               sq= sqrt(sz) +2 ;
               blocks.assign(2*sq , Neutral_elemnt)  ;
               for (int i =   0 ; i <sz; ++i)  {
                        blocks[i/sq] = merge(blocks[i/sq] , nums[i]);
               }
      }



      void update  (int idx , int v)  {      //  sometimes can be optimized to O(1) if u dont need to see all elems
               int b  = idx /  sq ;
               nums[idx] = v;
               item res = Neutral_elemnt ;
               int  l =  b * sq , r  = l+sq - 1;

               for (int   i  = l ; i<=r; ++i){
                          res= merge(res, single(nums[i])) ;
               }
               blocks[b] =  res;
      }

      int query (int l ,  int r )  {
              item ret= Neutral_elemnt ;
              for (int  i  = l  ; i <=r;  ++i)  {
                        if (i%sq==0 and i+sq-1<=r)  {
                                ret   = merge(ret, blocks[i/sq] ) ;
                                i+=sq-1;
                                continue ;
                        }
                        ret = merge(ret, nums[i]) ;

              }
              return ret;
      }

};

void  ICPC ()  {

      int n  ,q  ;
      cin >> n >>q ;

      vector  <int > values(n) ;

      for (int  i =  0 ; i  <n ; ++i) {
                cin>> values[i] ;
      }

      SQRT tmp (n ,  values)  ;


      while(q--)  {
              int  k ;   cin >> k ;

              if(k==1) {
                     int idx,  v;
                     cin >> idx>>v;
                     idx--;       //0bas
                     tmp.update(idx, v)  ;
              }
              else  {
                      int  l , r;
                      cin >>  l  >> r ;
                      l-- ; r-- ; // 0based
                      cout<<tmp.query( l  , r)  <<"\n";
              }
      }


}


int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0) ;



    int tc=1 ;
    int i = 1;
    while(tc--)  {
        // cout<<"Case #"<<i++<<": ";
        ICPC() ;
    }


}
