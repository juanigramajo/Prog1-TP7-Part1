#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct fecha
{
    int dia;
    int mes;
    int ano;
} typedef fecha;

struct publicacion
{
    char titulo[30];
    char editorial[30];
    int edicion;
    fecha fec_publicacion;
    char tieneisbn;
    long int isbn;
    char categoria;
    int cantidad;
    int stock;
} typedef publi;


publi cargar();
void mostrar(publi datos, char categoriaNueva);
char editar(publi datos);


int main() {
    publi datos;
    char categoriaNueva;

    datos = cargar();

    categoriaNueva = editar(datos);

    mostrar(datos, categoriaNueva);

    return 0;
}


publi cargar(){
    publi informacion;

    puts("\n---------------CARGA DE DATOS---------------");
    printf("Ingrese el título: ");
    gets(informacion.titulo);

    printf("Ingrese la editorial: ");
    gets(informacion.editorial);

    printf("Ingrese el número de edición: ");
    scanf("%d", &informacion.edicion);

    printf("Ingrese la fecha de publicación (dd / mm / aaaa): ");
    scanf("%d %d %d", &informacion.fec_publicacion.dia, &informacion.fec_publicacion.mes, &informacion.fec_publicacion.ano);
    

    while (informacion.fec_publicacion.dia < 1 || informacion.fec_publicacion.dia > 31) {
        printf("\nIngrese un día valido (1 - 31)\nIngrese el día correcto: ");
        scanf("%d", &informacion.fec_publicacion.dia);
    }

    while (informacion.fec_publicacion.mes < 1 || informacion.fec_publicacion.mes > 12) {
        printf("\nIngrese un mes valido (1 - 12)\nIngrese el mes correcto: ");
        scanf("%d", &informacion.fec_publicacion.mes);
        
    }

    while (informacion.fec_publicacion.ano < 1000 || informacion.fec_publicacion.ano > 2022) {
        printf("\nIngrese un año valido (1000 - 2022)\nIngrese el año correcto: ");
        scanf("%d", &informacion.fec_publicacion.ano);
    }
    
    printf("\n¿Tiene ISBN?\nPresione S para indicar SI o presione N para indicar NO: ");
    scanf(" %c", &informacion.tieneisbn);
    
    while (informacion.tieneisbn != 'S' && informacion.tieneisbn != 's' && informacion.tieneisbn != 'N' && informacion.tieneisbn != 'n')
    {
        printf("\n\nError de formato\nPresione S para indicar SI o N para indicar NO: ");
        scanf(" %c", &informacion.tieneisbn);
    }

    if (informacion.tieneisbn == 'S' || informacion.tieneisbn == 's')
    {
        printf("Ingrese el ISBN: ");
        scanf("%ld", &informacion.isbn);

        long int aux = informacion.isbn;
        int contador = 0;

        while (aux > 0) {
            aux = aux / 10;
            contador ++;
        }

        while (contador < 10 || contador > 13) {
            printf("\nIngrese un número válido (entre 10 y 13 dígitos)\nIngrese el ISBN: ");
            scanf("%ld", &informacion.isbn);

            aux = informacion.isbn;
            contador = 0;

            while (aux > 0) {
            aux = aux / 10;
            contador ++;
            }
        }
    } else if (informacion.tieneisbn == 'N' || informacion.tieneisbn == 'n')
    {
        informacion.isbn = 0;
    }
    
    fflush(stdin);
    printf("\nCATEGORÍAS:\nPresione L para LIBRO\nPresione R para REVISTA\nPresione T para TESIS\n\nIngrese la categoría: ");
    scanf(" %c", &informacion.categoria);
    
    while (informacion.categoria != 'L' && informacion.categoria != 'l' && informacion.categoria != 'R' && informacion.categoria != 'r' && informacion.categoria != 'T' && informacion.categoria != 't')
    {
        printf("\nError de formato\n(Presione L para LIBRO)\n(Presione R para REVISTA)\n(Presione T para TESIS): ");
        scanf(" %c", &informacion.categoria);
    }

    
    printf("Ingrese la cantidad de ejemplares: ");
    scanf("%d", &informacion.cantidad);    

    while (informacion.cantidad < 1) {
        printf("\nNo puede haber menos de 1 ejemplar, ingrese la cantidad de ejemplares: ");
        scanf("%d", &informacion.cantidad);
    }


    printf("Ingrese la cantidad de ejemplares en stock: ");
    scanf("%d", &informacion.stock);

    while (informacion.stock > informacion.cantidad) {
        printf("\nNo puede haber más ejemplares en stock que la cantidad declarada de ejemplares, ingrese la cantidad de ejemplares en stock: ");
        scanf("%d", &informacion.stock);
    }


    return (informacion);
}



void mostrar(publi informacion, char categoriaNueva){

    puts("\n ---------------Datos ingresados---------------");
    
    printf("Título: ");
    puts(informacion.titulo);

    printf("Editorial: ");
    puts(informacion.editorial);

    printf("Edicion número %d \n", informacion.edicion);

    printf("Publicada el %d / %d / %d \n", informacion.fec_publicacion.dia, informacion.fec_publicacion.mes, informacion.fec_publicacion.ano);

    printf("ISBN: %ld \n", informacion.isbn);

    switch (categoriaNueva)
    {
    case 'l':
        printf("Categoría: Libro\n");
        break;
    case 'r':
        printf("Categoría: Revista\n");
        break;
    case 't':
        printf("Categoría: Tesis\n");
        break;
    }

    printf("Cantidad de ejemplares: %d \n", informacion.cantidad);

    printf("Cantidad de ejemplares en Stock: %d \n", informacion.stock);
}


char editar(publi informacion)
{
    int editorial1 = strcmp(informacion.editorial, "FACET");
    int editorial2 = strcmp(informacion.editorial, "facet");
    int editorial3 = strcmp(informacion.editorial, "Facet");

    if (informacion.isbn == 0 && (editorial1 == 0 || editorial2 == 0 || editorial3 == 0))
    {
        informacion.categoria = 't';

    } else if (informacion.isbn == 0 && (editorial1 != 0 && editorial2 != 0 && editorial3 != 0))
    {
        informacion.categoria = 'r';
    }
    
    if (informacion.isbn != 0)
    {
        informacion.categoria = 'l';
    }

    informacion.categoria = tolower(informacion.categoria);
    

    return(informacion.categoria);

}