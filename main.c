// Cordero Hernández Marco Ricardo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 50

typedef struct {
	unsigned char estado : 3;
	// 0 -> Healthy; 1 -> Sick; 2 -> Recovered; 4 -> Empty
} PERSSTAT;

typedef struct {
	unsigned int id; 							// With no bit assignment because it can generate too many ids
	unsigned short dias 		: 10;		// Up to 3 years
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
			
	printf("INITIAL CASE\n");
	printf("Patient 0 in (%d,%d)\n",c0x,c0y);
	show(celdas);
	
	char dec;
	printf("\n0 to continue, other to exit");
	
	int cont_dias = 1;
	while(1){
		printf("\n\nDay %d -> ",cont_dias);
		scanf("%d",&dec);
		
		if(dec == 0){
			check_replace(celdas);
			show(celdas);
			cont_dias++;
		} else {
			printf("\n\n ------ STAY AT HOME ------ \n\n",144);
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
			case 0: // upper left
				if(row > 0 && col > 0){
					avail = (celdas[row-1][col-1].celstat) ? 0 : 1;
				}
				break;
			case 1:	// upper centre
				if(row > 0){
					avail = (celdas[row-1][col].celstat) ? 0 : 1;
				}
				break;
			case 2:	// upper right
				if(row > 0 && col < size){
					avail = (celdas[row-1][col+1].celstat) ? 0 : 1;
				}
				break;
			case 3:	// left centre
				if(row > 0){
					avail = (celdas[row][col-1].celstat) ? 0 : 1;
				}
				break;
			case 4:	// right centre
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
	
	// Swaps the values in real time
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(celdas[i][j].celstat){
				n_pos = move(celdas,i,j);
				swap_val(celdas, celdas[i][j], i, j, n_pos);
			}
		}
	}
	
	CELDA holder[size][size];
	
	for(int i = 0; i < size; i++){ // Since we don't want to affect the original array in real time, this copies the original content to a temporal container
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
					
					if(i > 0 && j > 0 && celdas[i-1][j-1].sujeto.status.estado == 1){	// Upper left
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i-1][j-1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i-1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i-1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}
					
					if(i > 0 && celdas[i-1][j].sujeto.status.estado == 1){	// Upper centre
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i-1][j].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i-1][j].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i-1][j].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
					
					if(i > 0 && j < size && celdas[i-1][j+1].sujeto.status.estado == 1){	// Upper right
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i-1][j+1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i-1][j+1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i-1][j+1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}
					
					if(j > 0 && celdas[i][j-1].sujeto.status.estado == 1){	// Centre left
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i][j-1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i][j-1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i][j-1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
						
					if(j < size && celdas[i][j+1].sujeto.status.estado == 1){	// Centre right
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i][j+1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i][j+1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i][j+1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
						
					if(i < size && j > 0 && celdas[i+1][j-1].sujeto.status.estado == 1){	// Lower left
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i+1][j-1].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i+1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i+1][j-1].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
					
					if(i < size && celdas[i+1][j].sujeto.status.estado == 1){	// Lower centre
						if(celdas[i][j].sujeto.cubrebocas == 0 && celdas[i+1][j].sujeto.cubrebocas == 0 && probabilidad <= 60){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 || celdas[i+1][j].sujeto.cubrebocas == 1 && probabilidad <= 20){
							holder[i][j].sujeto.status.estado = 1;	
						} else if(celdas[i][j].sujeto.cubrebocas == 1 && celdas[i+1][j].sujeto.cubrebocas == 1 && probabilidad <= 6){
							holder[i][j].sujeto.status.estado = 1;	
						}
					}	
						
					if(i < size && j < size && celdas[i+1][j+1].sujeto.status.estado == 1){	// Lower right
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
