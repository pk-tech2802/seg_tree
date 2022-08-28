// Q find the no of distinct elements in given segment 

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

vi st[10001]  ;
void build(int si,int ss,int se,vi &v){
    if(ss==se){
        st[si] = {v[ss-1]} ;
        // cout<<"si : "<<si<<" -> ";
        // for(auto x : st[si]){
        //     cout<<x<<" " ;
        // }
        // cout<<"\n" ;

        return ;
    }
    int mid = (ss+se)/2;
    build(si*2,ss,mid,v);
    build(si*2+1,mid+1,se,v);

    int i = 0 , j=0 ;
    while(i<st[si*2].size() && j<st[si*2+1].size()){
        if(st[si*2][i]<st[si*2+1][j]){
            st[si].pb(st[si*2][i]) ;
            i++ ;
        }
        else{
            st[si].pb(st[si*2+1][j]) ;
            j++ ;
        }
    }

    while(i<st[si*2].size()){
        st[si].pb(st[si*2][i]) ;
        i++ ;
    }

    while(j<st[si*2+1].size()){
        st[si].pb(st[si*2+1][j]) ;
        j++ ;
    }
    // cout<<"si : "<<si<<" -> ";
    // for(auto x : st[si]){
    //     cout<<x<<" " ;
    // }
    // cout<<"\n" ;
    return ;
}

void query(int si,int ss,int se,int qs,int qe,set<int>&s){
    
    if(ss>qe||se<qs){//completely outside
        return ;
    }

    if(ss>=qs && se<=qe){ // completely inside 
        for(auto x : st[si]){
            s.insert(x) ;
        }
        // cout<<"si : "<<si<<" -> " ;
        // for(auto x : s){
        //     cout<<x<<" " ;
        // }
        // cout<<"\n" ;
        return ;
    }

    int mid = (ss+se)/2 ;
    query(si*2,ss,mid,qs,qe,s) ;
    query(si*2+1,mid+1,se,qs,qe,s) ;
    // cout<<"si : "<<si<<" -> " ;
    // for(auto x : s){
    //     cout<<x<<" " ;
    // }
    // cout<<"\n" ;
}
int mod = 998244353;
int main()
{   
    vector<int> v={1,2,1,1,2,1,2,3,4,2,2,1} ;
    build(1,1,v.size(),v);
    set<int>s ;
    query(1,1,v.size(),10,12,s) ;
    cout<<s.size() ;
    return 0;
}
