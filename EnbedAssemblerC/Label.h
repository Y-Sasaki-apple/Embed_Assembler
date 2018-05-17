#pragma once
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
void set_label(const char* name, int place) {

}
void set_label_place(const char* name, int place) {

}
int get_label(const char* name) {

}
