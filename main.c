#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona {
    char nombre[20];
    char apellido[20];
    char localidad[70];
    int edad;
    char genero[20];
    char interes[20];
};

void tomarLocalidades(char localidades[][70]) {
    long pos = 0;

    FILE *localidadesFile;
    localidadesFile = fopen("codigoLocalidades.txt", "r");

    char buff[70];

    while (!feof((FILE*)localidadesFile)) {
        fgets(buff, 70, (FILE*)localidadesFile);

        for (int n = 0 ; n < (strlen(buff) - 1) ; ++n) {
            if (buff[n] == ',') {
                ++n;

                int h = 0;

                for (int j = n; (j < (strlen(buff) - 1)) || (buff[n] == ' ' && buff[n+1] == ' ') ; ++j) {
                    localidades[pos][h] = buff[j];

                    ++h;
                }

                localidades[pos][h] = '\0';

                ++pos;
            }
        }
    }

    fclose(localidadesFile);
}

long stringToLong(char texto[20]) {
    long numero;

    for (int n = 0 ; texto[n] != ' ' || texto[n] != '\0' ; ++n) {

    }
}

void tomarPersonas(struct Persona personas[], long cantPersonas, long personasATomar, char localidades[][70]) {
    long randoms[cantPersonas];

    char genero[2][2] = {
        "M",
        "F"
    }, interes[4][2] = {
        "F",
        "M",
        "A",
        "N"
    };
    
    for (long n = 0 ; n < personasATomar ; ++n) {
        long random = rand()%cantPersonas, repetido = 0;

        for (long h = 0 ; h <= n ; ++h) {
            if (h == n) {
                randoms[h] = random;
            } else {
                if (randoms[h] == random) {
                    h = n;

                    repetido = 1;
                }
                if (randoms[h] > random) {
                    long actual = randoms[h], sig;
                            
                    if ((h+1) != n) {
                        sig = randoms[h+1];
                    }

                    randoms[h] = random;

                    random = actual;

                    while (h < n) {
                        ++h;

                        if (h != n) {
                            actual = sig;
                            
                            sig = randoms[h+1];
                        }

                        randoms[h] = random;

                        random = actual;
                    }
                }
            }
        }
        if (repetido == 1) {
            --n;
        }
    }

    FILE *personasFile;
    personasFile = fopen("personas.txt", "r");
    
    char linea[70];

    long posPersonas = 0;
    for (long cont = 1 ; !feof((FILE*)personasFile) || cont < randoms[personasATomar - 1] ; ++cont) {    
        fgets(linea, 70, (FILE*)personasFile);
        
        if (cont == randoms[posPersonas]) {
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
                    personas[posPersonas].edad = strtol(token, &pEnd, 10);
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

int main()
{
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

    struct Persona personas[personasATomar];

    tomarPersonas(personas, cantPersonas, personasATomar, localidades);

    for (long n = 0 ; n < (personasATomar - 1) ; ++n) {
        printf("%s\n", personas[n].nombre);
        printf("%s\n", personas[n].apellido);
        printf("%s\n", personas[n].localidad);
        printf("%d\n", personas[n].edad);
        printf("%s\n", personas[n].genero);
        printf("%s\n", personas[n].interes);
    }

    return 0;
}
