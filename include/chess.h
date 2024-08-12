#ifndef CHESS_H
#define CHESS_H

#include "gba/types.h"
#include "main.h"

/*
 * Entry tasks for the different versions of the UI. In `start_menu.c', we'll launch a task using one of
 * these functions. You can change which is used to change which menu is launched.
 */

// Launch the basic version of the UI
void Task_OpenSampleUi_StartHere(u8 taskId);

#endif
