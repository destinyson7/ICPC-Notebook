int compare(pair<int, int> p1, pair<int, int> p2){ 
    if (p1.first == p2.first)  
        return p1.second > p2.second; 
    return p1.first < p2.first; 
} 
void buildTree(int* tree, int pos, int low, int high,int index, int value) 
{  
    if (index < low || index > high) 
        return; 
    if (low == high) { 
        tree[pos] = value; 
        return; 
    } 
    int mid = (high + low) / 2; 
    buildTree(tree, 2 * pos + 1, low, mid, index, value); 
    buildTree(tree, 2 * pos + 2, mid + 1, high, index, value); 
    tree[pos] = max(tree[2 * pos + 1], tree[2 * pos + 2]); 
} 
int findMax(int* tree, int pos, int low, int high, int start, int end) 
{ 
    if (low >= start && high <= end)  
        return tree[pos]; 
    if (start > high || end < low)  
        return 0;     
    int mid = (high + low) / 2;  
    return max(findMax(tree, 2 * pos + 1, low, mid, start, end),  
               findMax(tree, 2 * pos + 2, mid + 1, high, start, end)); 
} 
int findLIS(int arr[], int n) { 
    pair<int, int> p[n]; 
    for (int i = 0; i < n; i++) { 
        p[i].first = arr[i];  
        p[i].second = i;  
    } 
    sort(p, p + n, compare); 
    int len = pow(2, (int)(ceil(sqrt(n))) + 1) - 1; 
    int tree[len]; 
    memset(tree, 0, sizeof(tree)); 
    for (int i = 0; i < n; i++) { 
        buildTree(tree, 0, 0, n - 1, p[i].second,  
        findMax(tree, 0, 0, n - 1, 0, p[i].second) + 1); 
    }     
    return tree[0]; 
} 