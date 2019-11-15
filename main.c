#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[20];
    char apellido[20];
    char localidad[20];
    int edad;
    char genero[20];
    char interes[20];
} Persona;

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

long pertenece(long randoms[], long cantidad, long random) {
    for (long n = 0 ; n < cantidad ; ++n) {
        if (randoms[n] == random) {
            return 1;
        }
    }

    return 0;
}

void tomarPersonas(Persona personas[], long cantPersonas, long personasATomar) {
    long randoms[cantPersonas];
    
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
                    long actual = randoms[h];
                            
                    randoms[h] = random;

                    ++h;
                    while (h <= n) {
                        actual = randoms[h];

                        randoms[h] = actual;

                        ++h;
                    }
                }
            }
        }
        if (repetido == 1) {
            --n;
        } else {
            printf("%d %d\n", n, randoms[n]);
        }
    }
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

    Persona personas[personasATomar];

    tomarPersonas(personas, cantPersonas, personasATomar);

    return 0;
}
