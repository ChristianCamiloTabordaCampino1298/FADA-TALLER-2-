#include <iostream>
#include <string>

// Autor: Christian Taborda
 
using namespace std;

int minimo(int A, int B, int C, int &aux){ 
	int minimo = A;
	aux = 1;
	if(minimo>B){
		minimo = B;
		aux = 2;
	}
	if(minimo>C){
		minimo = C;
		aux = 3;
	}
	return minimo;
}

void costos(int ** M, int E, int *** C, int *** A, int n){
	int aux;
	for(int y=(n-1); y>=0; y--){
		for(int x=(n-1); x>=0; x--){
			for(int z=0; z<E+1; z++){
				if(x==(n-1) && y==(n-1)){
					C[x][y][z] = 0;
				}
				if(x!=(n-1) && y==(n-1)){
					if(z<M[x+1][y]){
						C[x][y][z] = 999;
					}else{
						C[x][y][z] = M[x+1][y] + C[x+1][y][z-M[x+1][y]];
						A[x][y][z] = 1;
					}
				}
				if(x==(n-1) && y!=(n-1)){
					if(z<M[x][y+1]){
						C[x][y][z] = 999;
					}else{
						C[x][y][z] = M[x][y+1] + C[x][y+1][z-M[x][y+1]];
						A[x][y][z] = 2;
					}
				}
				if(x!=(n-1) && y!=(n-1)){
					if(z<M[x+1][y] && z<M[x][y+1] && z<M[x+1][y+1]){
						C[x][y][z] = 999;
					}
					if(z>=M[x+1][y] && z>=M[x][y+1] && z>=M[x+1][y+1]){
						C[x][y][z] = minimo(M[x+1][y] + C[x+1][y][z-M[x+1][y]],M[x][y+1] + C[x][y+1][z-M[x][y+1]],M[x+1][y+1] + C[x+1][y+1][z-M[x+1][y+1]],aux);
						A[x][y][z] = aux;
					}
					if(z>=M[x+1][y] && z>=M[x][y+1] && z<M[x+1][y+1]){
						C[x][y][z] = minimo(M[x+1][y] + C[x+1][y][z-M[x+1][y]],M[x][y+1] + C[x][y+1][z-M[x][y+1]],999,aux);
						A[x][y][z] = aux;
					}
					if(z>=M[x+1][y] && z<M[x][y+1] && z>=M[x+1][y+1]){
						C[x][y][z] = minimo(M[x+1][y] + C[x+1][y][z-M[x+1][y]],999,M[x+1][y+1] + C[x+1][y+1][z-M[x+1][y+1]],aux);
						A[x][y][z] = aux;
					}
					if(z<M[x+1][y] && z>=M[x][y+1] && z>=M[x+1][y+1]){
						C[x][y][z] = minimo(999,M[x][y+1] + C[x][y+1][z-M[x][y+1]],M[x+1][y+1] + C[x+1][y+1][z-M[x+1][y+1]],aux);
						A[x][y][z] = aux;
					}
					if(z>=M[x+1][y] && z<M[x][y+1] && z<M[x+1][y+1]){
						C[x][y][z] = M[x+1][y] + C[x+1][y][z-M[x+1][y]];
						A[x][y][z] = 1;
					}
					if(z<M[x+1][y] && z<M[x][y+1] && z>=M[x+1][y+1]){
						C[x][y][z] = M[x+1][y+1] + C[x+1][y+1][z-M[x+1][y+1]];
						A[x][y][z] = 3;
					}
					if(z<M[x+1][y] && z>=M[x][y+1] && z<M[x+1][y+1]){
						C[x][y][z] = M[x][y+1] + C[x][y+1][z-M[x][y+1]];
						A[x][y][z] = 2;
					}
				}
			}
		}
	}
}

string construir(int ** M, int E, int *** A, int n){
	string salida = "/ ";
	int i = 0,j = 0;
	while(i!=(n-1) || j!=(n-1)){
		switch(A[i][j][E]){
			case 1:
				salida += "abajo / ";
				i++;
				break;
			case 2:
				salida += "derecha / ";
				j++;
				break;
			case 3:
				salida += "diagonal inf der/ ";
				i++;
				j++;
				break;
		}
		E-=M[i][j];
	}	
	return salida;
}	

int main(){
	
	int n = 4;
	
	int ** M = new int * [n];
	for(int x=0; x<n; x++){
		M[x] = new int[n];
	}
		
	M[0][0] = 0;
	M[0][1] = 20;
	M[0][2] = 20;
	M[0][3] = 10;
	M[1][0] = 15;
	M[1][1] = 40;
	M[1][2] = 10;
	M[1][3] = 10;
	M[2][0] = 15;
	M[2][1] = 15;
	M[2][2] = 50;
	M[2][3] = 5;
	M[3][0] = 15;
	M[3][1] = 15;
	M[3][2] = 15;
	M[3][3] = 0;
	
	int E = 80;
	
	int *** C = new int ** [n];
	int *** A = new int ** [n];
	
	for(int x=0; x<n; x++){
		C[x] = new int * [n];
		A[x] = new int * [n];
		for(int y=0; y<n; y++){
			C[x][y] = new int[E+1];
			A[x][y] = new int[E+1];
		}
	}
			
	costos(M,E,C,A,n);
	if(C[0][0][E] < 999){
		cout << "El camino más óptimo es: " << endl;
		cout << construir(M,E,A,n) << endl;
		cout << "La energía mínima consumida es: " << C[0][0][E] << endl;
	}else{
		cout << "El camino no existe." << endl;
	}
	
	for(int x=0; x<n; x++){
		for(int y=0; y<n; y++){
			delete[] C[x][y];
			delete[] A[x][y];
		}
	}
	
	for(int x=0; x<n; x++){
		delete[] M[x];
		delete[] A[x];
		delete[] C[x];
	}
	
	delete[] M;
	delete[] C;
	delete[] A;
		
	return 0;
	
}
	
	
