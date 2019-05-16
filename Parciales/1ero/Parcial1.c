#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define p printf
#define s scanf
#define TXT_ORIG "original.txt"
#define TXT_DEST "destino.txt"

char * palabraInvertidaMayuscula(char palabra[]) {
	int length, i, j;
	char *ret;
	char palabraInvertida[30];
	ret = palabraInvertida;

	i = 0;
	j = strlen(palabra) - 1;

	while(i < strlen(palabra)) {
		if (palabra[j] < 97){
			palabraInvertida[i] = palabra[j];
		} else {
			palabraInvertida[i] = palabra[j] - 32;
		}
		j--;
		i++;
	}

	palabraInvertida[i] = '\0';

	return ret;
}

void palabrasVocalesAMayusculaInvertidas(char txtOrig[], char txtDest[]) {
	FILE *fpOrig, *fpDest;
    
	char linea[100];
	char *token;
	char aux[30];
	int i, len;

    fpOrig = fopen(txtOrig, "r");
    fpDest = fopen(txtDest, "w");

    // Leo cada linea
    while(fgets(linea, 100, fpOrig)) {
    	token = strtok(linea, " ,.");
    	len = strlen(token);

    	while(token != NULL) {
    		switch(token[0]) {
    			case 'a':
    			case 'e':
    			case 'i':
    			case 'o':
    			case 'u':
    			case 'A':
    			case 'E':
    			case 'I':
    			case 'O':
    			case 'U':
	    			strcpy(aux, palabraInvertidaMayuscula(token));
	    			p(" %s", aux);
	    			fputc(' ', fpDest);
	    			fputs(aux, fpDest);
    				break;
    			default:
    				p(" %s", token);
    				fputc(' ', fpDest);
    				fputs(token, fpDest);
    		}

    		token = strtok(NULL, " ,.");
    	}
    }

}

int main(){
	palabrasVocalesAMayusculaInvertidas(TXT_ORIG, TXT_DEST);

    getch();
    return 0;
}