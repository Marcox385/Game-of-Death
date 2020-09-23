// Cordero Hernández Marco Ricardo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 50

typedef struct {
	unsigned char stat : 3;
	// 0 -> Healthy; 1 -> Sick; 2 -> Recovered; 4 -> Empty
} PERSSTAT;

typedef struct {
	unsigned int id; 							// With no bit assignment because it can generate too many ids
	unsigned short days 		: 10;		// Up to 3 years
	unsigned char age			: 	7;
	unsigned char mask: 	1;
	PERSSTAT status;
} PERSON;

typedef struct {
	unsigned char celstat : 1;
	PERSON individual;
} CELL;

void initialize(CELL cells[size][size]);
void show(CELL cells[size][size]);
void check_replace(CELL cells[size][size]);
int move(CELL cells[size][size],int row, int col);
void swap_val(CELL cells[size][size],CELL celdA,int row, int col, int new_pos);

CELL cells[size][size];

int main(){
	
	srand(time(NULL));
	
	initialize(cells);
	int c0x, c0y;
	
	while(1){
		c0x = rand()%size;
		c0y = rand()%size;
		if(cells[c0x][c0y].celstat == 1){
			cells[c0x][c0y].individual.status.stat = 1;
			cells[c0x][c0y].individual.days = 0;
			break;
		}
	}
			
	printf("INITIAL CASE\n");
	printf("Patient 0 in (%d,%d)\n",c0x,c0y);
	show(cells);
	
	char dec;
	printf("\n0 to continue, other to exit");
	
	int cont_dias = 1;
	while(1){
		printf("\n\nDay %d -> ",cont_dias);
		scanf("%d",&dec);
		
		if(dec == 0){
			check_replace(cells);
			show(cells);
			cont_dias++;
		} else {
			printf("\n\n ------ STAY AT HOME ------ \n\n",144);
			return 0;
		}
	}
	
}

void initialize(CELL cells[size][size]){
	int dec, cont = 0, unique_id = 1;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			dec = rand()%2;
			
			if(dec == 0 && cont >= 1250){
				dec = 1;
			} else {
				if(dec == 0) cont++;
			}
			
			cells[i][j].individual.id = unique_id * dec;
			cells[i][j].individual.age = (rand()%91) * dec;
			cells[i][j].celstat = dec;
			if(dec == 1) unique_id++;
		}
	}
	
	int decub, countmask = 0;	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(cells[i][j].celstat){
				cells[i][j].individual.status.stat = 0;
				decub = rand()%2;
				
				if(decub == 1 && countmask >= 625){
					decub = 0;
				} else {
					if(decub == 1) countmask++;
				}
				
				cells[i][j].individual.mask = decub;
			} else {
				cells[i][j].individual.status.stat = 4;
			}
		}
	}
}

