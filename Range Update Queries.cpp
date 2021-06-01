#include<bits/stdc++.h>
#include<iostream>
using namespace std;

long long int tree[10000001];
int a[10000001];
int n;

void add(int node,int l_n,int h_n,int l_r,int h_r,int v)
{
	if(l_r<=l_n && h_r>=h_n)
	tree[node]+=v;
	else if(h_r<l_n || h_n<l_r)
	return ;
	else
	{
		int mid = l_n + (h_n - l_n)/2;
		add(2*node+1,l_n,mid,l_r,h_r,v);
		add(2*node+2,mid+1,h_n,l_r,h_r,v);
	}
	return;
}

long long int get(int node,int l_n,int h_n,int i)
{
	if(l_n==i && h_n==i)
	return tree[node];
	else if(i<l_n || h_n<i)
	return 0;
	else
	{
		int mid = l_n + (h_n - l_n)/2;
		return (tree[node] + get(2*node+1,l_n,mid,i) + get(2*node+2,mid+1,h_n,i));
	}
}

void build_tree(int node,int l_n,int h_n)
{
	if(l_n==h_n)
	tree[node]=a[l_n];
	else
	{
		tree[node]=0;
		int mid = l_n + (h_n - l_n)/2;
		build_tree(2*node+1,l_n,mid);
		build_tree(2*node+2,mid+1,h_n);
	}
	return;
}

int main()
{
    int q;
    cin>>n>>q;
    for(int i=0;i<n;i++)
    cin>>a[i];
    
    /* PADDING */
    while(__builtin_popcount(n)!=1)
    {
    	a[n]=0;
    	n++;
	}
	build_tree(0,0,n-1);
	while(q--)
	{
		int a1;
		cin>>a1;
		if(a1==1)
		{
			int l,r,u;
			cin>>l>>r>>u;
			l--;
			r--;
			add(0,0,n-1,l,r,u);
		}
		else
		{
			int k;
			cin>>k;
			k--;
			cout<<get(0,0,n-1,k)<<endl;
		}
	}
	return 0;
}
