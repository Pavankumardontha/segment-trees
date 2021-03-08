#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int a[10001];
int t[10000001];
int n;

void build(int l,int r,int inode)
{
	if((r-l)==1)
	{
		t[inode]=a[l];
		return;
	}
	else
	{
		int mid = l + (r-l)/2;
		build(l,mid,2*inode+1);
		build(mid,r,2*inode+2);
		t[inode] = min(t[2*inode+1],t[2*inode+2]);
	}
}
void update(int i,int v,int inode,int ls,int rs)
{
	if((rs-ls)==1)
	{
		a[i]=v;
		t[inode]=v;
		return;
	}
	else
	{
		int mid = ls + (rs-ls)/2;
		if(i<mid)
		update(i,v,2*inode+1,ls,mid);
		else
		update(i,v,2*inode+2,mid,rs);
		t[inode] = min(t[2*inode+1],t[2*inode+2]);
	}
}
int minimum(int l,int r,int inode,int ls,int rs)
{
	if(l>=rs || r<=ls)
	return INT_MAX;
	else if(l<=ls && r>=rs)
	return t[inode];
	else
	{
		int mid = ls + (rs-ls)/2;
		int m1 = minimum(l,r,2*inode+1,ls,mid);
		int m2 = minimum(l,r,2*inode+2,mid,rs);
		return min(m1,m2);
	}
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	cin>>a[i];
	build(0,n,0);
	cout<<"build done"<<endl;
	update(3,-8,0,0,n);
	cout<<"update done"<<endl;
	cout<<minimum(0,5,0,0,n)<<endl;
}

