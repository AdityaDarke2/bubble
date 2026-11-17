def bubble(arr):
    cnt=0
    size = len(arr)
    for i in range(size):
        for j in range(0, size-i-1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
            cnt+=1
    print("\nnumber comparisons performed: ", f"{cnt}")
               
marks = [78,45,92,67,54,88,61,73]


size=len(marks)


print("Original Array: ")
for i in range(size):
    print(marks[i], end=" ")


bubble(marks)


print("Sorted Array: ")
for i in range(size):
    print(marks[i], end=" ")


def quick_sort(array, start, end):
    if start >= end:
        return 0


    comparisons = 0
   
    mid = start + (end - start) // 2
    array[start], array[mid] = array[mid], array[start]
   
    pivot_val = array[start]
    low = start + 1
    high = end


    while True:
        while low <= high:
            comparisons += 1
            if array[high] >= pivot_val:
                high -= 1
            else:
                break


        while low <= high:
            comparisons += 1
            if array[low] <= pivot_val:
                low += 1
            else:
                break


        if low <= high:
            array[low], array[high] = array[high], array[low]
        else:
            break


    array[start], array[high] = array[high], array[start]


    comparisons += quick_sort(array, start, high - 1)
    comparisons += quick_sort(array, high + 1, end)


    return comparisons


marks1 = [78, 45, 92, 67, 54, 88, 61, 73]
total_comparisons = quick_sort(marks1, 0, len(marks1) - 1)


print("Sorted Array:      ", marks1)
print("Total Comparisons: ", total_comparisons)
