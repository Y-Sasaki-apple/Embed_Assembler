#pragma once
#include"Commands.h"
#include"Register.h"
#include"Label.h"
#define MAX_DATA 3000
#define MAX_LINE 200

char output[MAX_DATA] = { 0 };

void init() {
	init_resisters();
	init_commands();
}