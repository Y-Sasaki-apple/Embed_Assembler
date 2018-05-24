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
char errmsg[MAX_DATA] = "";
int error = 0;
int linerror[MAX_LINE] = { 0 };
void search_label(FILE * fp_read) {
	char line[MAX_LINE];
	int linen = 0;
	int place = 0;
	while (linen++, fgets(line, sizeof(line), fp_read)) {
		error = 0;
		char *next_token = NULL;
		char *token[4] = { NULL };
		char* command = { NULL };
		char* arg[2] = { NULL };
		int argn = 0;
		int i = 0;
		token[i++] = strtok_s(line, " \n", &next_token);
		if (!token[0] || token[0][0] == ';')continue;
		for (; i < 4 && (token[i] = strtok_s(NULL, " ,\n", &next_token)); i++)if (token[i][0] == ';')break;
		argn = i - 1;
		if (strchr(token[0], ':') != '\0') {
			//ラベル発見
			set_label(token[0], place);
			command = token[1];
			arg[0] = token[2];
			arg[1] = token[3];
			argn--;
		}
		else {
			command = token[0];
			arg[0] = token[1];
			arg[1] = token[2];
		}

		int cmdid = check_command(command);

		//check_command error
		if (error != 0) {
			printf_s("Line:%d \t%s", linen, errmsg); 
			linerror[linen] = 1; 
			continue;
		}
		//Aug Error
		if (commands[cmdid].argn != argn) {
			printf_s("Line:%d \tコマンド%sの引数の数は%dですが、%d個の引数が与えられました。", linen, commands[cmdid].name, commands[cmdid].argn, argn);
			linerror[linen] = 1;
			continue;
		}

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
	int linen = 0;
	int place = 0;
	while (linen++,fgets(line, sizeof(line), fp_read)) {
		if (linerror[linen])continue;
		char *next_token = NULL;
		char *token[4];
		char* command;
		char* arg[2];
		int i = 0;
		char output[2];
		token[i++] = strtok_s(line, " \n", &next_token);
		for (; i < 4 && (token[i] = strtok_s(NULL, " ,\n", &next_token)); i++)if (token[i][0] == ';')break;
		if (!token[0] || token[0][0] == ';')continue;
		for (; i < 4; i++)token[i] = "";
		if (strchr(token[0], ':') != '\0') {
			//ラベル発見
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
			//commandfunc error
			if (error != 0) {
				printf_s("Line:%d \t%s", linen, errmsg);
				linerror[linen] = 1;
				place += commands[cmdid].datan;
				continue;
			}
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
