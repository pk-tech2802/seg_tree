
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
int arr[10001] ;
int st[10001] ,lazy[10001];

void build(int si,int ss,int se){
    if(ss==se){
        st[si] = arr[ss] ;
        return ;
    }
    int mid = (ss+se)/2 ;
    build(si*2,ss,mid) ;
    build(si*2+1,mid+1,se) ;

    st[si] = st[si*2]+st[si*2+1] ;
}

int query(int si,int ss,int se,int qs,int qe){

    if(lazy[si]!=0){ // found 1 seg need to be updated 
        int dx = lazy[si] ;

        lazy[si]=0 ; // update and make curr pending update 0
        st[si]+=(dx*(se-ss+1)) ; // add seg size*val to the curr seg sum 
        
        if(ss!=se){
            lazy[si*2]=dx,lazy[si*2+1]=dx ; // we made change in par seg but if exist childs make them to inherit the change
        }
    }

    if(ss>qe || se<qs){//completely inside 
        return 0 ;
    }

    if(ss>=qs && se<= qe){
        return st[si] ; // completely inside 
    }

    int mid = (ss+se)/2;
    int q1 = query(si*2,ss,mid,qs,qe) ;
    int q2 = query(si*2+1,mid+1,se,qs,qe) ;

    return q1+q2 ;
}

void update(int si,int ss,int se,int qs,int qe,int val){
    if(lazy[si]!=0){
        int dx = lazy[si] ; // pending update found 
        st[si]+=dx*(se-ss+1) ; // update set sum by adding segsize*val
        lazy[si]=0 ; // make pending update to the cuur node to be 0 
        if(ss!=se){
            lazy[si*2]+=dx ; // if childs exist make child segment to inherit change 
            lazy[si*2+1]+=dx ;// i.e if there is already pending update in child seg and we are sending another update from par , simply add the updateds
        }
    }

    if(ss>qe || se<qs){ //completely outside 
        return ; 
    }

    if(ss>=qs && se<=qe){ // completely inside 
        int dx = (se-ss+1)*val ; // amount needed to added to curr seg , dont 
        st[si]+=dx ; // update seg sum val 
        if(ss!=se){
            lazy[si*2]+=val ; // since par is changed make changes in child 
            lazy[si*2+1]+=val ;
        }
        return ;
    }

    int mid = (ss+se)/2 ;
    update(si*2,ss,mid,qs,qe,val) ;
    update(si*2+1,mid+1,se,qs,qe,val) ;
}
int main()
{   
    vector<int> v={1,5,2,-3,4,-1} ;
    
    int n,q,code,l,r,val ;
    cin>>n>>q;
    build(1,1,n) ;
    while(q--){
        cin>>code ;
        if(code==1){
            cin>>l>>r ;
            cout<<query(1,1,n,l,r)<<"\n" ;
        }
        else{
            cin>>l>>r>>val ;
            update(1,1,n,l,r,val) ;
        }
    }
    return 0;
}
