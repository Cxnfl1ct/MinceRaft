#include "models.h"

Model dummy;

extern Model models[MAX_MODELS];
extern unsigned int models_cnt;

int ModelAppend(Model model) {
	if (models_cnt < 0 || models_cnt >= MAX_MODELS)
		return 1;

	models[models_cnt++] = model;

	return 0;
}

int ModelSet(unsigned int idx, Model model) {
	if (idx < 0 || idx >= models_cnt)
		return 1;

	models[idx] = model;

	return 0;
}

Model ModelFetch(unsigned int idx) {
	Model ret_model;

	if (idx >= 0 && idx < models_cnt)
		ret_model = models[idx];

	return ret_model;
}

int ModelRemove(unsigned int idx) {
	if (idx >= models_cnt)
		return 1;

	UnloadModel(models[idx]);

	if (models_cnt > 0)
		models_cnt--;

	return 0;
}

int ModelRemoveAll() {
	int i, lim;

	if (lim >= MAX_MODELS)
		lim = MAX_MODELS;
	else
		lim = models_cnt;

	for (i = 0; i <= lim; i++)
		UnloadModel(models[i]);

	models_cnt = 0;

	return 0;
}
