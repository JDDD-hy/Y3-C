# include <stdio.h>
int main()
{
    /*int num,hundred,ten,one;
    for (num=100;num<1000;num++){
        hundred=num//100;
        ten=(num/100)%10;
        one=num%10;
        if (num==)

    }我还没写完
*/
    int n;
    scanf("%d",&n);
    int begin;
    int i=1;
    while(i<n)
    {
        begin*=10;
        i++;
    }
    printf("begin from %d\n",begin);
    for (i=begin;i<begin*10;i++)
    {
        int sum;
        int t,d;
        t=i%10;
        d=i/10; //未完成

        if (sum==i)
        printf("%d",i);
    }

    return 0;
}