#include <stdio.h>
#include <math.h>
#include <time.h>
int a[100000+5],b[100000+5],d[100000+5],n;
int random(int l,int r){return rand()%(r-l+1)+l;}
void quicksort(int l,int r)
{
	if(l>=r)return;
	int bas=a[random(l,r)],bp=0,cp=0,dp=0;
	for(int i=l;i<=r;i++)
	{
		if(a[i]==bas)cp++;
		else if(a[i]<bas)b[bp++]=a[i];
		else d[dp++]=a[i];
	}
	for(int i=0;i<bp;i++)a[l+i]=b[i];
	for(int i=0;i<cp;i++)a[l+bp+i]=bas;
	for(int i=0;i<dp;i++)a[l+bp+cp+i]=d[i];
	quicksort(l,l+bp-1);
	quicksort(l+bp+cp,r);
}
int main()
{
	srand(time(NULL));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	quicksort(1,n);
	for(int i=1;i<=n;i++)printf("%d",a[i]);
	return 0;
}