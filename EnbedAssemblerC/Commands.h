#pragma once
#include<string.h>
#include"Header.h"
#include"Register.h"
#include"Label.h"
#define COMMAND_NUM 18
enum CommandNum {
	Mov = 0, LD, ST, Add, AdC, Sub, SbB, And, Or, EOr, Inc, Dec, Not, Jmp, JS, JZ, JC, Halt
};
char* CommandNames[COMMAND_NUM] = {
	"MOV","LD","ST","ADD","ADC","SUB","SBB","AND","OR","EOR","INC","DEC","NOT","JMP","JS","JZ","JC","HALT"
};
struct Command {
	char* name;
	enum CommandNum number;
	int argn;
	int datan;
	int(*func)(const char* arg1, const char* arg2, char* output);
};
struct Command commands[COMMAND_NUM];

int check_command(const char* command) {
	for (int i = 0; i < COMMAND_NUM; i++) {
		if (strcmp(command, commands[i].name))return commands[i].number;
	}
	return -1;
}

int mov(const char* arg1, const char* arg2,char* output) {
	int r1 = check_resister(arg1);
	int r2 = check_resister(arg1);
	output[0] = 0b000 << 5 | r1 << 2 | r2;
	return 1;
}
int ld(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	int r2 = get_label(arg1);
	output[0] = 0b100 << 5 | r1;
	output[1] = r2;
	return 1;
}
int st(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	int r2 = get_label(arg1);
	output[0] = 0b101 << 5 | r1 << 2;
	output[1] = r2;
	return 1;
}
int add(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b001000 << 2 | r1;
	return 1;
}
int adc(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b001001 << 2 | r1;
	return 1;
}
int sub(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b001010 << 2 | r1;
	return 1;
}
int sbb(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b001011 << 2 | r1;
	return 1;
}
int and(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b001100 << 2 | r1;
	return 1;
}
int or(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b001101 << 2 | r1;
	return 1;
}
int eor(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b001111 << 2 | r1;
	return 1;
}
int inc(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b010000 << 2 | r1;
	return 1;
}
int dec(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b010001 << 2 | r1;
	return 1;
}
int not(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	output[0] = 0b010100 << 2 | r1;
	return 1;
}
int jmp(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	int r2 = get_label(arg1);
	output[0] = 0b11000000;
	output[1] = r2;
	return 1;
}
int js (const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	int r2 = get_label(arg1);
	output[0] = 0b11110000;
	output[1] = r2;
	return 1;
}
int jz(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	int r2 = get_label(arg1);
	output[0] = 0b11101000;
	output[1] = r2;
	return 1;
}
int jc(const char* arg1, const char* arg2, char* output) {
	int r1 = check_resister(arg1);
	int r2 = get_label(arg1);
	output[0] = 0b11100100;
	output[1] = r2;
	return 1;
}
int halt(const char* arg1, const char* arg2, char* output) {
	output[0] = 0b11111111;
	return 1;
}
void init_command(int i, const char *name, enum CommandNum number, int argn, int datan, int(*func)(const char* arg1, const char* arg2, char* output)) {
	strcpy_s(commands[i].name,sizeof(commands[i].name),name);
	commands[i].number = number;
	commands[i].argn = argn;
	commands[i].datan = datan;
	commands[i].func = func;
}
void init_commands() {
	init_command(0, "Mov", Mov, 2, 1, mov);
	init_command(1, "Ld", LD, 2, 2, ld);
	init_command(2, "St", ST, 2, 2, st);
	init_command(3, "Add", Add, 1, 1, add);
	init_command(4, "Adc", AdC, 1, 1, adc);
	init_command(5, "Sub", Sub, 1, 1, sub);
	init_command(6, "SbB", SbB, 1, 1, sbb);
	init_command(7, "And", And, 1, 1, and);
	init_command(8, "Or", Or, 1, 1, or);
	init_command(9, "Eor", EOr, 1, 1, eor);
	init_command(10, "Inc", Inc, 1, 1, inc);
	init_command(11, "Dec", Dec, 1, 1, dec);
	init_command(12, "Not", Not, 1, 1, not);
	init_command(13, "Jmp", Jmp, 1, 2, jmp);
	init_command(14, "Js", JS, 1, 2, js);
	init_command(15, "Jz", JZ, 1, 2, jz);
	init_command(16, "Jc", JC, 1, 2, jc);
	init_command(17, "Halt", Halt, 1, 2, halt);
}