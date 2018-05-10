#pragma once
#define MAX_DATA 3000
#define LABELNAME_MAX 300
#define MAX_LABEL 30
#define MAX_LABEL_IN_CODE 300
#define MAX_LINE 200
#define COMMAND_NUM 18
char output[MAX_DATA] = { 0 };
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



enum ResisterNum {
	A=0b01,B=0b10,C=0b11
};
char* ResisterNames[]={
	"A","B","C"
};
struct Resister{
	char* name;
	enum ResisterNum number;
};
struct Resister resisters[3];
void init_resisters() {
	for (int i = 0; i < 3; i++) {
		resisters[i].name = CommandNames[i];
		resisters[i].number = i+1;
	}
}

int check_command(const char* command) {
	for (int i = 0; i < COMMAND_NUM; i++) {
		if (strcmp(command, commands[i].name))return commands[i].number;
	}
	return -1;
}
int check_resister(const char* resister) {
	for (int i = 0; i < 3; i++) {
		if (strcmp(resister, resisters[i].name))return commands[i].number;
	}
	return -1;
}