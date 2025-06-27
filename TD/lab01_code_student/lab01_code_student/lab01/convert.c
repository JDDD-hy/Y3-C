 # include<stdio.h>

int main()
 {
 printf("input foot and inch:\n");
float foot; // 如果声明时为int，则只在int范畴中计算，比如6/8=0
float inch;
scanf("%f %f",&foot,&inch);
printf("the height is %f\n",(foot+inch/12)*0.3048);
 return 0;
 }
 