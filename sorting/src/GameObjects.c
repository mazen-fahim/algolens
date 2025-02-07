#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../include/LinkedList.h"
#include "../include/GameObjects.h"

/* Keep track of created game objects in a linked list*/
List rectangles;
List lines; List polygons;

static void destroyRectangles(void *data){free((Rectangle *) data);}
static void destroyLines(void *data){free((Line *) data);}
static void destroyPolygons(void *data){free((Polygon *) data);}
Rectangle *createRectangle(int id, float x, float y,  float width, float height, float mass, float xSpeed, float ySpeed, float xForce, float yForce,
        int red, int green, int blue, int alpha, bool gravity ,void(*update)(struct Rectangle*, float elapsed))
{
    // Initialize the linked list only once
    static bool initialize = false;
    if(!initialize){
        list_init(&rectangles, destroyRectangles);
        initialize = true;
    }

    // Create the square and add to the linked list
    // the square will be freed in two cases
    //  1) shutDown function will destroy all of the linked list
    //  2) when removing an element from the linked list it will free it using the
    //      provided destroy function above
    Rectangle *rectangle = (Rectangle *)malloc(sizeof(Rectangle));
    rectangle->id = id;
    rectangle->x = x;
    rectangle->y = y;
    rectangle->width = width;
    rectangle->height = height;
    rectangle->mass = mass;
    rectangle->widthScale = 1;
    rectangle->heightScale = 1;
    rectangle->xForce = xForce;
    rectangle->yForce = yForce + ((gravity)? 9.8 : 0);
    rectangle->xSpeed = xSpeed;
    rectangle->ySpeed = ySpeed;
    rectangle->red = red;
    rectangle->green = green;
    rectangle->blue = blue;
    rectangle->alpha = alpha;
    rectangle->gravity = gravity;
    rectangle->update = update;
    rectangle->rect.x = rectangle->x;
    rectangle->rect.y = rectangle->y;
    rectangle->rect.w = rectangle->width * rectangle->widthScale;
    rectangle->rect.h = rectangle->height * rectangle->heightScale;
    list_ins_next(&rectangles, NULL, rectangle);
    return rectangle;
}

void createLine(float x1, float y1, float x2, float y2, int thickness, float xSpeed, float ySpeed, float mass, float xForce, float yForce,
        int red, int green, int blue, int alpha, bool gravity ,void(*update)(struct Line*, float elapsed))
{
    // Initialize the linked list only once
    static bool initialize = false;
    if(!initialize){
        list_init(&lines, destroyLines);
        initialize = true;
    }
    Line *line = (Line *)malloc(sizeof(Line));
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    line->thickness = thickness;
    line->xSpeed = xSpeed;
    line->ySpeed = ySpeed;
    line->xForce = xForce;
    line->yForce = yForce + ((gravity)? 9.8 : 0);
    line->mass = mass;
    line->red = red;
    line->green = green;
    line->blue = blue;
    line->alpha = alpha;
    line->gravity = gravity;
    line->update = update;
    list_ins_next(&lines, NULL, line);
}

void createPolygon(float x, float y, unsigned numberOfSides, float sideLength, float sideScale, float mass, float xSpeed, float ySpeed, float xForce, float yForce,
        int red, int green, int blue, int alpha, bool gravity ,void(*update)(struct Polygon*, float elapsed))
{
    // Initialize the linked list only once
    static bool initialize = false;
    if(!initialize){
        list_init(&polygons, destroyPolygons);
        initialize = true;
    }
    Polygon *polygon = (Polygon *)malloc(sizeof(Polygon));
    polygon->x = x;
    polygon->y = y;
    polygon-> numberOfSides = numberOfSides;
    polygon->sideLength = sideLength;
    polygon->sideScale = sideScale;
    polygon->radius = (sideLength*sideScale) / (2* sin(M_PI/numberOfSides));
    polygon->mass = mass;
    polygon->xSpeed = xSpeed;
    polygon->ySpeed = ySpeed;
    polygon->xForce = xForce;
    polygon->yForce = yForce + ((gravity)? 9.8 : 0);
    polygon->red = red;
    polygon->green = green;
    polygon->blue = blue;
    polygon->alpha = alpha;
    polygon->gravity = gravity;
    polygon->update = update;
    list_ins_next(&polygons, NULL, polygon);
}
