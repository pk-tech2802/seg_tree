// worse worse complexity 

#include <bits/stdc++.h>
using namespace std;
#define fo(i, s, e) for (int i = s; i < e; i++)
typedef long long ll;
#define ff first
#define ss second
#define in insert
#define all(x) x.begin(), x.end()
#define pb push_back
using vi = vector<int>;
using vvi = vector<vector<int>>;

int mod = 998244353;

int seg(vector<int>&v,int s,int e,int req_s,int req_e){
    
    if(s>req_e||e<req_s){
        return INT_MAX ;
    }
    if(s==e){
        return v[s] ;
    }

    int mid = (s+e)/2 ;
    int m1 = seg(v,s,mid,req_s,req_e) ;
    int m2 = seg(v,mid+1,e,req_s,req_e) ;

    return min(m1,m2) ;
}
int main()
{   
    vector<int> v={1,5,2,-3,4,-1} ;
    cout<<seg(v,0,5,1,1)<<"\n";
    return 0;
}
