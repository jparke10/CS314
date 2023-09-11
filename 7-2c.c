#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 2048

struct ColorPoint {
	long a;
	long r;
	long g;
	long b;
};

long f(struct ColorPoint **points, int n) {
	long sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += points[j][i].a;
			sum += points[j][i].r;
			sum += points[j][i].g;
			sum += points[j][i].b;
		}
	}
	return sum;
}

long g(struct ColorPoint **points, int n) {
	long sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += points[i][j].a;
			sum += points[i][j].r;
			sum += points[i][j].g;
			sum += points[i][j].b;
		}
	}
	return sum;
}

struct ColorPoint** create2DArray(int n) {
	// array to hold a pointer to the beginning of each row
	struct ColorPoint **points =
		(struct ColorPoint**)malloc(n * sizeof(struct ColorPoint*));
	for (int i = 0; i < n; ++i) {
		// array to hold each row
		points[i] =
			(struct ColorPoint*)malloc(n * sizeof(struct ColorPoint));
		for (int j = 0; j < n; ++j) {
			// init the colorpoint struct
			points[i][j].a = rand();
			points[i][j].r = rand();
			points[i][j].g = rand();
			points[i][j].b = rand();
		}
	}
	return points;
}

void free2DArray(struct ColorPoint** points, int n) {
	for (int i = 0; i < n; ++i) {
		free(points[i]);
	}
	free(points);
}

int main() {
	struct ColorPoint **funf = create2DArray(size);
	struct ColorPoint **fung = create2DArray(size);
	// function f, hovering around 0.0191
	clock_t start = clock();
	f(funf, size);
	clock_t end = clock();
	double totalTime1 = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Function F runtime: %f\n", totalTime1);
	free2DArray(funf, size);
	// function g, hovering around 0.0065
	start = clock();
	g(fung, size);
	end = clock();
	double totalTime2 = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Function G runtime: %f\n", totalTime2);
	free2DArray(fung, size);
	// function g is faster due to the fact that it has a miss rate
	// half as common as f's, as well as the fact that it can cache
	// 2 value accesses at a time because it reads 64 bytes sequentially
	// (they aren't found sequentially when going by rows rather than
	// columns)
}
