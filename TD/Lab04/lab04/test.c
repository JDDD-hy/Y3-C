#include <stdio.h>

// void swapS(int *a, int length) {
//     int max = a[0], min = a[0];
//     int i=0,j=0;
//     for (int x = 0; x < length; x++) {
//         if (a[x] > max) {
//             max = a[x];
//             i=x;
//         }
//         if (a[x] < min) {
//             min = a[x];
//             j=x;
//         }
//         printf("max_idx:%d,min_idx:%d\n",i,j);
//     }


//     // 交换最大值和最小值
//     a[i]=a[j]^a[i];
//     a[j]=a[j]^a[i];
//     a[i]=a[j]^a[i];

// }

// int main() {
//     int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
//     int length = sizeof(arr) / sizeof(arr[0]);
//     printf("%d\n",length);
//     swapS(arr, length);
//     for (int i = 0; i < length; i++) {
//         printf("%d ", arr[i]);
//     }
//     return 0;
// }
