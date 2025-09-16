/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 void merge(int *nums, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge(nums, left, mid);
    merge(nums, mid + 1, right);
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int*) malloc(sizeof(int) * n1);
    int *R = (int*) malloc(sizeof(int) * n2);
    for (int i = 0; i < n1; i++) L[i] = nums[i + left];
    for (int j = 0; j < n2; j++) R[j] = nums[j + mid + 1];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            nums[k++] = L[i++];
        } else {
            nums[k++] = R[j++];
        }
    }
    while (i < n1) nums[k++] = L[i++];
    while (j < n2) nums[k++] = R[j++];
 }
int* sortArray(int* nums, int numsSize, int* returnSize) {
    merge(nums, 0, numsSize - 1);
    *returnSize = numsSize;
    return nums;
}