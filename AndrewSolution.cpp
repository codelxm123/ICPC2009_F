#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1.0);
struct node
{
	int x,y;	
};
node vec[10];
node stackk[10];
double alld[1<<10];
double ans[1<<10];
int m,n,case_num;
//根据横坐标从小到大，如果横坐标相同，纵坐标从小到大原则排序 
bool cmp(node a,node b)
{
	if (a.x==b.x)
		return a.y<b.y;
	else
		return a.x<b.x;
}
//计算叉积 
int cross(node a,node b,node c)
{
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
//计算两点距离 
double dis(node a,node b) 
{
	return sqrt((a.x-b.x)*(a.x-b.x)*1.0+(a.y-b.y)*(a.y-b.y)*1.0);
}
//采用Andrew算法 
double AndrewConvexHull(int state,int n,node vex[])
{
	int i;
	memset(stackk,0,sizeof(stackk));
	int top=0;
	//构造"下凸包" 
	for (i=0;i<n;i++)
		if (state&(1<<i))
		{
			while (top>1&&cross(stackk[top-2],stackk[top-1],vex[i])<=0)
				top--;
			stackk[top++]=vex[i];
		}
	int k=top;
	//构造"上凸包" 
	for (i=n-2;i>=0;i--)
		if (state&(1<<i))
		{
			while (top>k&&cross(stackk[top-2],stackk[top-1],vex[i])<=0)
				top--;
			stackk[top++]=vex[i];
		}
	//计算整个凸包长 
	double s=0;
	for (i=1;i<top;i++)
		s+=dis(stackk[i-1],stackk[i]);
	return s;
}
int main() {
	scanf("%d%d",&n,&m);
	case_num=0;
	while (n!=0)
	{
		int i;	
		case_num++;
		for (i=0;i<n;i++)
			scanf("%d%d",&vec[i].x,&vec[i].y);
		//预先排序 
		sort(vec,vec+n,cmp);
		memset(alld,0,sizeof(alld));
		//循环，考虑所有点集，计算对应单个围栏长度 
		for (i=1;i<1<<n;i++)
			alld[i]=2.0*PI*m+AndrewConvexHull(i,n,vec);
		memset(ans,sizeof(ans),0);
		for (i=1;i<1<<n;i++)
		{
			//单个围栏长度 
			ans[i]=alld[i];
			int j;
			//动态规划，再考虑多围栏情况，即是划分成两个点集，对应最短围栏总长度相加 
			for (j=1;j<i;j++)
				if ((j&i)==j) 
					ans[i]=min(ans[i],ans[j]+ans[i^j]);
		}
		printf("Case %d: length = %.2f\n",case_num,ans[(1<<n)-1]);
		scanf("%d%d",&n,&m);
	}
	return 0;
}
