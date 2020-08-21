#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

typedef struct {
    char nombre[50];
    char apellidos[50];
    int edad;
    char telefono[50];
    int id;
    int cama;
    int status; // 0 -> alta 1 -> internado
} paciente;

typedef struct {
    int estatus; // 0-> ocupada/false ocupada 1-> libre/true
    int idpaciente;
    int id;
} cama;

typedef void (* menu_t)();

int numPacientes = 0;
int numCama = 0;
int count = 1;
int flag = 0;
paciente *p1;
cama *c;
void agregarPaciente();
void ListaDePacientes();
void DarDeAlta();
void asignarCama();
void Alta(paciente *, cama *);
long int imprimir(paciente *);
int main(int argc, const char * args []){
    int opcion = -1;
    
    menu_t * opciones = (menu_t *) malloc(N * sizeof(menu_t));
    
    *opciones = agregarPaciente;
    *(opciones+1) = ListaDePacientes;
    *(opciones+2) = DarDeAlta;
    
    c = (cama *) malloc(sizeof(cama)*N);
    for(int i = 0; i<N; i++){
        (c+i)->estatus = 1;
    }
    while (opcion != 0) {
        printf("1. Agregar un nuevo paciente \n2. Lista de pacientes \n3. Dar de Alta\n0-Salir\n");
        
        printf("Selecciona tu opción: ");
        scanf("%d", &opcion);
        
        if (opcion > 0 && opcion <= N) {
            (*(opciones[opcion-1]))();
        }    
    }
    free(opciones);
    
    return 0;
}

void agregarPaciente(){
    numPacientes++;
    numCama++;
    paciente * ingresado;

    if(numPacientes>1){
        p1 = (paciente *) realloc(p1,(numPacientes*sizeof(paciente)));
        for (int i = 0; i < numPacientes; i++)
        {
             if((p1+i)->status==1){
             }
             else{
                (p1+i)->status=0;
             }
        }
        
    }
    else{
        p1 = (paciente *) malloc(sizeof(paciente)*numPacientes);
        for (int i = 0; i < numPacientes; i++)
        {
            (p1+i)->status=0;
        }
    }

    ingresado = p1+numPacientes;
    ingresado -> id = numPacientes;
    ingresado->status=1;
    
    asignarCama(c, ingresado);
    if(flag==0){
        printf("Datos de la persona \n");
            
        printf("Entre el nombre: ");
        scanf(" %[^\n]",ingresado->nombre);

        printf("Entre el apellidos: ");
        scanf(" %[^\n]",ingresado->apellidos);
        
        printf("Entre la edad: ");
        scanf(" %d",&ingresado->edad);

        printf("Entre el numero telefonico ");
        scanf(" %s",ingresado->telefono);
    }
}
void ListaDePacientes()
{
    imprimir(p1);
}
void DarDeAlta(){
    imprimir(p1);
    Alta(p1, c);
}

long int imprimir(paciente * p1){
    paciente * p;
    for (int i = 1; i <= numPacientes; i++)
    {
        p = p1+i;
        if(p->status==1){
            printf("\n\tPaciente: %d \n\tNombre: %s \n\tApellidos: %s \n\tEdad: %d \n\tTelefono: %s \n\tCama asignada: %d\n\n",(p->id),(p->nombre),(p->apellidos),(p->edad),(p->telefono),(p->cama));
        }   
    }
    for (int i = 0; i < N*count; i++)
    {
        printf("\n Cama %d asignada a paciente %d con estatus %d \n", (c+i)->id,(c+i)->idpaciente,(c+i)->estatus);
    }
    
    return 0;
}
void asignarCama(cama * c, paciente * p1){
    cama * aux = c;
    paciente * p = p1;
    int disponibilidad = 0;

    for(int i = 0; i<N*count; i++){
        if((aux+i)->estatus==1){
            (aux+i)->estatus=0;
            (aux+i)->idpaciente=p->id;
            if((aux+i)->id==0){
                (aux+i)->id=numCama;
            }
            p->cama=((aux+i)->id);
            printf("\nCama asignada: %d\n",(aux+i)->id);
            disponibilidad = 1;
            break;
        }
    }
    if(disponibilidad==0){
        printf("No hay camas disponibles ¿Desea agregar más? Y/N\n");
        char resp;
        scanf(" %c",&resp);
        if(resp=='Y'){
            count++;
            c = (cama *) realloc(c,(N*count)*sizeof(cama));

            for(int i = 0; i<N*count; i++){
                if((aux+i)->idpaciente==0){
                    (aux+i)->estatus=1;
                }
            printf("cama: %d paciente: %d\n",(aux+i)->id,(aux+i)->idpaciente);
            }
        asignarCama(c,p1);
        }
        else{
            printf("No pueden ser ingresados más pacientes");
            flag = 1;
        }
    }
}
void Alta(paciente * p1, cama * c){
    int idc;
    printf("Ingrese el numero de cama del paciente que desea dar de alta \n");
    scanf("%d",&idc);
    paciente * p = p1;
    cama * cma = c;
    for (int i = 0; i < numPacientes; i++)
    {
        if((p+i)->cama==idc){
            (p+i)->status=0;
            for (int j = 0; j < N*count; j++)
            {
                if((cma+j)->id==(p+i)->cama){
                (cma+j)->estatus=1;
                (cma+j)->idpaciente=0;
                }
            printf("\n Cama %d asignada a paciente %d con estatus %d \n", (cma+j)->id,(cma+j)->idpaciente,(cma+j)->estatus);
            }
        }
    }
    
}
