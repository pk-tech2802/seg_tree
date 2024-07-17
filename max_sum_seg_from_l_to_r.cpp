
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

struct data{
    int sum,pre,suf,ans ;
} ;


int arr[10001] ;
data st[4*10001] ,lazy[4*10001];

data make_data(int val){
    data res ;
    res.sum = val ;
    res.suf = res.pre = res.ans = max(val,0) ;
    return res ;
}

data combine(data l, data r){
    data res ;
    res.sum = l.sum+r.sum ;
    res.pre = max(l.pre,l.sum+r.pre) ;
    res.suf = max(r.suf,r.sum+l.suf) ;
    res.ans = max(max(l.ans,r.ans),l.suf+r.pre) ;
    return res ;
}

void build(int si,int ss,int se){
    if(ss==se){
        st[si] = make_data(arr[ss]) ;
        // cout<<"si "<<si<<" ss "<<ss<<" se "<<se<<" -> sum: "<<st[si].sum<<" pre: "<<st[si].pre<<" suf: "<<st[si].suf<<" ans: "<<st[si].ans<<"\n";
        return ;
    }
    int mid = ss+(se-ss)/2 ;
    build(2*si,ss,mid) ;
    build(2*si+1,mid+1,se) ; 
    st[si] = combine(st[2*si],st[2*si+1]) ;

    // cout<<"si "<<si<<" ss "<<ss<<" se "<<se<<" -> sum: "<<st[si].sum<<" pre: "<<st[si].pre<<" suf: "<<st[si].suf<<" ans: "<<st[si].ans<<"\n";
}

data query(int si,int ss,int se,int qs,int qe){
    if(qs>se || qe<ss){
        data dm = make_data(-1e9) ;
        return  dm ; 
    }
    if(qs<=ss && se<=qe){
        // cout<<"si "<<si<<" ss "<<ss<<" se "<<se<<" -> sum: "<<st[si].sum<<" pre: "<<st[si].pre<<" suf: "<<st[si].suf<<" ans: "<<st[si].ans<<"\n";
        return st[si] ; 
    }

    int mid = ss+(se-ss)/2 ; 
    data left = query(2*si,ss,mid,qs,qe) ;
    data right = query(2*si+1,mid+1,se,qs,qe) ;

    data res = combine(left,right) ;

    return res ;
}

void update(int si,int ss,int se,int ind,int val){
    if(ss==se){
        arr[ind] = val ; 
        st[si] = make_data(arr[ind]) ;
        return ;
    }
    int mid = ss+(se-ss)/2 ;

    if(ind<=mid){
        update(2*si,ss,mid,ind,val) ;
    }
    else{
        update(2*si+1,mid+1,se,ind,val) ;
    }
    st[si] = combine(st[2*si],st[2*si+1]) ;
}
int main()
{   
    int n ;
    cin>>n ;
    fo(i,1,n+1){
        cin>>arr[i] ;
    }
    build(1,1,n) ;

    int q ;
    cin>>q ;
    while(q--){
        int qs,qe ;
        cin>>qs>>qe ;
        data dm = query(1,1,n,qs,qe);
        cout<<dm.ans<<"\n";
    }
    return 0;
}
