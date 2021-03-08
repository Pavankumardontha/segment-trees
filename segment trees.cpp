#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int a[100001]; //input array
int t[100000001]; //heap
int n; //size of the array
//size of the formed heap will be (2*n-1)

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
    	t[inode] = t[(2*inode)+1] + t[(2*inode)+2];
    	return;
	}
	
}
void update(int i,int v,int inode,int ls,int rs)
{
	/* We want to set a[i] = v. We want to write recursion such that this touches only the leaf node which has range [i,i+1).*/
	if((rs-ls)==1)
	{
		/* this implies that we have reached the leaf node having range (i,i+1).we will update the leaf node as well the element
		at the ith index in the array.So we have to update the element not only in a[] but also in the heap.After updation is 
		completed we will update the parents node value by suming up the children.So by this way,the element which got updated 
		will also effect the sum of different segments.*/
		t[inode] = v;
		a[i] = v;
		return;
	}
	else
	{
	    /* we have to now traverse either the left subtree of the right subtree.This can be done by calcuating the mid value.*/
		int mid = ls + (rs-ls)/2;
		if(i<mid)
		{
			/* we will traverse the left sub-tree.if the parent of the heap is at index i,then its left child is at index 2i+1.*/
			update(i,v,2*(inode)+1,ls,mid); //[ls,mid)
		}	
		else
		{
			update(i,v,2*(inode)+2,mid,rs); //rs[mid,rs)
		}
		/* remember that we have to solve sum the left and right child value so that the parents value gets updated automatically.*/
		t[inode] = t[2*inode + 1] + t[2*inode + 2];
	}
	return ;
}

 int sum(int l,int r,int inode,int ls,int rs) /* returns sum in the interval [l,r).*/
{
	/* l = left index of the array
	r = right index of the array
	inode = current node index in heap(we always start the recursion from the root node)
	(ls,rs) = array range which is covered by our current node
	Note the difference between (l,r) and (ls,rs). (l,r) belong to the original array and (ls,rs) belong the nodes in max heap.
	We have array indices and also heap indices.Each heap index(node) has a set of array indices which specify the range our 
	current node covers in the array.
	*/
	/* Here we have 3 possibilities. 
1) if the current node range values (ls,rs) do not fall in our required range (l,r) then we return 0 in this case.
	if(l>=rs || r<=ls) return 0;
2) if the current node range values fall completely in our required range (l,r) then we return the current node value
	if(l<=ls && r>=rs) return t[inode];
3) if there is any overlap between our current node range (ls,rs) and required range (l,r) then we spilt the sum into 
	2 parts calculate the sum of both the parts and return this combined sum.
	*/
	
	if(l>=rs || r<=ls)
	return 0;
	else if(l<=ls && r>=rs)
	return t[inode];
	else
	{
		int mid = ls + (rs-ls)/2;
		int s1 = sum(l,r,2*inode+1,ls,mid);
		int s2 = sum(l,r,2*inode+2,mid,rs);
		int ans = s1+s2;
		return ans;
	}
}



int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	cin>>a[i];
	
	build(0,n,0);
	cout<<"heap is build"<<endl;
	update(3,18,0,0,n); //a[3]=18
	cout<<"update done"<<endl;
	cout<<sum(3,8,0,0,n)<<endl;  // sum from [l,r)=[3,8) = a[3]+ a[4] + a[5] + a[6] + a[7]
	/*the last 3 arguments will be common to update and sum calls.This states that we always start from the root with range [0,n).*/
}
