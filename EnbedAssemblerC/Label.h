#pragma once
#include<string.h>
#include<stdlib.h>
#define LABELNAME_MAX 300
#define MAX_LABEL 30
#define MAX_LABEL_IN_CODE 300
struct LABEL {
	int pos;
	char name[LABELNAME_MAX];
};
struct LABEL labels[MAX_LABEL];
struct LABEL_PLACE {
	int pos;
	char name[LABELNAME_MAX];
};
struct LABEL_PLACE label_places[MAX_LABEL_IN_CODE];
static labelnum = 0;
void set_label(const char* name, int place) {
	strncpy_s(labels[labelnum].name,sizeof(labels[labelnum].name),name,strlen(name)-1);
	labels[labelnum].pos = place;
	labelnum++;
}
int get_label(const char* name) {
	for (int i = 0; i < labelnum; i++) {
		if (strcmp(labels[i].name, name) == 0) {
			return labels[i].pos;
		}
	}
	return strtol(name, NULL, 16);
}
