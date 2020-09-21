// Cordero Hernández Marco Ricardo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 50

typedef struct {
	unsigned char estado : 3;
	// 0 -> Sano; 1 -> Enfermo; 2 -> Recuperado; 4 -> Vacio
} PERSSTAT;

typedef struct {
	unsigned int id; 							// sin asignación de bits porque puedes generarse muchos
	unsigned short dias 		: 10;		// hasta 3 años
	unsigned char edad			: 	7;
	unsigned char cubrebocas: 	1;
	PERSSTAT status;
} PERSONA;

typedef struct {
	unsigned char celstat : 1;
	PERSONA sujeto;
} CELDA;

void initialize(CELDA celdas[size][size]);
void show(CELDA celdas[size][size]);
void check_replace(CELDA celdas[size][size]);
int move(CELDA celdas[size][size],int row, int col);
void swap_val(CELDA celdas[size][size],CELDA celdA,int row, int col, int new_pos);

CELDA celdas[size][size];

int main(){
	
	srand(time(NULL));
	
	initialize(celdas);
	int c0x, c0y;
	
	while(1){
		c0x = rand()%size;
		c0y = rand()%size;
		if(celdas[c0x][c0y].celstat == 1){
			celdas[c0x][c0y].sujeto.status.estado = 1;
			celdas[c0x][c0y].sujeto.dias = 0;
			break;
		}
	}
			
	printf("ESCENARIO INICIAL\n");
	printf("Caso 0 en (%d,%d)\n",c0x,c0y);
	show(celdas);
	
	char dec;
	printf("\n0 para continuar, cualquier otro para salir");
	
	int cont_dias = 1;
	while(1){
		printf("\n\nD%ca %d -> ",161,cont_dias);
		scanf("%d",&dec);
		
		if(dec == 0){
			check_replace(celdas);
			show(celdas);
			cont_dias++;
		} else {
			printf("\n\n ------ QU%cDATE EN CASA ------ \n\n",144);
			return 0;
		}
	}
	
}

void initialize(CELDA celdas[size][size]){
	int dec, cont = 0, unique_id = 1;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			dec = rand()%2;
			
			if(dec == 0 && cont >= 1250){
				dec = 1;
			} else {
				if(dec == 0) cont++;
			}
			
			celdas[i][j].sujeto.id = unique_id * dec;
			celdas[i][j].sujeto.edad = (rand()%91) * dec;
			celdas[i][j].celstat = dec;
			if(dec == 1) unique_id++;
		}
	}
	
	int decub, contbrebocas = 0;	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(celdas[i][j].celstat){
				celdas[i][j].sujeto.status.estado = 0;
				decub = rand()%2;
				
				if(decub == 1 && contbrebocas >= 625){
					decub = 0;
				} else {
					if(decub == 1) contbrebocas++;
				}
				
				celdas[i][j].sujeto.cubrebocas = decub;
			} else {
				celdas[i][j].sujeto.status.estado = 4;
			}
		}
	}
}

void show(CELDA celdas[size][size]){
	int stat, condicion;	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			stat = celdas[i][j].celstat;
			
			if(stat){
				condicion = celdas[i][j].sujeto.status.estado;
				switch(condicion){						
					case 0:						
						if(celdas[i][j].sujeto.cubrebocas){
							printf("s ");
						} else {
							printf("S ");
						}
						break;
					case 1:
						if(celdas[i][j].sujeto.cubrebocas){
							printf("e ");
						} else {
							printf("E ");
						}
						break;
					case 2:
						printf("r ");
						break;
					default:
						printf("  ");
						break;
				}
			} else {
				printf("  ");
			}
		}
		printf("\n");
	}
}

int move(CELDA celdas[size][size],int row, int col){
	int new_pos, cont = 0, avail = 0;
	while(avail == 0){
		new_pos = rand()%8;
		switch(new_pos){
			case 0: // izquierda superior
				if(row > 0 && col > 0){
					avail = (celdas[row-1][col-1].celstat) ? 0 : 1;
				}
				break;
			case 1:	// centro superior
				if(row > 0){
					avail = (celdas[row-1][col].celstat) ? 0 : 1;
				}
				break;
			case 2:	// derecha superior
				if(row > 0 && col < size){
					avail = (celdas[row-1][col+1].celstat) ? 0 : 1;
				}
				break;
			case 3:	// izquierda centro
				if(row > 0){
					avail = (celdas[row][col-1].celstat) ? 0 : 1;
				}
				break;
			case 4:	// derecha centro
				if(row < size){
					avail = (celdas[row][col+1].celstat) ? 0 : 1;
				}
				break;
			case 5:
				if(row < size && col > 0){
					avail = (celdas[row+1][col-1].celstat) ? 0 : 1;
				}
				break;
			case 6:
				if(row < size){
					avail = (celdas[row+1][col].celstat) ? 0 : 1;
				}
				break;
			case 7:
				if(row < size && col < size){
					avail = (celdas[row+1][col+1].celstat) ? 0 : 1;
				}
				break;
		}
		cont++;
		if(cont == 20) break;
	}
	
	if(cont >= 20){
		return 8;
	} else {
		return new_pos;
	}
}

