// UVA 11053

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(a) a.begin(), a.end()
#define sz(a) (ll)(a.size())
#define endl "\n"

const ll L = 1e5+5;

ll a, b, N;

ll f(ll x)
{
    return (((a*x)%N*x)%N + b)%N;
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    while(true)
    {
        // ll N;
        cin >> N;

        if(N == 0)
        {
            break;
        }

        // ll a, b;
        cin >> a >> b;

        ll tortoise = f(0);
        ll hare = f(f(0));

        while(tortoise != hare)
        {
            tortoise = f(tortoise);
            hare = f(f(hare));
        }

        ll die = 1;
        tortoise = f(tortoise);

        while(tortoise != hare)
        {
            tortoise = f(tortoise);
            die++;
        }

        cout << N - die << endl;
    }

    return 0;
}