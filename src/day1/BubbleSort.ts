export default function bubble_sort(arr: number[]): void {
    const n = arr.length;
    for (let i = 0; i < n; i++ ) //operation has to be done n-1 times, so either inclusive-exclusive or inclusive-inclusive n-1 
        for (let j = 0; i < n-1-j; i++) //inclusive-exclusive, AND operation only done on index before previous last, 
            if (arr[i] > arr[i+1]){
                let temp = arr[i]
                arr[i]= arr[i+1]
                arr[i+1]= temp
            }
    }