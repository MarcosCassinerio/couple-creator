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


void obtenerLocalidad(char *linea) {
    char localidad[50];

    for (int n = 0 ; n < (strlen(linea) - 1) ; ++n) {
        if (linea[n] == ',') {
            ++n;

            int h = 0;

            for (int j = n ; j < (strlen(linea) - 1) ; ++j) {
                localidad[h] = linea[j];

                ++h;
            }

            localidad[h] = '\0';
        }
    }

    strcpy(linea, localidad);

    printf("%s\n", linea);
}

void tomarLocalidades(char *localidades) {
    int pos = 0;

    FILE *localidadesFile;
    localidadesFile = fopen("codigoLocalidades.txt", "r");

    while (!feof((FILE*)localidadesFile)) {
        localidades[pos] = (char *) malloc(50 * sizeof(char));

        fgets(localidades[pos], 50, (FILE*)localidadesFile);

        obtenerLocalidad(&localidades[pos]);

        printf("%s\n", localidades[pos]);

        ++pos;
    }

    fclose(localidadesFile);
}

int cantidadLocalidades() {
    int cantLocalidades = 1;

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

int main()
{
    int cantLocalidades;

    cantLocalidades = cantidadLocalidades();

    char *localidades[cantLocalidades];

    tomarLocalidades(&localidades);
/*
    for (int n = 0 ; n < (cantLocalidades - 1) ; ++n) {
        printf("%s\n", localidades[n]);
    }
*/
    return 0;
}
