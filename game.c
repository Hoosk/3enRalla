#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*Para hacer a rand() más aleatorio.*/
#define N 3
#define TRUE 0
#define FALSE 1
typedef char Fila[N];
typedef Fila Tauler[N];
/*Llena el vector con espacios, usarlo solo 1 vez.*/
void emplenaElVector (Tauler vector) {
int i,j;
	for (i=0;i<N;i++) {
		for (j=0;j<N;j++) {
			vector[i][j]=' ';
		}
	}
}
/*Muestra fixa en el tablero.*/
void mostrarFixa(Tauler mostra,int  i, int j,int num){
	if (mostra[i][j]==' '){
		printf("%i ",num );
	}else{
		printf("%c ",mostra[i][j] );
	}
}

/*Hace las lineas de el tablero.*/
void lineas(){
	int j;
	for (j=0;j<N;j++) {
		printf("+");
		printf("----");				
	}
}
/*Muestra el tablero*/
void mostraTabla(Tauler vector) {
	int multiplicador=1,j,i, num=1;
	lineas();
	printf("+\n");
	for (i=0;i<N;i++) {

		for (j=0;j<N;j++) {
			printf("|  ");mostrarFixa(vector,i,j,num);
			num++;
		}
		printf("|\n");
		lineas();
		printf("+\n");	
	}
	printf("\n");
}
/*Decide que jugador empieza la partida, True sera el jugador 1, False el Jugador 2.*/
int empezarPartida(){
int salida=10;
	srand(time(NULL));
	int j1,j2;
	char i;
	j1= rand()%6+1;	
	j2= rand()%6+1;	
	printf("Jugador 1, saca un : %i\n", j1);
	printf("Jugador 2, saca un : %i\n\n", j2);
	if (j1>j2){
		 salida=TRUE;
	}else if (j1<j2){
		 salida=FALSE;
	}else{
		 printf("Ops! Ha salido el mismo numero, pulse enter para volver a lanzar los dados.\n\n");
		if (getchar() == '\n') {
			j1=0;j2=0;
		 	empezarPartida();/*Asi consigo que no salgan dados repetidos.*/
		 }		 
	}
return salida;
}

char jugador(int queJugador, Tauler vector){
	int colocar,f,c;
	char fixa;
	if (queJugador == 1){fixa='X';}else{fixa='O';}
	printf("Jugador %d, entra el número (de l'1 al %d) del quadrat on vols colocar la fitxa (%c):",queJugador, N*N,fixa);
	scanf("%d",&colocar);
	f=(colocar-1)/N; c=(colocar-1)%N;/* Formula para saber en que posicion de la matriz nos colocamos*/
	if (vector[f][c]!=' '){ /*Comprovamos que sea una jugada valida*/
		jugador(queJugador,vector);
	}
	return vector[f][c]=fixa;
}
char botSkynet(Tauler vector){
	int colocar,f,c,i;
	for (i = 0; i < 1000000; i++)	{/* hacer tiempo para generar un nuevo numero y que el programa no se descontrole*/}
	srand(time(NULL));

	colocar=rand()%(N*N)+1;	
	f=(colocar-1)/N; c=(colocar-1)%N;			
	if (vector[f][c]!=' ' && vector[f][c]=='X'){ 
		for (i = 0; i < 1000000; i++)	{/* hacer tiempo para generar un nuevo numero y que el programa no se descontrole*/}
		botSkynet(vector);
	}
	return vector[f][c]='O';
}
void ganador(int contador, int jugador){
	int a=0;
	if (contador==N){
		printf("Has ganado jugador %d \n", jugador);
		system("./win.sh");
		exit (0); /*Si, se que esta malament, pero no sortia be amb un return.*/
	}

}
void quienGana(Tauler vector){
int i,j,h1,h2,v1,v2,d1,d2,a=0;
	for (i=0;i<N;i++) {
		h1=0;h2=0;d1=0;
		v1=0;v2=0;d2=0;		
		for (j=0;j<N;j++) {
			if(vector[i][j]=='X'){
				h1++;
				ganador(h1,1);
			}else if(vector[i][j]=='O'){
				h2++;
				ganador(h2,2);
			}	
			if(vector[j][i]=='X'){
				v1++;
				ganador(v1,1);
			}else if(vector[j][i]=='O'){
				v2++;
				ganador(v2,2);
			}	
			/*Diagonales*/
			if(vector[i][j+1]=='X' ){
				d1++;
				ganador(d1,1);
			}else if(vector[i][j+1]=='O'){
				d2++;
				ganador(d2,2);
			}		
			
		}
			
	}
}
void partida(int tipo){
	/*tipo es para ver que jugadores entran en juego, TRUE 2 jugadores, FALSE con bots, se asume que el BOT es el jugador 1*/
	Tauler posicio;
	int empieza=0,ahora,turnos,i;
	emplenaElVector (posicio);
	empieza=empezarPartida();	
	mostraTabla(posicio);
	for (turnos = 0; turnos < (N*2); turnos++){
		if (empieza==0){
			jugador(1,posicio);
		}else{
			if (tipo==FALSE){
				printf("Jugador Skynet fa la seva jugada:\n\n");
				botSkynet(posicio);
			}else{ 
				jugador(2,posicio);
			}
		}	
		mostraTabla(posicio);
		quienGana(posicio);
		
		if (empieza==0){
			empieza=1;
		}else{
			empieza=0;
		}
		
	}
	printf("Empat!\n");
}

int main(int argc, char const *argv[]){
	if (argc==1){
		partida(TRUE);
	}else{
		partida(FALSE);
	}	
	return 0;
}
	 
