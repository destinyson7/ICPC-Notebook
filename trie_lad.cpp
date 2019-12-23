// Task: Given an array of integers, find the subarray with maximum XOR.

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define endl "\n"

const ll L = 1e5+5;

ll a[L];

typedef struct node
{
    node* left;
    node* right;
} node;

node* newNode()
{
    node* temp = (node*)malloc(sizeof(node));
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

node* insert(node* head, ll num)
{
    node* cur = head;
    for(ll i=31; i>=0; i--)
    {
        ll bit = (num>>i)&1;
        
        if(bit)
        {
            if(!cur->right)
            {
                cur->right = newNode();
            }

            cur = cur->right;
        }

        else
        {
            if(!cur->left)
            {
                cur->left = newNode();
            }

            cur = cur->left;
        }
    }

    return head;
}

ll query(node* head, ll num)
{
    node* cur = head;

    ll ans = 0;

    for(ll i=31; i>=0; i--)
    {
        ll bit = (num>>i)&1;

        if(bit)
        {
            if(cur->left)
            {
                // cout << i << endl;
                ans+=(1<<i);

                cur = cur->left;
            }

            else
            {
                cur = cur->right;
            }
        }

        else
        {
            if(cur->right)
            {
                ans+=(1<<i);

                cur = cur->right;
            }

            else
            {
                cur = cur->left;
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll T;
    cin >> T;

    while(T--)
    {
        node* head = newNode();

        ll n;
        cin >> n;

        ll cur_xor = 0;
        ll ans = 0;

        head = insert(head, 0);

        for(ll i=0; i<n; i++)
        {
            cin >> a[i];
            cur_xor^=a[i];
            head = insert(head, cur_xor);
            ans = max(ans, query(head, cur_xor));
        }

        cout << ans << endl;
    }

    return 0;
}