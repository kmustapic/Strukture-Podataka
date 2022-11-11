#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define MAX_LINE 1024

struct _Polinom;
typedef struct _Polinom *Pozicija;

typedef struct _Polinom
{
    int koef;
    int ekspo;
    Pozicija next;

} Polinom;

int CitanjeIzDatoteke(Pozicija a1, Pozicija a2);
int SortiranoDodavanje(Pozicija a, int koef, int ekspo);
int Delete(Pozicija a);
int IspisListe(Pozicija a);
int Umnozak(Pozicija a1, Pozicija a2, Pozicija produktHead);
int Sum(Pozicija a1, Pozicija a2, Pozicija sumaHead);

int main()
{
    Polinom head1, head2, produkt, suma;

    head1.next = NULL;
    head2.next = NULL;
    produkt.next = NULL;
    suma.next = NULL;

    CitanjeIzDatoteke(&head1, &head2);

    printf("Polinom 1: ");
    IspisListe(head1.next);

    printf("Polinom 2: ");
    IspisListe(head2.next);

    Umnozak(head1.next, head2.next, &produkt);
    printf("PRODUKT: ");
    IspisListe(produkt.next);

    Sum(head1.next, head2.next, &suma);
    printf("SUMA: ");
    IspisListe(suma.next);

    return 0;
}

int CitanjeIzDatoteke(Pozicija a1, Pozicija a2)
{

    FILE *datoteka = NULL;
    char buffer[MAX_LINE];
    char *bufferP = NULL;
    int k = 0, e = 0, n = 0;

    datoteka = fopen("pol.txt", "r");
    if (datoteka == NULL)
    {
        printf("Greska otvaranja datoteke.\n");
        return -1;
    }

    // Prvi polinom
    fgets(buffer, MAX_LINE, datoteka);
    bufferP = buffer;

    while (strlen(bufferP) > 0)
    {
        if (sscanf(bufferP, " %d %d %n", &k, &e, &n) == 2)
        {
            SortiranoDodavanje(a1, k, e);
        }
        bufferP = bufferP + n;
    }

    // Drugi polinom
    fgets(buffer, MAX_LINE, datoteka);
    bufferP = buffer;

    while (strlen(bufferP) > 0)
    {
        if (sscanf(bufferP, " %d %d %n", &k, &e, &n) == 2)
        {
            SortiranoDodavanje(a2, k, e);
        }
        bufferP = bufferP + n;
    }

    fclose(datoteka);
    return 0;
}

int SortiranoDodavanje(Pozicija a, int koef, int ekspo)
{
    Pozicija noviElement = NULL;

    while (a->next != NULL && (a->next->ekspo) > ekspo)
    {
        a = a->next;
    }
    if (a->next != NULL && (a->next->ekspo) == ekspo)
    {
        a->next->koef = a->next->koef + koef;
        if (a->next->koef == 0)
        {
            Delete(a);
        }
    }
    else
    {
        if (koef != 0)
        {
            noviElement = (Pozicija)malloc(sizeof(Polinom));
            if (noviElement == NULL)
            {
                printf("Greska kod alociranja memorije.");
                return -1;
            }
            noviElement->koef = koef;
            noviElement->ekspo = ekspo;
            noviElement->next = a->next;
            a->next = noviElement;
        }
    }

    return 0;
}

int Delete(Pozicija a)
{
    Pozicija temp = NULL;

    temp = a->next;
    a->next = temp->next;
    free(temp);
    return 0;
}

int IspisListe(Pozicija a)
{
    while (a != NULL)
    {
        printf("%dx^(%d)", a->koef, a->ekspo);
        if (a->next != NULL)
            printf(" + ");
        a = a->next;
    }
    printf("\n");
    return 0;
}

int Umnozak(Pozicija a1, Pozicija a2, Pozicija produktHead)
{
    Pozicija temp = a2;
    Pozicija element = NULL;
    int k, e;
    while (a1 != NULL)
    {
        a2 = temp;
        while (a2 != NULL)
        {

            k = a1->koef * a2->koef;
            e = a1->ekspo + a2->ekspo;
            SortiranoDodavanje(produktHead, k, e);
            a2 = a2->next;
        }
        a1 = a1->next;
    }

    return 0;
}

int Sum(Pozicija a1, Pozicija a2, Pozicija sumaHead)
{
    int k, e;

    while (a1 != NULL && a2 != NULL)
    {
        if (a1->ekspo == a2->ekspo)
        {
            e = a1->ekspo;           // eksponent sume
            k = a1->koef + a2->koef; // koeficijent sume
            SortiranoDodavanje(sumaHead, k, e);
            a1 = a1->next;
            a2 = a2->next;
        }
        else if (a1->ekspo > a2->ekspo)
        {
            e = a1->ekspo;
            k = a1->koef;
            SortiranoDodavanje(sumaHead, k, e);
            a1 = a1->next;
        }
        else if (a2->ekspo > a1->ekspo)
        {
            e = a2->ekspo;
            k = a2->koef;
            SortiranoDodavanje(sumaHead, k, e);
            a2 = a2->next;
        }
    }
    while(a1!=NULL) {
        if (a1 != NULL)
        {
            SortiranoDodavanje(sumaHead, a1->koef, a1->ekspo);
            a1 = a1->next;
        }
    }
    if (a2 != NULL)
    {
        while (a2 != NULL)
        {
            SortiranoDodavanje(sumaHead, a2->koef, a2->ekspo);
            a2 = a2->next;
        }
    }

    return 0;
}