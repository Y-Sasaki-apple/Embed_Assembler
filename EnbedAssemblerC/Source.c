/*
Easy Assembler
*/
#include<stdio.h>
#include<string.h>
#include"Header.h"

void set_label(const char* name, int place) {

}
void set_label_place(const char* name, int place) {

}

void search_label(FILE* fp_read) {
	char line[MAX_LINE];
	char *token[4];
	char *next_token = NULL;
	int place = 0;
	while (fgets(line, sizeof(line), fp_read)) {
		char* command;
		char* arg[2];
		int i = 0;
		for (; token[i] = strtok_s(line, " ", &next_token); i++);
		for (; i < 4; i++)token[i] = "";
		if (strchr(token[0], ':') != '\0') {
			token[0][strlen(token[0]) - 1] = '\0';
			set_label(token[0], place);
			command = token[1];
			arg[0] = token[2];
			arg[1] = token[3];
		} else {
			command = token[0];
			arg[0] = token[1];
			arg[1] = token[2];
		}
		
		switch (check_command(command)){
		case Mov:
		case LD:
		case ST:
		case Add:
		case AdC:
		case Sub:
		case SbB:
		case And:
		case Or:
		case EOr:
		case Inc:
		case Dec:
		case Not:
		case Jmp:
		case JS:
		case JZ:
		case JC:
		case Halt:
		default:
			break;
		}

	}


}

int main(int argc, char* argv[]) {
	FILE *fp_read, *fp_write;
	fp_read = fopen_s(&fp_read, argv[1], "r");
	fp_write = fopen_s(&fp_write, argv[2], "wb");

}
