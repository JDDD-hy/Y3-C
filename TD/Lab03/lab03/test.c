# include <stdio.h>
int main(){
    int a[10];
    int *p = a;
    printf("%p %p %p %p\n",&a[0], &a[0]+1, &a[0]+4, &a[1]);
    printf("%ld",sizeof(a[0]));
    return 0;
}