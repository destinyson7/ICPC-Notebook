// UVA 11053
ll a, b, N;
ll f(ll x){
    return (((a*x)%N*x)%N + b)%N;
}   
int main()
{
    cin >> N >> a >> b;
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
