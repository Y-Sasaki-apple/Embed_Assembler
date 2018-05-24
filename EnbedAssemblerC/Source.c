/*
Easy Assembler
*/
#include<stdio.h>
#include<string.h>
#include"Header.h"
//switch (check_command(command)) {
//case Mov:
//case LD:
//case ST:
//case Add:
//case AdC:
//case Sub:
//case SbB:
//case And:
//case Or:
//case EOr:
//case Inc:
//case Dec:
//case Not:
//case Jmp:
//case JS:
//case JZ:
//case JC:
//case Halt:
//default:
//	break;
//}


unsigned char outdata[MAX_DATA] = { 0 };

void search_label(FILE * fp_read) {
	char line[MAX_LINE];

	int place = 0;
	while (fgets(line, sizeof(line), fp_read)) {
		char *next_token = NULL;
		char *token[4] = { NULL };
		char* command = { NULL };
		char* arg[2] = { NULL };
		int i = 0;
		token[i++] = strtok_s(line, " ", &next_token);
		if (token[0][0] == ';')continue;
		for (; i < 4 && (token[i] = strtok_s(NULL, " ", &next_token)); i++)if (token[i][0] == ';')break;
		if (strchr(token[0], ':') != '\0') {
			//ƒ‰ƒxƒ‹”­Œ©
			set_label(token[0], place);
			command = token[1];
			arg[0] = token[2];
			arg[1] = token[3];
		}
		else {
			command = token[0];
			arg[0] = token[1];
			arg[1] = token[2];
		}

		int cmdid = check_command(command);
		if (!commands[cmdid].isextra) {
			place += commands[cmdid].datan;
		}
		else {
			process_extra_commands(cmdid, arg[0], arg[1], outdata, &place);
		}
	}
}

void assemble(FILE * fp_read) {
	char line[MAX_LINE];
	char *token[4];
	char *next_token = NULL;
	int place = 0;
	while (fgets(line, sizeof(line), fp_read)) {
		char *next_token = NULL;
		char *token[4];
		char* command;
		char* arg[2];
		int i = 0;
		char output[2];
		token[i++] = strtok_s(line, " ", &next_token);
		for (; i < 4 && (token[i] = strtok_s(NULL, " ,", &next_token)); i++)if (token[i][0] == ';')break;
		if (token[0][0] == ';')continue;
		for (; i < 4; i++)token[i] = "";
		if (strchr(token[0], ':') != '\0') {
			//ƒ‰ƒxƒ‹”­Œ©
			token[0][strlen(token[0]) - 1] = '\0';
			set_label(token[0], place);
			command = token[1];
			arg[0] = token[2];
			arg[1] = token[3];
		}
		else {
			command = token[0];
			arg[0] = token[1];
			arg[1] = token[2];
		}
		int cmdid = check_command(command);
		if (!commands[cmdid].isextra) {
			commands[cmdid].func(arg[0], arg[1], output);
			for (int i = 0; i < commands[cmdid].datan; i++) {
				outdata[place + i] = output[i];
			}
			place += commands[cmdid].datan;
		}
		else {
			process_extra_commands(cmdid, arg[0], arg[1], outdata, &place);
		}
	}
}

void outputfile(FILE* fp_write) {
	for (int i = 0; i < MAX_DATA; i++) {
		if (outdata[i] == '\0')continue;
		char temp[100];
		unsigned char checksum = 0;
		//fputc(outdata[i], fp_write);
		fputc(':', fp_write);

		sprintf_s(temp, sizeof(temp), "%02hhX", 16); fputs(temp, fp_write); checksum += 16;

		sprintf_s(temp, sizeof(temp), "%04X", i); fputs(temp, fp_write); checksum += i;

		fputs("00", fp_write);

		for (int j = 0; j < 16; j++) {
			sprintf_s(temp, sizeof(temp), "%02hhX", outdata[i + j]); fputs(temp, fp_write);
			checksum += outdata[i + j];
		}
		i += 16 - 1;
		sprintf_s(temp, sizeof(temp), "%02hhX", -checksum); fputs(temp, fp_write);
		fputc('\r', fp_write);
		fputc('\n', fp_write);
	}
	fputs(":00000001FF\r\n", fp_write);
}

int main(int argc, char* argv[]) {
	FILE *fp_read, *fp_write;

	init();
	if (argc > 1) {
		fopen_s(&fp_read, argv[1], "r");
		fopen_s(&fp_write, argv[2], "w");
	}
	else {
		fopen_s(&fp_read, "test", "r");
		fopen_s(&fp_write, "test.txt", "w");
	}
	search_label(fp_read);
	rewind(fp_read);
	assemble(fp_read);
	outputfile(fp_write);

}
