#include<bits/stdc++.h>
#include <iostream>
using namespace std;
long long int tree[10000001];
int a[10000001];
int n;
long long int xorquery(int node,int l_n,int h_n,int l_r,int h_r)
{
    if( l_r<=l_n && h_n<=h_r )
    return tree[node];
    if( h_n<l_r || h_r<l_n)
    return 0;
    int mid = l_n + (h_n-l_n)/2;
    return (xorquery(2*node+1,l_n,mid,l_r,h_r) ^ xorquery(2*node+2,mid+1,h_n,l_r,h_r));
}
void build_tree(int node,int l_n,int h_n)
{
    /* CHECK IF PADDING IS DONE OR NOT. THIS FUNCTION IS CALLED AFTER PROPER PADDING*/
    if(l_n==h_n)
    {
        tree[node] = a[l_n];
        return;
    }
    else
    {
        int mid = l_n + (h_n-l_n)/2;
        build_tree(2*node+1,l_n,mid);
        build_tree(2*node+2,mid+1,h_n);
        tree[node] = (tree[2*node+1] ^ tree[2*node+2]);
        return;
    }
}
int main() 
{
	int q;
	cin>>n>>q;
	for(int i=0;i<n;i++)
	cin>>a[i];
	
	while(__builtin_popcount(n)!=1)
	{
	    a[n]=0;
	    n++;
	}
	build_tree(0,0,n-1);
	
	int l;
	int r;
	while(q--)
	{
	    cin>>l>>r;
	    l--;
	    r--;
	    cout<<xorquery(0,0,n-1,l,r)<<endl;
	}
	return 0;
}
