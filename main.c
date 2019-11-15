#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Personas {
    char nombre[20];
    char apellido[20];
    char localidad[70];
    char edad[5];
    char genero[20];
    char interes[20];
} Persona;

void tomarLocalidades(char localidades[][70]) {
    long localidadesPos = 0;

    FILE *localidadesFile;
    localidadesFile = fopen("codigoLocalidades.txt", "r");

    char linea[70];

    while (!feof((FILE*)localidadesFile)) {
        fgets(linea, 70, (FILE*)localidadesFile);

        int comaBandera = 0, localidadesCont = 0;

        for (int cont = 0 ; (cont < (strlen(linea) - 1)) && ((linea[cont] != ' ') || (linea[cont+1] != ' ')) ; ++cont) {
            if (linea[cont] == ',') {
                comaBandera = 1;

                ++cont;
            }
            if (comaBandera == 1) {
                localidades[localidadesPos][localidadesCont] = linea[cont];

                ++localidadesCont;
            }
        }

        localidades[localidadesPos][localidadesCont] = '\0';

        ++localidadesPos;
    }

    fclose(localidadesFile);
}

long cantidadLocalidades() {
    long cantLocalidades = 0;

    char buff[255];

    FILE *localidadesFile;
    localidadesFile = fopen("codigoLocalidades.txt", "r");

    while (!feof((FILE*)localidadesFile)) {
        fgets(buff, 255, (FILE*)localidadesFile);

        ++cantLocalidades;
    }

    fclose(localidadesFile);

    return cantLocalidades;
}

void tomarNumerosRamdom(long numerosRandom[], long personasATomar, long cantPersonas) {
    for (long cont = 0 ; cont < personasATomar ; ++cont) {
        long numeroRandom = rand()%cantPersonas, repetido = 0;

        for (long h = 0 ; h <= cont ; ++h) {
            if (h == cont) {
                numerosRandom[h] = numeroRandom;
            } else {
                if (numerosRandom[h] == numeroRandom) {
                    h = cont;

                    repetido = 1;
                }
                if (numerosRandom[h] > numeroRandom) {
                    long actual = numerosRandom[h], sig;
                            
                    if ((h+1) != cont) {
                        sig = numerosRandom[h+1];
                    }

                    numerosRandom[h] = numeroRandom;

                    numeroRandom = actual;

                    while (h < cont) {
                        ++h;

                        if (h != cont) {
                            actual = sig;
                            
                            sig = numerosRandom[h+1];
                        }

                        numerosRandom[h] = numeroRandom;

                        numeroRandom = actual;
                    }
                }
            }
        }
        if (repetido == 1) {
            --cont;
        }
    }
}

void tomarPersonas(struct Personas personas[], long cantPersonas, long personasATomar, char localidades[][70]) {
    long numerosRandom[personasATomar];

    char genero[2][2] = {
        "M",
        "F"
    }, interes[4][2] = {
        "F",
        "M",
        "A",
        "N"
    };

    tomarNumerosRamdom(numerosRandom, personasATomar, cantPersonas);

    for (int n = 0 ; n < personasATomar ; ++n) {
        printf("%lu\n", numerosRandom[n]);
    }

    FILE *personasFile;
    personasFile = fopen("personas.txt", "r");
    
    char linea[70];

    long posPersonas = 0;
    for (long cont = 1 ; !feof((FILE*)personasFile) || cont < numerosRandom[personasATomar - 1] ; ++cont) {    
        fgets(linea, 70, (FILE*)personasFile);
        
        if (cont == numerosRandom[posPersonas]) {
            int comas = 0;

            char coma[2] = ",", *token;

            token = strtok(linea, coma);
            
            while( token != NULL ) {

                if (comas == 0) {
                    strcpy(personas[posPersonas].nombre, token);
                }

                if (comas == 1) {
                    strcpy(personas[posPersonas].apellido, token);
                }

                if (comas == 2) {
                    char *pEnd;
                    strcpy(personas[posPersonas].localidad, localidades[strtol(token, &pEnd, 10) - 1]);
                }

                if (comas == 3) {
                    char *pEnd;
                    strcpy(personas[posPersonas].edad, token);
                }

                if (comas == 4) {
                    char *pEnd;
                    strcpy(personas[posPersonas].genero, genero[strtol(token, &pEnd, 10) - 1]);
                }

                if (comas == 5) {
                    token[1] = '\0';
                    char *pEnd;
                    strcpy(personas[posPersonas].interes, interes[strtol(token, &pEnd, 10) - 1]);
                }
                
                token = strtok(NULL, coma);

                ++comas;
            }

            ++posPersonas;
        }
    }
}

long cantidadPersonas() {
    long cantPersonas = 0;

    char buff[255];

    FILE *personasFile;
    personasFile = fopen("personas.txt", "r");

    while (!feof((FILE*)personasFile)) {
        fgets(buff, 255, (FILE*)personasFile);

        ++cantPersonas;
    }

    fclose(personasFile);

    return cantPersonas;
}

void imprimirEnArchivo(struct Personas personas[], long personasATomar){
    FILE *salida;

    salida = fopen("salida.txt","w+");

    for (int n = 0 ; n < personasATomar ; ++n) {
        char linea[100];
        strcpy(linea, "");
        strcat(linea, personas[n].nombre);
        strcat(linea, ",");
        strcat(linea, personas[n].apellido);
        strcat(linea, ",");
        strcat(linea, personas[n].localidad);
        strcat(linea, ",");
        strcat(linea, personas[n].edad);
        strcat(linea, ",");
        strcat(linea, personas[n].genero);
        strcat(linea, ",");
        strcat(linea, personas[n].interes);
        strcat(linea, "\n");

        fputs(linea, salida);
    }

    fclose(salida);
}

int main(){
    long cantLocalidades = cantidadLocalidades(), cantPersonas = cantidadPersonas(), personasATomar = 0;

    char localidades[cantLocalidades][70];

    tomarLocalidades(localidades);

    printf("Ingrese la cantidad de personas a tomar:\n");

    while (personasATomar == 0) {
        scanf("%d", &personasATomar);

        if (personasATomar <= 0 || personasATomar > cantPersonas) {
            printf("El numero ingresado no es nardo, ingrese de nuevo:\n");

            personasATomar = 0;
        }
    }

    struct Personas personas[personasATomar];

    tomarPersonas(personas, cantPersonas, personasATomar, localidades);

    imprimirEnArchivo(personas, personasATomar);

    return 0;
}
