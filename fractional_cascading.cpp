
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

vector<vector<int>> st[4*10001] ;

vi mergeVecs(vi&v1,vi&v2)
{   
    int n1 = v1.size(),n2 = v2.size();
    int i = 0, j = 0, k = 0;

    vi v3(n1+n2) ;

    while (i<n1 && j <n2)
    {
        if (v1[i] < v2[j])
            v3[k++] = v1[i++];
        else
            v3[k++] = v2[j++];
    }
 
    while (i < n1)
        v3[k++] = v1[i++];
 
    while (j < n2)
        v3[k++] = v2[j++];

    return v3 ;
}

vvi build(int si,int ss,int se){
    if(ss==se){
        vvi dm(3,vi(1,1e9)) ;
        dm[0][0] = arr[ss] ;
        return st[si] = dm;
    }
    
    int mid = ss+ (se-ss)/2 ;

    vvi re1 = build(2*si,ss,mid) ;
    vvi re2 = build(2*si+1,mid+1,se) ;

    int len = se-ss+1 , l1 = re1[0].size(), l2=re2[0].size() ;
    
    vvi res(3,vi(len,1e9)) ;

    res[0] = mergeVecs(re1[0],re2[0]) ;
    int j = 0 , ptr = 0;
    while(j<len && ptr<l1){
        if(re1[0][ptr]<res[0][j]){
            while(ptr<l1 && re1[0][ptr]<res[0][j]){
                ptr++  ;
            }
        }
        
        if(ptr==l1){
            break; 
        }
        res[1][j] = ptr ; 
        j++ ;
    } 

    j=0,ptr=0;

    while(j<len && ptr<l2){
        if(re2[0][ptr]<res[0][j]){
            while(ptr<l2 && re2[0][ptr]<res[0][j]){
                ptr++  ;
            }
        }
        
        if(ptr==l2){
            break; 
        }
        res[2][j] = ptr ; 
        j++ ;
    } 

    // cout<<"si "<<si<<" - ss "<<ss<<" se "<<se<<"\n";
    // cout<<"vec -> ";
    // for(auto x : res[0]){
    //     cout<<x<<" ";
    // }
    // cout<<"\n";
    
    // for(auto x : re1[0]){
    //     cout<<x<<" ";
    // }
    // cout<<"  ";
    // for(auto x : re2[0]){
    //     cout<<x<<" ";
    // }
    // cout<<"\n";

    // cout<<"ind1 -> ";
    // for(auto x : res[1]){
    //     cout<<x<<" ";
    // }
    // cout<<"\n";
    // cout<<"ind2 -> ";
    // for(auto x : res[2]){
    //     cout<<x<<" ";
    // }
    // cout<<"\n";
    return st [si] = res ;
}

int query(int si,int ss,int se,int qs, int qe,int ele,int idx){
    if(si==1){
        idx = lower_bound(st[1][0].begin(),st[1][0].end(),ele) - st[1][0].begin() ;
    }
    // cout<<"si "<<si<<" - ss "<<ss<<" se "<<se<<" idx "<<idx<<"\n";
    if(idx==1e9){
        return 1e9 ;
    }
    if(qs>se || qe<ss){
        return 1e9 ;
    }

    if(qs<=ss && se<=qe){
        return st[si][0][idx] ;
    }
        
    int mid = ss + (se-ss)/2; 

    int q1 = query(2*si,ss,mid,qs,qe,ele,st[si][1][idx]);
    int q2 = query(2*si+1,mid+1,se,qs,qe,ele,st[si][2][idx]);

    return min(q1,q2);

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
        int qs,qe,ele ;
        cin>>qs>>qe>>ele ;
        int dm = query(1,1,n,qs,qe,ele,1e9) ;
        cout<<dm<<"\n";
    }
    return 0;
}
