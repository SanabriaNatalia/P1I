/*
 PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 201820
 Natalia Sanabria Forero - 201532265 - n.sanabria@uniandes.edu.co
 Santiago Barbosa Nieto - 201730869 - s.barbosan@uniandes.edu.co
 Cristina Isabel González Osorio - 201520019 - ci.gonzalez10@uniandes.edu.co
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
    // Declaración de variables
	int tamanio = (datosBin->tamanio);
	unsigned char *info = (datosBin->informacion);
    int byte[8];   
    int tamBin = (tamanio*8);

    //Ajusta el tamaño del vector binario si no es módulo 3
    if(tamBin % 3 != 0)
    {
        tamBin += (3 - (tamBin % 3));
    }

    //Declaración de variables
    int binaryVector[tamBin];
    int j = 0;

    //Se traduce a binario byte a byte
    for(int k=0; k<=tamanio; k++)
    {
        int letter = info[k];
        int i;
         for(i=0; i<8; i++)    
        {    
            if(letter<=0)
            {
                byte[i] = 0;
            }
            else{
                byte[i]=letter%2;    
                letter = letter/2; 
            }     
        }   

        //Se invierte la secuencia de bits obtenida        
        for(i=i-1 ;i>=0 ;i--)    
        {   
            binaryVector[j] = byte[i]; 
            j += 1; 
        } 
    }

    //Se traduce cada grupo de 3 bits a octal
    int numOctal = 0;
	for (int l = 0; l < tamBin; l = l + 3)
	{
		int octal = binaryVector[l] * 4 + binaryVector[l + 1] * 2 + binaryVector[l + 2] + 48; //Se suma 48 para pasarlo a octal
		datosOct->informacion[numOctal] = octal;
		numOctal++;
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

