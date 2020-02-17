#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cliente.h"
#include "shared.h"
#include "fichero.h"

char *menuModuloCliente[] = {
    "Nuevo Cliente",
    "Modificar Cliente",
    "Eliminar Cliente",
    "Listar Clientes",
    "Retroceder"
};

// Variables Globales externas
Cliente listaCliente[100] = {0};
int contadorCliente = 0;

void moduloCliente() {
    //Cliente

    int opcionMenuCliente = -1;

    do {
        system("clear");
        puts("\t\t\t ** CLIENTE** ");
        opcionMenuCliente = seleccionarOpcionMenu(menuModuloCliente, 5);

        switch (opcionMenuCliente) {
            case 1:
                system("clear");
                Cliente auxCliente = NuevoCliente(contadorCliente);
                if (auxCliente.cedula == 0) break;
                listaCliente[contadorCliente++] = auxCliente;
                archivarClientes(listaCliente, contadorCliente);
                puts("Registro Ingresado con exito!!!");
                clean_stdin();
                break;
            case 2:
                modificarCliente();
                break;
            case 3:
                system("clear");
                int opcionIDcliente = -1;
                imprimirListaClientes(listaCliente, contadorCliente);
                printf("\n Seleccione ID del cliente: ");
                fflush(stdin);
                scanf("%d", &opcionIDcliente);
                eliminarDatosCliente(listaCliente, &contadorCliente, opcionIDcliente);
                clean_stdin();
                break;

            case 4:
                system("clear");
                imprimirListaClientes(listaCliente, contadorCliente);
                clean_stdin();
                break;
        }
    } while (opcionMenuCliente != 5);
}

void eliminarDatosCliente(Cliente clientes[], int* contadorCliente, int idCliente) {
    for (int p = idCliente; p<*contadorCliente - 1; p++) {
        clientes[p] = clientes[p + 1];
        strcpy(clientes[p].nombres, clientes[p + 1].nombres);
        strcpy(clientes[p].direccion, clientes[p + 1].direccion);
        strcpy(clientes[p].telefono, clientes[p + 1].telefono);
        clientes[p].cedula = clientes[p + 1].cedula;

    }
    *contadorCliente = *contadorCliente - 1;
}

void modificarCliente() {

    int opcionIDcliente = -1;
    Cliente auxCliente = {0};

    system("clear");
    puts("\t\t\t *** MODIFICAR CLIENTE ***");
    imprimirListaClientes(listaCliente, contadorCliente);
    printf("\n Seleccione ID del cliente: ");
    fflush(stdin);
    scanf("%d", &opcionIDcliente);

    auxCliente = buscarClienteByID(listaCliente, contadorCliente, opcionIDcliente);

    if (auxCliente.cedula != 0) {

        auxCliente = NuevoCliente(opcionIDcliente);

        for (int i = 0; i < contadorCliente; i++) {
            if (auxCliente.id == listaCliente[i].id) {
                listaCliente[i] = auxCliente;
                archivarClientes(listaCliente, contadorCliente);
                printf("\n Cliente %d modificado exitosamente!!!", listaCliente[i].id);
                clean_stdin();
                break;
            }
        }
    }
}

void imprimirListaClientes(Cliente listaClientes[], int sizeListaClientes) {

    puts("\t\t\t ** Lista Clientes **");
    puts("_________________________________________________________________________________________________________");
    printf("| %2s | %20s \t | %10s \t | %10s \t | %20s \t |\n", "ID_CLIENT", "NOMBRES", "CEDULA/RUC", "TELEFONO", "DIRECCION");
    puts("=========================================================================================================");
    for (int i = 0; i < sizeListaClientes; i++) {
        printf("|     %02d    | %20s \t | %10d \t | %10s \t | %20s \t \n",
                listaClientes[i].id, listaClientes[i].nombres,
                listaClientes[i].cedula, listaClientes[i].telefono,
                listaClientes[i].direccion);
    }
}

Cliente buscarClienteByID(Cliente listaClientes[], int sizeListaClientes, int idCliente) {

    Cliente clienteEncontrado = {0};
    for (int i = 0; i < sizeListaClientes; i++) {
        if (idCliente == listaClientes[i].id) {
            clienteEncontrado = listaClientes[i];
            break;
        }
    }
    return clienteEncontrado;
}

Cliente NuevoCliente(int contCliAux) {
    Cliente cliAux = {0};
    cliAux.id = contCliAux;

    int registrarCliente = NO;

    do {
        printf("INGRESE LA INFORMACION DEL CLIENTE %d\n\n", contCliAux);
        printf("CEDULA/RUC: ");
        clean_stdin_dontStop();
        scanf("%d", &cliAux.cedula);

        printf("NOMBRE Y APELLIDO: ");
        clean_stdin_dontStop();
        scanf("%[^\n]", &cliAux.nombres);

        printf("TELEFONO: ");
        clean_stdin_dontStop();
        scanf("%s", &cliAux.telefono);

        printf("DIRECCION: ");
        clean_stdin_dontStop();
        scanf("%[^\n]", &cliAux.direccion);

        printf("\nConfirmar Registro?, 1 [SI], 0 [Cancelar y Salir], cualquier tecla [Modificar]: ");
        clean_stdin_dontStop();
        scanf("%d", &registrarCliente);
        if (registrarCliente == 1) registrarCliente = SI;
        if (registrarCliente == 0) {
            cliAux.cedula = 0;
        }
    } while (registrarCliente = NO);
    return (cliAux);
}

Cliente *eliminarCliente(int idCliente, Cliente *listaClientes, int sizeListaClientes) {

    Cliente auxNuevaListaClientes[] = {0};
    for (int i = 0; i < sizeListaClientes; i++) {
        if (listaClientes[i].id != idCliente)
            auxNuevaListaClientes[i] = listaClientes[i];
    }

    return auxNuevaListaClientes;
}
