#ifndef QUEUE_H
#define QUEUE_H

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct File File;
struct File
{
    Element *premier;
};


void enfiler(File *file, int nvNombre);
int defiler(File *file);


#endif