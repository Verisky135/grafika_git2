#include <stdlib.h>
#include <stdio.h>
#include "square.c"

typedef struct {
	int x;
	int y;
} Point;

/*Gambar explosion masih jelek*/
Point explosionPoint[11] = {
	{4,9}, {7,12}, {11, 10}, {7, 14}, {10, 16},
	{6, 16}, {2, 18}, {5, 15}, {1, 14}, {4, 12}
};

void swap (int *a, int *b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
void swapPoint (Point *P1, Point *P2) {
	swap(&P1->x, &P2->x);
	swap(&P1->y, &P2->y);
}

void plotSlopPositiveLine (Point P1, Point P2, color C, int W) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.x - P1.x);
	dY = abs(P2.y - P1.y);
	i = P1.x;
	j = P1.y;
	
	if (dX >= dY) {
		p = 2*dY - dX;
		printf("Based on X\n");
		for (x=P1.x; x<=P2.x; x++) {
			printf("%d %d\n", x, j);
			if (W<4) printSquare(W, x, j, C);
			else {
				if (x%(W/2)==0) printSquare(W, x, j, C);
			}
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j++;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;
		printf("Based on Y\n");
		for (y=P1.y; y<=P2.y; y++) {
			printf("%d %d\n", i, y);
			if (W<4) printSquare(W, i, y, C);
			else {
				if (y%(W/2)==0) printSquare(W, i, y, C);
			}
			if (p >= 0) {
				p += 2* (dX - dY);
				i++;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}

void plotSlopNegativeLine (Point P1, Point P2, color C, int W) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.x - P1.x);
	dY = abs(P2.y - P1.y);
	i = P1.x;
	j = P1.y;	

	if (dX >= dY) {
		p = 2*dY - dX;		
		printf("Based on X\n");
		for (x=P1.x; x<=P2.x; x++) {
			printf("%d %d\n", x, j);
			if (W<4) printSquare(W, x, j, C);
			else {
				if (x%(W/2)==0) printSquare(W, x, j, C);
			}
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j--;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;
		printf("Based on Y\n");
		for (y=P2.y; y<=P1.y; y++) {
			printf("%d %d\n", i, y);
			if (W<4) printSquare(W, i, y, C);
			else {
				if (y%(W/2)==0) printSquare(W, i, y, C);
			}
			if (p >= 0) {
				p += 2* (dX - dY);
				i++;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}

void plotVerticalLine (Point P1, Point P2, color C, int W) {
	int j;
	for(j = P1.y ; j <= P2.y; j++){
        printf("%d %d\n", P1.x , j);
	printSquare(W, P1.x, j, C);
	}
}

void drawBresenhamLine (Point P1, Point P2, color C, int W) {
	if (P1.x > P2.x) {
		swapPoint(&P1,&P2);
	}
	printf("%d %d\n", P1.x, P1.y);
	printf("%d %d\n", P2.x, P2.y);
	if ((P2.x >= P1.x && P1.y > P2.y)) {
		printf("N Slope\n");
		plotSlopNegativeLine(P1,P2,C,W);
	}
	else if (P1.x == P2.x) {
		plotVerticalLine(P1,P2,C,W);
	}
	else {
		printf("P Slope\n");
		plotSlopPositiveLine(P1,P2,C,W);
	}
}

void drawPolyline (int n, Point *P, color C, int W) {
	int i;
	for (i = 0;i < n-1;i++) {
		drawBresenhamLine(P[i], P[i+1], C, W);
	}
}

void drawPolygon (int n, Point *P, color C, int W) {
	drawBresenhamLine(P[n-1], P[0], C, W);
	drawPolyline(n, P, C, W);
	// fill unknown generated gap
	drawBresenhamLine(P[n-1], P[0], C, W);
}

/*
initialPoint : explosion location in the screen
scaleFactor : size of the explosion
*P isi dengan array explosionPoint
*/
void drawExplosion (Point initialPoint, int n, Point *P, int scaleFactor) {
	/*Orange color*/
	color C;
	C.R = 218;
	C.G = 114;
	C.B = 53;

	int i;

	if (scaleFactor >1) {
		for (i = 0; i<n; i++) {
			P[i].x *= scaleFactor;
			P[i].y *= scaleFactor;
		}
	}

	for (i = 0; i<n; i++) {
		P[i].x += initialPoint.x;
		P[i].y +=initialPoint.y;
	}

	drawPolygon(n, P, C, 2);
}