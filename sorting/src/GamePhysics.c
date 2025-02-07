#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/LinkedList.h"
#include "../include/GameObjects.h"
#include "../include/globals.h"

void applyPhysics(Rectangle *rectangle, float elapsed){
    if((rectangle->x) < (rectangle->width/2)){
        rectangle->xSpeed = abs((int)rectangle->xSpeed);
    }
    if((rectangle->x) > (windowGlobal.windowWidth - rectangle->width/2)){
        rectangle->xSpeed = -abs((int)rectangle->xSpeed);
    }
    if((rectangle->y) < (rectangle->height/2)){
        rectangle->ySpeed = abs((int)rectangle->ySpeed);
    }
    if((rectangle->y) > (windowGlobal.windowHeight - rectangle->height/2)){
        rectangle->ySpeed = -abs((int)rectangle->ySpeed);
    }
    // Dynamics (Newton laws)
    rectangle->xSpeed += rectangle->xForce / rectangle-> mass * elapsed;
    rectangle->x += rectangle->xSpeed * elapsed;
    rectangle->ySpeed += rectangle->yForce / rectangle-> mass * elapsed;
    rectangle->y += rectangle->ySpeed * elapsed;
}

void update(float elapsed)
{
    // Iterate over all the rectangles inside the linked list.
    for(List_elmt *temp = rectangles.head; temp != NULL; ){
        Rectangle *rectangle = ((Rectangle *)temp->data);
        applyPhysics(rectangle, elapsed);
        // call the user defined call back update function if not NULL.
        if(rectangle-> update != NULL)
            rectangle->update(rectangle, elapsed);
        temp = temp->next;
    }
}
