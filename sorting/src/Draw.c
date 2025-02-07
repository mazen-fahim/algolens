#include <SDL2/SDL.h>
#include <math.h>
#include "../include/LinkedList.h"
#include "../include/GameObjects.h"
#include "../include/globals.h"

void drawLines(void)
{
    for(List_elmt *temp = lines.head; temp != NULL; ){
        Line *line = ((Line *)temp->data);
        SDL_SetRenderDrawColor(rendererGlobal, line->red, line->green, line->blue, line->alpha);
        SDL_Point point1 = {line->x1, line->y1};
        SDL_Point point2 = {line->x2, line->y2};
        for(int i =0; i < line->thickness; i++)
        {
            SDL_RenderDrawLineF(rendererGlobal, point1.x, point1.y, point2.x,point2.y);
            point1.x += 1;
            point2.x += 1;
        }
        temp = temp->next;
    }
}

void drawRectangles(void)
{
    for(List_elmt *temp = rectangles.head; temp != NULL; ){ 
        Rectangle*rectangle = ((Rectangle *)temp->data);
        SDL_SetRenderDrawColor(rendererGlobal, rectangle->red, rectangle->green, rectangle->blue, rectangle->alpha);
        rectangle->rect.x = rectangle->x;
        rectangle->rect.y = rectangle->y;
        rectangle->rect.h = rectangle->height;
        rectangle->rect.w = rectangle->width;
        SDL_RenderFillRect(rendererGlobal, &(rectangle->rect));
        temp = temp->next;
    }
}

void drawPolygons(void)
{
    float totalAngle = 360;
    float stepAngle;
    SDL_Point point1;
    SDL_Point point2;
    for(List_elmt *temp = polygons.head; temp != NULL; ){
        Polygon* polygon = ((Polygon *)temp->data);
        SDL_SetRenderDrawColor(rendererGlobal, polygon->red, polygon->green, polygon->blue, polygon->alpha);
        SDL_RenderDrawPoint(rendererGlobal, polygon->x, polygon->y);
        stepAngle = totalAngle/polygon->numberOfSides;
        stepAngle = stepAngle * M_PI/180;
        // sin and cos are not accurate.
        for(int i = 0; i < polygon->numberOfSides; i++)
        {
            point1.x = polygon->x + cos(stepAngle *   i  ) * polygon->radius;
            point1.y = polygon->y + sin(stepAngle *   i  ) * polygon->radius;
            point2.x = polygon->x + cos(stepAngle * (i+1)) * polygon->radius;
            point2.y = polygon->y + sin(stepAngle * (i+1)) * polygon->radius;
            if(i == polygon->numberOfSides -1){
                point2.x = polygon->x +  polygon->radius;
                point2.y = polygon->y;
            }
            SDL_RenderDrawLineF(rendererGlobal, point1.x, point1.y, point2.x,point2.y);
        }
        temp = temp->next;
    }
}

void draw(void)
{
    SDL_SetRenderDrawColor(rendererGlobal, 0, 0, 0, 255);
    SDL_RenderClear(rendererGlobal);
    drawLines();
    drawRectangles();
    drawPolygons();
    SDL_RenderPresent(rendererGlobal);
}
