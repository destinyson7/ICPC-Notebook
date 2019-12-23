#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef long long int ll;

ll arr[100005];

void Merge(ll *arr, ll *left, ll l1, ll *right, ll l2)
{
    ll i = 0, j = 0, k = 0;

    while(i<l1 && j<l2)
    {
        if(left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }

        else
        {
            arr[k++] = right[j++];
        }
    }

    while(i<l1)
    {
        arr[k++] = left[i++];
    }    

    while(j<l2)
    {
        arr[k++] = right[j++];
    }
}

void mergeSort(ll *arr, ll n)
{
    if(n<2)
    {
        return;
    }

    ll *left, *right, mid;
    mid = n/2;

    left = (ll *) malloc(mid*sizeof(ll));
    right = (ll *) malloc((n-mid)*sizeof(ll));
    
    for(ll i=0; i<mid; i++)
    {
        left[i] = arr[i];
    }

    for(ll j=mid; j<n; j++)
    {
        right[j-mid] = arr[j];
    }

    mergeSort(left, mid);
    mergeSort(right, n-mid);
    Merge(arr, left, mid, right, n-mid);
}

int main()
{
    ll n;
    scanf("%lld", &n);

    for(ll i=0; i<n; i++)
    {
        scanf("%lld", &arr[i]);
    }

    mergeSort(arr, n);

    for(ll i=0; i<n; i++)
    {
        printf("%lld ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
