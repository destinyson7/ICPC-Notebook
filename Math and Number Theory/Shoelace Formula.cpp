double polygonArea(double X[], double Y[], int n) { 
    double area = 0.0; 
    int j = n - 1; // X and Y are coordinates of points
    for (int i = 0; i < n; i++){ 
        area += (X[j] + X[i]) * (Y[j] - Y[i]); 
        j = i;  // j is previous vertex to i 
    }    
    return abs(area / 2.0); 
}