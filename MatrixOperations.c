/*This program performs matrix operations including 
input, output, addition, and multiplication for
matrices of any dimensions. */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int *elements; /*a one-dimensional array*/
	int rows; /* number of rows of the matrix */
	int columns; /* number of columns of the matrix */
} matrix;

void read_matrix(matrix *a);
void deallocate(matrix *a);
void print(matrix a);
void displayMenu();
matrix add(matrix a, matrix b);
matrix subtract(matrix a, matrix b);
matrix multiply(matrix a, matrix b);

void main()
{
	matrix a, b, c;
	int choice;
	choice = 0;
	
	printf("-------- MATRIX OPERATIONS V1.1 --------\n\n");

	while (choice != 4) {
		displayMenu();
		printf("Enter your choice (1-4): \n");
		scanf("%d", &choice);

		if (choice == 1) {
			/*Addition*/
			printf("-------- ADDITION --------\n\n");

			printf("Matrix A: \n");
			read_matrix(&a);
			printf("Matrix A: \n\n");
			print(a);

			printf("Matrix B: \n");
			read_matrix(&b);
			printf("Matrix B: \n\n");
			print(b);

			c = add(a, b);
			if (c.elements == NULL) {
				printf("Error: Addition Dimensions Invalid\n\n");
			}
			else {
				printf("Result of Matrix A + Matrix B: \n\n");
				print(c);
			}
			deallocate(&a);
			deallocate(&b);
			deallocate(&c);
		}

		else if (choice == 2) {
			/*Subtraction*/
			printf("-------- SUBTRACTION --------\n\n");

			printf("Matrix A: \n");
			read_matrix(&a);
			printf("Matrix A: \n\n");
			print(a);

			printf("Matrix B: \n");
			read_matrix(&b);
			printf("Matrix B: \n\n");
			print(b);

			c = subtract(a, b);
			if (c.elements == NULL) {
				printf("Error: Subtraction Dimensions Invalid\n\n");
			}
			else {
				printf("Result of Matrix A - Matrix B: \n\n");
				print(c);
			}
			deallocate(&a);
			deallocate(&b);
			deallocate(&c);
		}

		else if (choice == 3) {
			/*Multiplication*/
			printf("-------- MULTIPLICATION --------\n\n");

			printf("Matrix A: \n");
			read_matrix(&a);
			printf("Matrix A: \n\n");
			print(a);

			printf("Matrix B: \n");
			read_matrix(&b);
			printf("Matrix B: \n\n");
			print(b);

			c = multiply(a, b);
			if (c.elements == NULL) {
				printf("Error: Multiplication Dimensions Invalid\n\n");
			}
			else {
				printf("Result of Matrix A * Matrix B: \n\n");
				print(c);
			}
			deallocate(&a);
			deallocate(&b);
			deallocate(&c);
		}

		else if (choice == 4) {
			printf("Exiting...\n");
			exit(0);
		}

		else {
			printf("Invalid Selection: Please enter a number 1-4\n\n");
		}
	}

}

/*Reads a matrix from the keyboard.
 Prompts the user to enter the dimensions, then the
 matrix entries, one row at a time. */
void read_matrix(matrix *a) {
	int n, i, j;
	printf("Enter the dimensions of the matrix.\n");
	printf("Enter the number of rows: ");
	scanf("%d", &(*a).rows);
	printf("Enter the number of columns: ");
	scanf("%d", &(*a).columns);

	n = (*a).rows * (*a).columns;
	(*a).elements = (int *)calloc(n, sizeof(int));

	for (i = 0; i < (*a).rows; i++) {
		for (j = 0; j < (*a).columns; j++) {
			printf("Enter the value for row %d, column %d: ",i+1,j+1);
			/*Address of the ith and jth elements in elements*/
			scanf("%d", &*((*a).elements + (*a).columns * i + j));
		}
	}
	putchar('\n');
}

