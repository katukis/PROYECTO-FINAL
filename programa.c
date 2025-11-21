#include <stdio.h>
void resetear(int arr[], int tam) 
{
    int i;
    for (i = 0; i < tam; i++) 
    {
        arr[i] = 0;
    }
}

int metervotos(int tabla[][3]) 
{
    int total = 0;
    int a, b, c;

    printf("concurso de canciones\n");
    printf("canciones del 0 al 9\n");
    printf("puntos: 3, 2, 1\n");
    printf("para terminar escribe -1 al inicio\n\n");

    while (total < 100) 
    {
        printf("persona %d ingresa 3 canciones: ", total);

        if (scanf("%d", &a) != 1) 
        {
            break;
        }

        if (a == -1) 
        {
            break;
        }

        scanf("%d %d", &b, &c);

        tabla[total][0] = a;
        tabla[total][1] = b;
        tabla[total][2] = c;

        total++;
    }

    return total;
}

void puntoscancion(int tabla[][3], int total, int puntos[]) 
{
    int i;
    int x, y, z;

    for (i = 0; i < total; i++) 
    {
        x = tabla[i][0];
        y = tabla[i][1];
        z = tabla[i][2];

        if (x >= 0 && x < 10) puntos[x] += 3;
        if (y >= 0 && y < 10) puntos[y] += 2;
        if (z >= 0 && z < 10) puntos[z] += 1;
    }
}

void top2(int puntos[], int *primero, int *segundo) 
{
    int i;
    int m1 = -1, m2 = -1;
    int id1 = -1, id2 = -1;

    for (i = 0; i < 10; i++) 
    {
        if (puntos[i] > m1) 
        {
            m2 = m1;
            id2 = id1;

            m1 = puntos[i];
            id1 = i;
        } else if (puntos[i] > m2 && i != id1) 
        {
            m2 = puntos[i];
            id2 = i;
        }
    }

    *primero = id1;
    *segundo = id2;
}

void puntospersonas(int tabla[][3], int total, int c1, int c2, int puntos[]) 
{
    int i, j;
    int ok1, ok2;

    for (i = 0; i < total; i++) 
    {
        ok1 = 0;
        ok2 = 0;

        for (j = 0; j < 3; j++) 
        {
            if (tabla[i][j] == c1) ok1 = 1;
            if (tabla[i][j] == c2) ok2 = 1;
        }

        if (ok1) puntos[i] += 30;
        if (ok2) puntos[i] += 20;
        if (ok1 && ok2) puntos[i] += 10;
    }
}

int ganador(int puntos[], int total) 
{
    int i;
    int mayor = -1;
    int quien = -1;

    for (i = 0; i < total; i++) 
    {
        if (puntos[i] > mayor) 
        {
            mayor = puntos[i];
            quien = i;
        }
    }

    return quien;
}

int main() 
{

    int tabla[100][3];
    int puntoscanciones[10];
    int puntospersona[100];
    int totalpersonas;
    int c1, c2;
    int quien;
    int i;

    resetear(puntoscanciones, 10);
    resetear(puntospersona, 100);

    totalpersonas = metervotos(tabla);

    if (totalpersonas == 0) 
    {
        printf("no se registraron votos\n");
        return 0;
    }

    puntoscancion(tabla, totalpersonas, puntoscanciones);
    top2(puntoscanciones, &c1, &c2);

    printf("\npuntos por cancion:\n");
    for (i = 0; i < 10; i++) {
        printf("cancion %d: %d puntos\n", i, puntoscanciones[i]);
    }

    printf("\nmas votada: %d\n", c1);
    printf("segunda mas votada: %d\n", c2);

    puntospersonas(tabla, totalpersonas, c1, c2, puntospersona);

    printf("\npuntos por persona:\n");
    for (i = 0; i < totalpersonas; i++) 
    {
        printf("persona %d tiene %d puntos\n", i, puntospersona[i]);
    }

    quien = ganador(puntospersona, totalpersonas);

    printf("\nganador del concurso: persona %d\n", quien);

    return 0;
}
