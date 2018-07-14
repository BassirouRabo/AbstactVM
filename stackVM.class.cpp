#include "stackVM.class.h"

/*
 * Instruction format
 * header: 2 bits
 * data: 30 bits
 *
 * header format
 * 0 => positive integer
 * 1 => negative integer
 * 3 => undefined
 * */

StackVM::StackVM(void): pc(100), sp(0), type(0), data(0), running(1)
{
	this->memory.reserve(1000000);
}

StackVM::~StackVM(void){}

i32 StackVM::getType(i32 instruction)
{
	i32 type = 0xc0000000;
	type = (type & instruction) >> 30;
	return (type);
}

i32 StackVM::getData(i32 instruction)
{
	i32 data	= 0x3fffffff;
	data = data & instruction;
	return (data);
}

void	StackVM::fetch()
{
	this->pc++;
}

void	StackVM::decode()
{
	this->type = StackVM::getType(memory[pc]);
	this->data = StackVM::getData(memory[pc]);
}

void	StackVM::execute()
{
	if (type == 0 || type == 2)
	{
		this->sp++;
		this->memory[sp] = this->data;
	}
	else
		StackVM::doPrimitive();
}

void	StackVM::doPrimitive()
{
	switch (this->data)
	{
		case 0:	// halt
			std::cout << "Halt" << std::endl;
			this->running = 0;
			break;
		case 1:	// add
			std::cout << "add " << this->memory[sp - 1] << " " << this->memory[sp] << std::endl;
			this->memory[sp -1] = this->memory[sp - 1] + this->memory[sp];
			this->sp--;
			break;
	}
}

void	StackVM::run(void)
{
	pc -= 1;
	while (this->running == 1)
	{
		StackVM::fetch();
		StackVM::decode();
		StackVM::execute();
		std::cout << "tos: " << this->memory[sp] << std::endl;
	}
}

void	StackVM::loadProgram(std::vector<i32> prog)
{
	for (i32 i = 0; i < prog.size(); i++)
		this->memory[this->pc + i] = prog[i];
}