void show(CELL cells[size][size]){
	int stat, condition;	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			stat = cells[i][j].celstat;
			
			if(stat){
				condition = cells[i][j].individual.status.stat;
				switch(condition){	// capital letter means the individual is wearing a mask			
					case 0:	// Safe
						if(cells[i][j].individual.mask){	
							printf("s "); 
						} else {
							printf("S ");
						}
						break;
					case 1:	// Sick
						if(cells[i][j].individual.mask){	
							printf("e ");
						} else {
							printf("E ");
						}
						break;
					case 2:	// Recovered
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

int move(CELL cells[size][size],int row, int col){
	int new_pos, cont = 0, avail = 0;
	while(avail == 0){
		new_pos = rand()%8;
		switch(new_pos){
			case 0: // upper left
				if(row > 0 && col > 0){
					avail = (cells[row-1][col-1].celstat) ? 0 : 1;
				}
				break;
			case 1:	// upper centre
				if(row > 0){
					avail = (cells[row-1][col].celstat) ? 0 : 1;
				}
				break;
			case 2:	// upper right
				if(row > 0 && col < size){
					avail = (cells[row-1][col+1].celstat) ? 0 : 1;
				}
				break;
			case 3:	// left centre
				if(row > 0){
					avail = (cells[row][col-1].celstat) ? 0 : 1;
				}
				break;
			case 4:	// right centre
				if(row < size){
					avail = (cells[row][col+1].celstat) ? 0 : 1;
				}
				break;
			case 5:
				if(row < size && col > 0){
					avail = (cells[row+1][col-1].celstat) ? 0 : 1;
				}
				break;
			case 6:
				if(row < size){
					avail = (cells[row+1][col].celstat) ? 0 : 1;
				}
				break;
			case 7:
				if(row < size && col < size){
					avail = (cells[row+1][col+1].celstat) ? 0 : 1;
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

void swap_val(CELL cells[size][size],CELL celdA,int row, int col, int new_pos){
	CELL holder;
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
		
		cells[ind_i][ind_j].celstat = cells[row][col].celstat;
		cells[ind_i][ind_j].individual.id = cells[row][col].individual.id;
		cells[ind_i][ind_j].individual.days = cells[row][col].individual.days;
		cells[ind_i][ind_j].individual.age = cells[row][col].individual.age;
		cells[ind_i][ind_j].individual.mask = cells[row][col].individual.mask;
		cells[ind_i][ind_j].individual.status.stat = cells[row][col].individual.status.stat;
		
		cells[row][col].celstat = 0;
		cells[row][col].individual.id = 0;
		cells[row][col].individual.days = 0;
		cells[row][col].individual.age = 0;
		cells[row][col].individual.mask = 0;
		cells[row][col].individual.status.stat = 4;
	}
}

void check_replace(CELL cells[size][size]){
	int probability, n_pos;
	
	// Swaps the values in real time
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(cells[i][j].celstat){
				n_pos = move(cells,i,j);
				swap_val(cells, cells[i][j], i, j, n_pos);
			}
		}
	}
	
	CELL holder[size][size];
	
	for(int i = 0; i < size; i++){ // Since we don't want to affect the original array in real time, this copies the original content to a temporal container
		for(int j = 0; j < size; j++){
			holder[i][j].celstat = cells[i][j].celstat;
			holder[i][j].individual.id = cells[i][j].individual.id;
			holder[i][j].individual.days = cells[i][j].individual.days;
			holder[i][j].individual.age = cells[i][j].individual.age;
			holder[i][j].individual.mask = cells[i][j].individual.mask;
			holder[i][j].individual.status.stat = cells[i][j].individual.status.stat;
		}
	}
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(cells[i][j].celstat){
				if(cells[i][j].individual.status.stat == 0){
					probability = rand()%101;
					
					if(i > 0 && j > 0 && cells[i-1][j-1].individual.status.stat == 1){	// Upper left
						if(cells[i][j].individual.mask == 0 && cells[i-1][j-1].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i-1][j-1].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i-1][j-1].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}
					
					if(i > 0 && cells[i-1][j].individual.status.stat == 1){	// Upper centre
						if(cells[i][j].individual.mask == 0 && cells[i-1][j].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i-1][j].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i-1][j].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}	
					
					if(i > 0 && j < size && cells[i-1][j+1].individual.status.stat == 1){	// Upper right
						if(cells[i][j].individual.mask == 0 && cells[i-1][j+1].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i-1][j+1].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i-1][j+1].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}
					
					if(j > 0 && cells[i][j-1].individual.status.stat == 1){	// Centre left
						if(cells[i][j].individual.mask == 0 && cells[i][j-1].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i][j-1].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i][j-1].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}	
						
					if(j < size && cells[i][j+1].individual.status.stat == 1){	// Centre right
						if(cells[i][j].individual.mask == 0 && cells[i][j+1].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i][j+1].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i][j+1].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}	
						
					if(i < size && j > 0 && cells[i+1][j-1].individual.status.stat == 1){	// Lower left
						if(cells[i][j].individual.mask == 0 && cells[i+1][j-1].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i+1][j-1].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i+1][j-1].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}	
					
					if(i < size && cells[i+1][j].individual.status.stat == 1){	// Lower centre
						if(cells[i][j].individual.mask == 0 && cells[i+1][j].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i+1][j].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i+1][j].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}	
						
					if(i < size && j < size && cells[i+1][j+1].individual.status.stat == 1){	// Lower right
						if(cells[i][j].individual.mask == 0 && cells[i+1][j+1].individual.mask == 0 && probability <= 60){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 || cells[i+1][j+1].individual.mask == 1 && probability <= 20){
							holder[i][j].individual.status.stat = 1;	
						} else if(cells[i][j].individual.mask == 1 && cells[i+1][j+1].individual.mask == 1 && probability <= 6){
							holder[i][j].individual.status.stat = 1;	
						}
					}
					
					if(holder[i][j].individual.status.stat == 1){
						holder[i][j].individual.days = 0;
					}
				} else if(cells[i][j].individual.status.stat = 1){
					if(cells[i][j].individual.days == 7){
						holder[i][j].individual.status.stat = 2;
					} else {
						holder[i][j].individual.days++;
					}
				}
			}
		}
	}
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			cells[i][j].celstat = holder[i][j].celstat;
			cells[i][j].individual.id = holder[i][j].individual.id;
			cells[i][j].individual.days = holder[i][j].individual.days;
			cells[i][j].individual.age = holder[i][j].individual.age;
			cells[i][j].individual.mask = holder[i][j].individual.mask;
			cells[i][j].individual.status.stat = holder[i][j].individual.status.stat;
		}
	}
}
