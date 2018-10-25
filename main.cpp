/*
 PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 201820
 Natalia Sanabria Forero - 201532265
 Santiago Barbosa Nieto - 201730869
 Cristina Isabel González Osorio - 201520019
 */

#include <iostream>

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//-- Definicion de la estructura para los datos del archivo de entrada y el de salida
typedef struct datos
{
    int tamanio;
    unsigned char *informacion;
} Datos;


//-- Prototipos de las funciones
int readFile(Datos * archivo, char *);
void writeFile(int, Datos * archivoEnOctal, char *);
void convertirAOctal(Datos * archivo, Datos * archivoEnOctal);


//-- Funciones

// Esta funcion se encarga de abrir un datos y leerlo en el vector informacion.
// Retorna el numero de bytes leidos.
// No hay que completar nada en esta funcion.
int readFile(Datos * archivo, char * nombreArchivo)
{
    FILE *file;
    int n;
    int x;
    
    file = fopen(nombreArchivo, "rb");
    
    if (!file)
    {
        printf("No se pudo abrir el archivo para leer: %s\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    n = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    archivo->tamanio = n;
    archivo->informacion = (unsigned char *)calloc(n, sizeof(unsigned char));
    
    for (x = 0; x < n; x++)
    {
        fread(&archivo->informacion[x], sizeof(unsigned char), 1, file);
    }
    archivo->informacion[x] = '\0';
    
    fclose(file);
    
    return n;
}


// Esta funcion se encarga de escribir un datos a partir del vector datos.
// El numero de bytes que se deben escribir viene en el parametro n.
// No hay que completar nada en esta funcion.
void writeFile(int n, Datos * archivoEnOctal, char *nombreArchivo)
{
    FILE *file;
    
    file = fopen(nombreArchivo, "wb");
    
    if (!file) {
        printf("No se pudo abrir el archivo para escribir: %s\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }
    
    fwrite((archivoEnOctal->informacion), 1, n, file);
    
    fclose(file);
}


// Esta funcion se encarga de convertir a octal cada uno de los bytes que se
//encuentran en la estructura datosBin->informacion y asignar los nuevos valores a la estructura datosOct->informacion.
// Deben desarrollar esta funcion en su totalidad.
void convertirAOctal(Datos * datosBin, Datos * datosOct)
{
    //TODO: COMPLETAR EL DESARROLLO DE LA FUNCION.
    int tamanio = (datosBin->tamanio)*8;
    unsigned char *info = (datosBin->informacion);
    
    int tamBin;
    
    if (tamanio%3==0)
    {
        tamBin = tamanio;
    }
    else if( tamanio%3 == 1)
    {
        tamBin = tamanio+2;
    }
    else
    {
        tamBin = tamanio+1;
    }
    
    int datos[tamBin];
    
    // Inicializa en 0 las casillas adicionales si las hay
    for(int k = tamBin-1; k > tamanio-1; k++)
    {
        info[k] = 0;
    }
    
    //Convierte los caracteres en un arreglo de ints de unos y ceros
    for (int i = 0; i < tamanio/8; i++)
    {
        int binNumOfChar = (info[i]); //Valor numérico del char en la posición i
        int res; // Residuo
        
        for(int j = 8; j > 0; j-- )
        {
            res = binNumOfChar%2;
            
            datos[i+(j-1)] = res;
            
            binNumOfChar=binNumOfChar/2;
        }
        
    }
    
    int numOctal = 0;
    for(int l = 0; l < tamBin; l=l+3)
    {
        int octal = datos[l]*4 + datos[l+1]*2 + datos[l+2];
        datosOct[numOctal] = octal;
    }
}

//-- Funcion main de la aplicacion
// No hay que completar nada en esta funcion.
int main()
{
    // Mensaje inicial
    printf("PROYECTO 1 - INFRATEC (ISIS-1304)");
    
    // Declaracion de todas las variables necesarias.
    int tamanio;
    int tamanioRepOctales;
    char nombreArchivo[200];
    char nombreArchivoOctales[200];
    Datos * archivo = (Datos *)malloc(sizeof(Datos));
    Datos * archivoEnOctal = (Datos *)malloc(sizeof(Datos));
    
    printf("\n\nIngrese el nombre del archivo a leer (incluya el formato. i.e. archivo.txt): \n");
    scanf("%s", nombreArchivo);
    tamanio = readFile(archivo, nombreArchivo);
    printf("\nEl tamanio del archivo es de %d bytes\n", tamanio);
    tamanioRepOctales = ((tamanio * 8) / 3) + ((tamanio % 3 == 0)? 0 : 1);
    archivoEnOctal->informacion = (unsigned char *)calloc(tamanioRepOctales, sizeof(unsigned char));
    printf("\nIngrese el nombre del archivo para guardar la representacion en octales del archivo origen (incluya el .txt): \n");
    scanf("%s", &nombreArchivoOctales);
    convertirAOctal(archivo, archivoEnOctal);
    writeFile(tamanioRepOctales, archivoEnOctal, nombreArchivoOctales);
    printf("\nEl archivo se transformo en su representacion a octal exitosamente!\n\n");
    printf("Revisa el archivo con nombre '%s' para ver el resultado!\n", nombreArchivoOctales);
    
    // Terminar
    system("PAUSE");
}
