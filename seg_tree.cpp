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

int st[10001] ;

int BuildTree(int si,int ss,int se,vector<int>&v){
    if(ss==se){
        return st[si] = v[ss-1] ;
    }
    int mid = (ss+se)/2;
    int n1 = BuildTree(si*2,ss,mid,v);
    int n2 = BuildTree(si*2+1,mid+1,se,v);

    return st[si] = min(n1,n2);
}

int query(int si ,int ss,int se,int qs ,int qe){
    if(ss>qe || se<qs){  // completely outside
        return 1e9 ;
    }

    if(qs<=ss && se<=qe){ // completely inside 
        return st[si] ;
    }

    int mid = (ss+se)/2; 
    int l = query(si*2,ss,mid,qs,qe) ;
    int r = query(si*2+1,mid+1,se,qs,qe) ;

    return min(l,r) ;
}

void update(int si ,int ss,int se,int qi ,vector<int>&v){
    if(ss==se ){
        st[si] = v[ss-1] ;
        return ;
    }
    int mid = (ss+se)/2 ;
    if(qi<=mid){
        update(si*2,ss,mid,qi,v) ;
    }
    else{
        update(si*2+1,mid+1,se,qi,v) ;
    }

    st[si] = min(st[si*2],st[si*2+1]) ;
}
int main()
{   
    vector<int> v={1,5,2,-3,4,-1} ;
    BuildTree(1,1,v.size(),v) ;
    cout<<query(1,1,v.size(),5,6)<<"\n" ;
    v[5]=-10 ;
    update(1,1,6,6,v) ;
    cout<<query(1,1,v.size(),5,6)<<"\n" ;
    return 0;
}
