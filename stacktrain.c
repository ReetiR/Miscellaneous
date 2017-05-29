#include <stdio.h>

struct stack
{
    int stk[5];
    int top;
};

typedef struct stack STACK;
STACK C;

int A[100];
int B[100];
 
 
void main ()
{
    int sizeA, sizeB, i, j, flag, temp;
    C.top = -1;
    flag = 0;

    printf("Enter size for train A:\t");
    scanf("%d", &sizeA);
    printf("Enter size for train B:\t");
    scanf("%d", &sizeB);
    while(sizeA >100 || sizeB>100){
        printf("Length within 100");
        printf("Enter size for train A:\t");
        scanf("%d", &sizeA);
        printf("Enter size for train B:\t");
        scanf("%d", &sizeB);
    }
    if(sizeA!=sizeB){
        printf("No");
    }
    else{
        printf("Enter sequence for train A:\n");
        for(i=0; i<sizeA; i++){
            scanf ("%d", &temp);
            A[i] =  temp;
        }
        printf("Enter sequence for train B:\n");
        for(i=0; i<sizeB; i++){
            scanf ("%d", &temp);
            B[i] = temp;
        }
        j = 0;
        for(i=0; i<sizeA; i++){
            C.top = C.top+1;
            if(C.top>=5){
                flag = 1;
                break;
            }
            C.stk[C.top]=A[i];
            while(C.stk[C.top]==B[j] && C.top>-1){
                C.top = C.top-1;
                j++;
            }
        }
        printf("%d", C.top);
        if(C.top== -1 && flag == 0){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
}