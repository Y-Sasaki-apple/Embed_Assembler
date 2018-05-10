#pragma once
#include<string.h>
#include"Header.h"
int mov(const char* arg1, const char* arg2,char* output) {
	int r1 = check_resister(arg1);
	int r2 = check_resister(arg1);
	output[0] = 0b000 << 5 | r1 << 2 | r2;
	return 1;
}
void init_command(int i, const char *name, enum CommandNum number, int argn, int datan, int(*func)(const char* arg1, const char* arg2, char* output)) {
	strcpy(commands[i].name,name);
	commands[i].number = number;
	commands[i].argn = argn;
	commands[i].datan = datan;
	commands[i].func = func;
}
void init_commands() {
	init_command(0, "Mov", Mov, 2, 1, mov);
}