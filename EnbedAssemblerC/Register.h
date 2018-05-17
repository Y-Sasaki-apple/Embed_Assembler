#pragma once

#include<string.h>
enum ResisterNum {
	A = 0b01, B = 0b10, C = 0b11
};
char* ResisterNames[] = {
	"A","B","C"
};
struct Resister {
	char* name;
	enum ResisterNum number;
};
struct Resister resisters[3];
void init_resisters() {
	for (int i = 0; i < 3; i++) {
		resisters[i].name = ResisterNames[i];
		resisters[i].number = (enum ResisterNum)(i + 1);
	}
}

int check_resister(const char* resister) {
	for (int i = 0; i < 3; i++) {
		if (strcmp(resister, resisters[i].name))return resisters[i].number;
	}
	return -1;
}