#pragma once
#include<string.h>
#define REG_NAME_MAX 3
enum ResisterNum {
	A = 0b01, B = 0b10, C = 0b11
};
char* ResisterNames[] = {
	"A","B","C"
};
struct Resister {
	char name[REG_NAME_MAX + 1];
	enum ResisterNum number;
};
struct Resister resisters[3];
void init_resisters() {
	for (int i = 0; i < 3; i++) {
		strcpy_s(resisters[i].name, sizeof(resisters[i].name), ResisterNames[i]);
		resisters[i].number = (enum ResisterNum)(i + 1);
	}
}

int check_resister(const char* resister) {
	for (int i = 0; i < 3; i++) {
		if (strcmp(resister, resisters[i].name)==0)return resisters[i].number;
	}
	return -1;
}