/*Deallocates the storage of matrix, changes the elements
 pointer to NULL, and changes both dimensions to 0. */
void deallocate(matrix *a) {
	free((*a).elements);
	(*a).rows = 0;
	(*a).columns = 0;
	(*a).elements = NULL;
}

void displayMenu() {
	printf("----------- MENU -----------\n");
	printf("1) Add\n");
	printf("2) Subtract\n");
	printf("3) Multiply\n");
	printf("4) Exit\n");
	putchar('\n');
}

/*Outputs the given matrix.*/
void print(matrix a) {
	int i, j;
	for (i = 0; i < a.rows; i++) {
		putchar('[');
		for (j = 0; j < a.columns; j++) {
			/*Use the address formula to print numbers*/
			printf("%3d  ", *(a.elements + a.columns * i + j)); 
		}
		putchar(']');
		printf("\n");
	}
	putchar('\n');
}

/*Returns the sum of matrices a and b: a + b */
matrix add(matrix a, matrix b) {
	int i, j;
	int n;

	/*Generate matrix c and set the proper dimensions*/
	matrix c;
	c.rows = a.rows;
	c.columns = a.columns;
	n = a.rows * a.columns;
	c.elements = (int *)calloc(n, sizeof(int));

	/*Check if dims are invalid*/
	if (a.rows != b.rows || a.columns != b.columns) {
		c.rows = 0;
		c.columns = 0;
		c.elements = NULL;
		return c;
	}
	else { /*Populate c*/
		for (i = 0; i < a.rows; i++) {
			for (j = 0; j < a.columns; j++) {
				/*Address formula*/
				*(c.elements + c.columns * i + j) = *(a.elements + a.columns * i + j) + *(b.elements + b.columns * i + j);
			}
		}
		return c;
	}
}

/*Returns the difference of matrices a and b: a - b */
matrix subtract(matrix a, matrix b) {
	int i, j;
	int n;

	/*Generate matrix c and set the proper dimensions*/
	matrix c;
	c.rows = a.rows;
	c.columns = a.columns;
	n = a.rows * a.columns;
	c.elements = (int *)calloc(n, sizeof(int));

	/*Check if dims are invalid*/
	if (a.rows != b.rows || a.columns != b.columns) {
		c.rows = 0;
		c.columns = 0;
		c.elements = NULL;
		return c;
	}
	else { /*Populate c*/
		for (i = 0; i < a.rows; i++) {
			for (j = 0; j < a.columns; j++) {
				/*Address formula*/
				*(c.elements + c.columns * i + j) = *(a.elements + a.columns * i + j) - *(b.elements + b.columns * i + j);
			}
		}
		return c;
	}
}

/*Return the product of matrices a and b: a * b 
TODO: Determine if the given matrices are square, and if so use the Strassen algorithm
to do the multiplication in O(n^2.8074) as opposed to O(n^3). Also, implement the Strassen
algorithm. */
matrix multiply(matrix a, matrix b) {
	int i, j, k;
	int n;
	int sum; /*Holds sum used for calculation*/

	/*Generate matrix c and set the proper dimensions*/
	matrix c;
	c.rows = a.rows;
	c.columns = b.columns;
	n = a.rows * b.columns;
	c.elements = (int *)calloc(n, sizeof(int));

	/*Check if dims are invalid*/
	if (a.columns != b.rows) {
		c.rows = 0;
		c.columns = 0;
		c.elements = NULL;
		return c;
	}
	else { /*Populate c*/
		sum = 0;
		for (i = 0; i < a.rows; i++) {
			for (j = 0; j < b.columns; j++) {
				/*Extra loop used for calculating sum*/
				for (k = 0; k < b.rows; k++) {
					sum += *(a.elements + a.columns * i + k) * *(b.elements + b.columns * k + j);
					*(c.elements + c.columns * i + j) = sum;
				}
				sum = 0;
			}
		}
		return c;
	}
}