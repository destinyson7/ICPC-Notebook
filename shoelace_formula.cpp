// Used to calculate area of convex polygon, given 
// its coordinates in the x and y plane

#include <bits/stdc++.h> 
using namespace std; 
  
// (X[i], Y[i]) are coordinates of i'th point. 
double polygonArea(double X[], double Y[], int n) 
{ 
    // Initialze area 
    double area = 0.0; 
  
    // Calculate value of shoelace formula 
    int j = n - 1; 
    for (int i = 0; i < n; i++) 
    { 
        area += (X[j] + X[i]) * (Y[j] - Y[i]); 
        j = i;  // j is previous vertex to i 
    } 
  
    // Return absolute value 
    return abs(area / 2.0); 
} 
 
int main() 
{ 
    double X[] = {0, 2, 4}; 
    double Y[] = {1, 3, 7}; 
  
    int n = sizeof(X)/sizeof(X[0]); 
  
    cout << polygonArea(X, Y, n); 
} 