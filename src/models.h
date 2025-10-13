#ifndef _MODELS_H
#define _MODELS_H

#include "raylib.h"
#include "config.h"

extern int ModelAppend(Model model);
int ModelSet(unsigned int idx, Model model);
Model ModelFetch(unsigned int idx);
int ModelRemove(unsigned int idx);
int ModelRemoveAll();

#endif
