/*
Alexander boev 314393158
Genady yolgin 321983413
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct Node {
	int raw;
	int col;
	struct Node* next;
}Node;

Node *ptr = NULL;

int getrand(int, int);
void creatematrix(int *, int*);
void mazepathmaker(int **, int, int);
void mazeprint(int **, int, int);
void cleanmemory(int**, int, int);
void allocatemaze(int ***, int, int);
void mazefinalfix(int **, int, int);
void goright(int**, int, int, int *);
void godown(int**, int, int, int *);
void goleft(int**, int, int, int *);
void goup(int**, int, int, int *);
void pop();
void push(int, int);

int main() {

	srand(time(NULL));

	int N = 0, M = 0;
	int tempright = 5;
	int tempdown = 5;
	int templeft = 5;
	int tempup = 5;
	int **maze;

	creatematrix(&N, &M);
	allocatemaze(&maze, N, M);
	mazepathmaker(maze, N, M);
	mazeprint(maze, N, M);
	printf("\n\n");
	Node *temp;
	push(0, 0);
	
	
	//maze[N - 1][M - 1] = 0; //test for no exit.
	
	while ((ptr->raw != (N - 1)) || (ptr->col != (M - 1))) {

		goright(maze, N, M, &tempright);

		if (tempright != 5) {
			godown(maze, N, M, &tempdown);
		}
		if (tempright != 5 && tempdown != 5 && ((ptr->raw != (N - 1)) || (ptr->col != (M - 1)))) {
			goleft(maze, N, M, &templeft);
		}
		if (tempright != 5 && tempdown != 5 && templeft != 5 && ((ptr->raw != (N - 1)) || (ptr->col != (M - 1)))) {
			goup(maze, N, M, &tempup);
		}
		if (tempright != 5 && tempdown != 5 && templeft != 5 && tempup != 5) {
			if ((ptr->raw != (N - 1)) || (ptr->col != (M - 1))) {
				maze[ptr->raw][ptr->col] = 3;
				if (ptr->next != NULL) {
					maze[ptr->raw][ptr->col] = 3;
					printf("Mouse is in(%d,%d) the color of this block is red and now the mouse will go up to(%d, %d).\n", ptr->raw, ptr->col, ptr->next->raw, ptr->next->col);
					pop();
				}
				else {
					printf("\n\nThe maze doesnt have an exit!\n\n");
					for (int i = 0; i < N; i++) {
						for (int j = 0; j < M; j++) {
							if (maze[i][j] == 3)
								maze[i][j] = 2;
						}
					}
					mazeprint(maze, N, M);
					cleanmemory(maze, N, M);
					exit(1);
				}
			}
		}
	}

	maze[N - 1][M - 1] = 2;
	printf("\n\n");

	printf("All the places the mouse visited!\n\n");
	mazeprint(maze, N, M);
	mazefinalfix(maze, N, M);
	temp = ptr;
	
	while (temp != NULL) {
		maze[temp->raw][temp->col] = 2;
		temp = temp->next;
	}

	printf("\n\n");
	printf("Final path of the mouse in the maze!\n\n");
	mazeprint(maze, N, M);
	cleanmemory(maze, N, M);
	printf("\n");
	return 0;

}

void mazefinalfix(int** maze, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (maze[i][j] == 3)
				maze[i][j] = 1;
		}
	}
}

void creatematrix(int* A, int* B) {
	int N = 0;
	int M = 0;
	printf("to create a maze, please enter the number of raws and columns. \n");
	printf("the minimum maze size is 15x15! \n");
	while (N<15) {                // enter raws  N>1
		printf("Enter raws: \n");
		scanf("%d", &N);
		if (N<15)
			printf("Wrong raw value,there must be atleast 15 raws!\n");
	}
	*A = N;
	while (M<15) {               // enter colums M>1
		printf("enter columns: \n");
		scanf("%d", &M);
		if (M<15)
			printf("Wrong colum value,there must be atleast 15 colums!\n");
	}
	*B = M;
}

int getrand(int min, int max) {

	return(rand() % (max - min) + min);
}

void mazepathmaker(int **maze, int N, int M) {

	for (int i = 0; i<N; i++) {     // generate random values 0 or 
		for (int j = 0; j<M; j++) {
			maze[i][j] = getrand(0, 2);
			//maze[i][j]=0;
		}
	}

	for (int i = 0; i<N; i++) {   //diagnol passage for the rat
		for (int j = 0; j<M; j++) {
			if (i == j)
				maze[i][j] = 1;
		}
	}
	int i = 1;
	while (i < N && i < M) {
		maze[i][i - 1] = 1;
		i++;
	}

	if (N>M) {           // make atleast 1 passage for the rat
		for (int i = M; i<N; i++) {
			for (int j = M - 1; j<M; j++) {
				maze[i][j] = 1;
			}
		}
	}

	if (M>N) {         // // make atleast 1 passage for the rat
		for (int i = N - 1; i<N; i++) {
			for (int j = N; j<M; j++) {
				maze[i][j] = 1;
			}
		}
	}

	printf("\n");
}

void mazeprint(int **maze, int N, int M) {

	for (int i = 0; i<N; i++) {     // test print
		for (int j = 0; j<M; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

void cleanmemory(int**maze, int N, int M) {
	while (ptr != NULL) {
		pop();
	}

	for (int i = 0; i < N; i++)
		free((maze)[i]);
	free(maze);
}

void allocatemaze(int*** maze, int N, int M) {
	(*maze) = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; ++i)
		(*maze)[i] = (int*)malloc(M * sizeof(int));
}

void goright(int** maze, int N, int M, int* temp) {
	while ((((ptr->col) + 1) < M) && (maze[ptr->raw][(ptr->col) + 1] != 0)) {
		if (maze[ptr->raw][(ptr->col) + 1] == 1) {
			printf("Mouse is in (%d,%d) the color of this block is yellow and now the mouse will go right to (%d, %d).\n", ptr->raw, ptr->col, ptr->raw, ptr->col + 1);
			if (maze[ptr->raw][ptr->col] != 3)
				maze[ptr->raw][ptr->col] = 2;
			push(ptr->raw, ((ptr->col) + 1));
			*temp = 5;
		}
		else {
			*temp = 6;
			break;
		}
	}
	*temp = 6;
}

void godown(int** maze, int N, int M, int *temp) {

	if ((ptr->raw) + 1 < N && maze[(ptr->raw) + 1][ptr->col] != 0) {
		if (maze[(ptr->raw) + 1][ptr->col] == 1) {
			printf("Mouse is in (%d,%d) the color of this block is yellow and now the mouse will go down to (%d, %d).\n", ptr->raw, ptr->col, ptr->raw + 1, ptr->col);
			if (maze[ptr->raw][ptr->col] != 3)
				maze[ptr->raw][ptr->col] = 2;
			push(((ptr->raw) + 1), ptr->col);
			*temp = 5;
		}
		else
			*temp = 6;
	}
	else
		*temp = 6;
}

void goleft(int** maze, int N, int M, int *temp) {
	if ((ptr->col) - 1 >= 0 && maze[ptr->raw][(ptr->col) - 1] != 0) {
		if (maze[ptr->raw][(ptr->col) - 1] == 1) {
			printf("Mouse is in (%d,%d) the color of this block is yellow and now the mouse will go left to (%d, %d).\n", ptr->raw, ptr->col, ptr->raw, ptr->col - 1);
			if (maze[ptr->raw][ptr->col] != 3)
				maze[ptr->raw][ptr->col] = 2;
			push(ptr->raw, (ptr->col - 1));
			*temp = 5;
		}
		else
			*temp = 6;
	}
	else
		*temp = 6;
}

void goup(int** maze, int N, int M, int *temp) {

	if ((ptr->raw) - 1 >= 0 && maze[(ptr->raw) - 1][ptr->col] != 0) {
		if (maze[(ptr->raw) - 1][ptr->col] == 1) {
			printf("Mouse is in (%d,%d) the color of this block is yellow and now the mouse will go up to (%d, %d).\n", ptr->raw, ptr->col, ptr->raw - 1, ptr->col);
			if (maze[ptr->raw][ptr->col] != 3)
				maze[ptr->raw][ptr->col] = 2;
			push((ptr->raw - 1), ptr->col);
			*temp = 5;
		}
		else
			*temp = 6;
	}
	else
		*temp = 6;
}

void push(int raw, int col) {
	Node* link = (Node*)malloc(sizeof(Node));
	link->raw = raw;
	link->col = col;
	link->next = ptr;
	ptr = link;

}

void pop() {
	if (ptr != NULL) {
		Node *temp = ptr;
		ptr = temp->next;
		free(temp);
	}
	else {
		printf("Out of range!\n");
	}
}
