#include<bits/stdc++.h>
#include <iostream>
using namespace std;
long long int tree[10000001];
int a[10000001];
int n;
long long int sum(int node,int l_n,int h_n,int l_r,int h_r)
{
    if( l_r<=l_n && h_n<=h_r )
    return tree[node];
    if( h_n<l_r || h_r<l_n)
    return 0;
    int mid = l_n + (h_n-l_n)/2;
    return sum(2*node+1,l_n,mid,l_r,h_r) + sum(2*node+2,mid+1,h_n,l_r,h_r);
}
void update(int node,int l_n,int h_n,int i,int v) //a[i]=v
{
    if(l_n==i && h_n==i)
    {
        tree[node] = v;
        a[i]=v;
        return;
    }
    if(i<l_n || h_n<i)
    return;
    int mid = l_n + (h_n-l_n)/2;
    update(2*node+1,l_n,mid,i,v);
    update(2*node+2,mid+1,h_n,i,v);
    tree[node] = tree[2*node+1] + tree[2*node+2];
    return;
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
        tree[node] = tree[2*node+1]+tree[2*node+2];
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
	int a1;
	int a2;
	int a3;
	while(q--)
	{
	    cin>>a1>>a2>>a3;
	    if(a1==2)
	    {
	        a2--;
	        a3--;
	        cout<<sum(0,0,n-1,a2,a3)<<endl;
	    }
	    else
	    {
	        a2--;
	        update(0,0,n-1,a2,a3);
	    }
	}
	return 0;
}
