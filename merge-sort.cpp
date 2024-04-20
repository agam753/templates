void merge(int low, int mid, int high, vector<int> &arr){
    int n1 = mid-low+1, n2 = high-mid
    int L[n1], R[n2];
    int i = 0, j = 0, idx = low;

    for(i = 0; i < n1; i++) L[i] = arr[i+low];
    for(i = 0; i < n2; i++) R[i] = arr[i+mid+1];
    


    /*    calculation logic (according to question)     */
    i = 0; j = 0;
    while(i < n1 && j < n2){
        if(R[j] >= L[i]-diff){ ans += n2-j; i++; }
        else j++;
    }


    
    /* Merging  */
    i = 0; j = 0; idx = low;
    while(i < n1 && j < n2){
        if(L[i] <= R[j])
            arr[idx++] = L[i++];
        else
            arr[idx++] = R[j++];
    }
    while(i < n1) arr[idx++] = L[i++];
    while(j < n2) arr[idx++] = R[j++];
}

void mergeSort(int low, int high, vector<int> &arr){
    if(low >= high)
        return;
    
    int mid = (low+high) >> 1;
    
    mergeSort(low, mid, arr);
    mergeSort(mid+1, high, arr);
    
    merge(low, mid, high, arr);
}