void swap_val(CELDA celdas[size][size],CELDA celdA,int row, int col, int new_pos){
	CELDA holder;
	int ind_i, ind_j;
	if(new_pos != 8){
		switch(new_pos){
			case 0:
				ind_i = row - 1;
				ind_j = col - 1;
				break;
			case 1:
				ind_i = row - 1;
				ind_j = col;
				break;
			case 2:
				ind_i = row - 1;
				ind_j = col + 1;
				break;
			case 3:
				ind_i = row;
				ind_j = col - 1;
				break;
			case 4:
				ind_i = row;
				ind_j = col + 1;
				break;
			case 5:
				ind_i = row + 1;
				ind_j = col - 1;
				break;
			case 6:
				ind_i = row + 1;
				ind_j = col;
				break;
			case 7:
				ind_i = row + 1;
				ind_j = col + 1;
				break;
			default:
				ind_i = row;
				ind_j = col;
				break;
		}
		
		celdas[ind_i][ind_j].celstat = celdas[row][col].celstat;
		celdas[ind_i][ind_j].sujeto.id = celdas[row][col].sujeto.id;
		celdas[ind_i][ind_j].sujeto.dias = celdas[row][col].sujeto.dias;
		celdas[ind_i][ind_j].sujeto.edad = celdas[row][col].sujeto.edad;
		celdas[ind_i][ind_j].sujeto.cubrebocas = celdas[row][col].sujeto.cubrebocas;
		celdas[ind_i][ind_j].sujeto.status.estado = celdas[row][col].sujeto.status.estado;
		
		celdas[row][col].celstat = 0;
		celdas[row][col].sujeto.id = 0;
		celdas[row][col].sujeto.dias = 0;
		celdas[row][col].sujeto.edad = 0;
		celdas[row][col].sujeto.cubrebocas = 0;
		celdas[row][col].sujeto.status.estado = 4;
	}
}

void check_replace(CELDA celdas[size][size]){
	int probabilidad, n_pos;
	
	// Mueve las celdas modificando el arreglo en tiempo real
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(celdas[i][j].celstat){
				n_pos = move(celdas,i,j);
				swap_val(celdas, celdas[i][j], i, j, n_pos);
			}
		}
	}
	
	CELDA holder[size][size];
	
	for(int i = 0; i < size; i++){ // Copia el contenido original a un conteneder temporal para no afectar en tiempo real al original
		for(int j = 0; j < size; j++){
			holder[i][j].celstat = celdas[i][j].celstat;
			holder[i][j].sujeto.id = celdas[i][j].sujeto.id;
			holder[i][j].sujeto.dias = celdas[i][j].sujeto.dias;
			holder[i][j].sujeto.edad = celdas[i][j].sujeto.edad;
			holder[i][j].sujeto.cubrebocas = celdas[i][j].sujeto.cubrebocas;
			holder[i][j].sujeto.status.estado = celdas[i][j].sujeto.status.estado;
		}
	}
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(celdas[i][j].celstat){
				if(celdas[i][j].sujeto.status.estado == 0){
					probabilidad = rand()%101;
					
					if(i > 0 && j > 0 && celdas[i-1][j-1].sujeto.status.estado == 1){	// Casilla superior izquierda
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i-1][j-1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i-1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i-1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}
					
					if(i > 0 && celdas[i-1][j].sujeto.status.estado == 1){	// Casilla superior central
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i-1][j].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i-1][j].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i-1][j].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
					
					if(i > 0 && j < size && celdas[i-1][j+1].sujeto.status.estado == 1){	// Casilla superior derecha
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i-1][j+1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i-1][j+1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i-1][j+1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}
					
					if(j > 0 && celdas[i][j-1].sujeto.status.estado == 1){	// Casilla central izquierda
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i][j-1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i][j-1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i][j-1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
						
					if(j < size && celdas[i][j+1].sujeto.status.estado == 1){	// Casilla central derecha
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i][j+1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i][j+1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i][j+1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
						
					if(i < size && j > 0 && celdas[i+1][j-1].sujeto.status.estado == 1){	// Casilla inferior izquierda
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i+1][j-1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i+1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i+1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
					
					if(i < size && celdas[i+1][j].sujeto.status.estado == 1){	// Casilla inferior central
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i+1][j].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i+1][j].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i+1][j].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
						
					if(i < size && j < size && celdas[i+1][j+1].sujeto.status.estado == 1){	// Casilla inferior derecha
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i+1][j+1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i+1][j+1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i+1][j+1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}
					
					if(holder[i][j].sujeto.status.estado == 1){
						holder[i][j].sujeto.dias = 0;
					}
				} else if(celdas[i][j].sujeto.status.estado = 1){
					if(celdas[i][j].sujeto.dias == 7){
						holder[i][j].sujeto.status.estado = 2;
					} else {
						holder[i][j].sujeto.dias++;
					}
				}
			}
		}
	}
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			celdas[i][j].celstat = holder[i][j].celstat;
			celdas[i][j].sujeto.id = holder[i][j].sujeto.id;
			celdas[i][j].sujeto.dias = holder[i][j].sujeto.dias;
			celdas[i][j].sujeto.edad = holder[i][j].sujeto.edad;
			celdas[i][j].sujeto.cubrebocas = holder[i][j].sujeto.cubrebocas;
			celdas[i][j].sujeto.status.estado = holder[i][j].sujeto.status.estado;
		}
	}
}
