#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1.0);
struct node
{
	int x,y;	
};
node vec[10];
node vex[10];
node stackk[10];
double alld[1<<10];
double ans[1<<10];
int xx,yy,n_points;
int m,n,case_num;
//根据纵坐标从小到大，如果纵坐标相同，横坐标从小到大原则排序 
bool cmp1(node a,node b)
{
	if (a.y==b.y)
		return a.x<b.x;
	else
		return a.y<b.y;
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
//根据点到起点极角从小到大，如果极角相同横坐标从小到大原则排序 
bool cmp2(node a,node b)
{
	if (atan2(a.y-yy,a.x-xx)!=atan2(b.y-yy,b.x-xx))
		return (atan2(a.y-yy,a.x-xx))<(atan2(b.y-yy,b.x-xx));
	return a.x<b.x;
}
//运用Graham扫描法 
double dealConvexHull(int t,node vex[])
{
	int i;
	//单个点情形，凸包长为0 
	if (t==1)
		return 0.0;
	//两个点情形，根据题意"凸包"长为两个点构成线段长的两倍 
	if (t==2)
		return 2.0*dis(vex[0],vex[1]);
	memset(stackk,0,sizeof(stackk));
	//用第一种排序，找出凸包始点 
	sort(vex,vex+t,cmp1);
	stackk[0]=vex[0];
	xx=stackk[0].x;
	yy=stackk[0].y;
	//根据求出始点，用第二种排序 
	sort(vex+1,vex+t,cmp2);
	stackk[1]=vex[1];
	int top=1;
	//开始构造凸包 
	for (i=2;i<t;i++)
	{
		//每添加一个点，都要维护凸包凸的性质，保证后一个点都是在前一个点基础上往左边转 
		while (i>=1&&cross(stackk[top-1],stackk[top],vex[i])<0)
			top--;
		stackk[++top]=vex[i];
	}
	//开始计算凸包长度 
	double s=0;
	for (i=1;i<=top;i++)
		s+=dis(stackk[i-1],stackk[i]);
	s+=dis(stackk[top],vex[0]);
	//返回总凸包长 
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
		memset(alld,0,sizeof(alld));
		//循环，考虑所有点集，计算对应单个围栏长度 
		for (i=1;i<1<<n;i++)
		{
			//拼接上整圆长度 
			alld[i]=2.0*PI*m;
			n_points=0;
			int j;
			for (j=0;j<n;j++)
			{
				if (i&(1<<j))
				{
					vex[n_points].x=vec[j].x;
					vex[n_points].y=vec[j].y;
					n_points++;
				}
			}
			alld[i]+=dealConvexHull(n_points,vex);
		}
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
