

#include <stdio.h>

int main()
{
        int A[20], N, Temp, i, j;
        printf("\nENTER THE NUMBER OF TERMS...: ");
        scanf("%d",&N);
        printf("\nENTER THE ELEMENTS OF THE ARRAY...: \n");
        for(i=1; i<=N; i++)
        {
            printf("\nENTER THE ELEMENT [ %d ]...: ",i);
            scanf("%d", &A[i]);
        }

        for(i=1; i<N; i++)
        {
            Temp = A[i];
            j = i-1;
            while(Temp<A[j] && j>0)
            {
                A[j+1] = A[j];
                j = j-1;
            }
            A[j+1] = Temp;
        }

        printf("\nTHE SORTED LIST IS...: \n\n");
        for(i=1; i<=N; i++)
                printf(" %d ",A[i]);

        printf("\n");

        return 0;
}
