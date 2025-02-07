#include <SDL2/SDL.h>
#include "../include/LinkedList.h"
#include "../include/GameObjects.h"
#include "../include/globals.h"

void handleKeyPressed(SDL_Keysym *key)
{
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    // arrow keys
    if((keyboardState[SDL_SCANCODE_UP] && keyboardState[SDL_SCANCODE_DOWN]) || (!keyboardState[SDL_SCANCODE_UP] && !keyboardState[SDL_SCANCODE_DOWN])){
        for(List_elmt *temp = rectangles.head; temp != NULL; ){
            Rectangle *rectangle = ((Rectangle *)temp->data);
            if(rectangle->id == 0)
                rectangle->ySpeed = 0;
            temp = temp->next;
        }
    }
    else if(keyboardState[SDL_SCANCODE_UP]){
        for(List_elmt *temp = rectangles.head; temp != NULL; ){
            Rectangle *rectangle = ((Rectangle *)temp->data);
            if(rectangle->id == 0)
                rectangle->ySpeed = -windowGlobal.windowHeight * 1.5;
            temp = temp->next;
        }
    }
    else if(keyboardState[SDL_SCANCODE_DOWN]){
        for(List_elmt *temp = rectangles.head; temp != NULL; ){
            Rectangle *rectangle = ((Rectangle *)temp->data);
            if(rectangle->id == 0)
                rectangle->ySpeed = windowGlobal.windowHeight * 1.5;
            temp = temp->next;
        }
    }

    // Keypad 
    if((keyboardState[SDL_SCANCODE_KP_8] && keyboardState[SDL_SCANCODE_KP_2]) || (!keyboardState[SDL_SCANCODE_KP_8] && !keyboardState[SDL_SCANCODE_KP_2])){
        for(List_elmt *temp = rectangles.head; temp != NULL; ){
            Rectangle *rectangle = ((Rectangle *)temp->data);
            if(rectangle->id == 1)
                rectangle->ySpeed = 0;
            temp = temp->next;
        }
    }
    else if(keyboardState[SDL_SCANCODE_KP_8]){
        for(List_elmt *temp = rectangles.head; temp != NULL; ){
            Rectangle *rectangle = ((Rectangle *)temp->data);
            if(rectangle->id == 1)
                rectangle->ySpeed = -windowGlobal.windowHeight * 1.5;
            temp = temp->next;
        }
    }
    else if(keyboardState[SDL_SCANCODE_KP_2]){
        for(List_elmt *temp = rectangles.head; temp != NULL; ){
            Rectangle *rectangle = ((Rectangle *)temp->data);
            if(rectangle->id == 1)
                rectangle->ySpeed = windowGlobal.windowHeight * 1.5;
            temp = temp->next;
        }
    }
}
