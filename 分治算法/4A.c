#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

double cal_distance(double p1[2], double p2[2]) {
    double dx = p1[0] - p2[0];
    double dy = p1[1] - p2[1];
    return sqrt(dx * dx + dy * dy);
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

//�����������midΪ�磬���߷ֱ�������� state���������׼��0Ϊ�����꣬1Ϊ������
void merge(double points[][2], int left, int mid, int right, int state){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    double left_half[n1][2];
    double right_half[n2][2];
    int i;
	for (i = 0; i < n1; i++) {
        left_half[i][0] = points[left + i][0];
        left_half[i][1] = points[left + i][1];
    }
    for (i = 0; i < n2; i++) {
        right_half[i][0] = points[mid + 1 + i][0];
        right_half[i][1] = points[mid + 1 + i][1];
    }

    i = 0;
	int j = 0; 
	int k = left;
    while (i < n1 && j < n2)
	{
        if (left_half[i][state] <= right_half[j][state])
		{
            points[k][0] = left_half[i][0];
            points[k][1] = left_half[i][1];
            i++;
        } 
		else 
		{
            points[k][0] = right_half[j][0];
            points[k][1] = right_half[j][1];
            j++;
        }
        k++;
    }
    while (i < n1)
	{
        points[k][0] = left_half[i][0];
        points[k][1] = left_half[i][1];
        i++;
        k++;
    }
    while (j < n2)
	{
        points[k][0] = right_half[j][0];
        points[k][1] = right_half[j][1];
        j++;
        k++;
    }
}

//���������� 
void mergeSort(double points[][2], int left, int right,int state) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(points, left, mid, state);
        mergeSort(points, mid + 1, right, state);
        merge(points, left, mid, right, state);
    }
}

//��Ҫ���� 
double findClosestPair(double points[][2], int n) {
    if (n <= 3) {
       	//�����㷨���� 
        double min_distance = DBL_MAX;
        int i,j;
		for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                double distance = cal_distance(points[i], points[j]);
                min_distance = min(min_distance, distance);
            }
        }
        return min_distance;
    }

    //�Ȱѵ㰴�պ��������� 
    mergeSort(points, 0, n - 1,0);

    int mid = n / 2;
    double left_distance = findClosestPair(points, mid);
    double right_distance = findClosestPair(points + mid, n - mid);

    //��ʱ����Сֵ 
    double min_distance = min(left_distance, right_distance);

    //����λ�߸�������һ������ 
    double strip[n][2];
    int strip_size = 0;
    double mid_x = (points[mid - 1][0] + points[mid][0]) / 2.0;
	int i;
    for (i = 0; i < n; i++) {
        if (fabs(points[i][0] - mid_x) < min_distance) 
		{
            strip[strip_size][0] = points[i][0];
            strip[strip_size][1] = points[i][1];
            strip_size++;
        }
    }

    //���������е��y�������� 
    mergeSort(strip, 0, strip_size-1,1);
	int j;
    //��������Ѱ�Ҹ�С���� 
    for (i = 0; i < strip_size; i++) {
        for (j = i + 1; j < strip_size && (strip[j][1] - strip[i][1]) < min_distance; j++) 
		{
            //�ȼ�������������������min�Ͳ������� 
			double strip_distance = cal_distance(strip[i], strip[j]);
            min_distance = min(min_distance, strip_distance);
        }
    }
    return min_distance;
}

int main() {
    int num;
    double x,y;
    scanf("%d",&num);
    int i = 0;
    double points[num][2];
    for(i=0;i<num;i++)
    	scanf("%lf %lf",&points[i][0],&points[i][1]);
    double closest_distance = findClosestPair(points, num);
    printf("%.3lf", closest_distance/2);
    return 0;
}
