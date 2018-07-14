#ifndef STACK_CLASS_H
# define STACK_CLASS_H

# include <iostream>
# include <vector>

typedef int32_t	i32;

class	StackVM {
	private:
	std::vector<i32>	memory;
	i32	 				pc;			// program counter
	i32					sp;			// Stack pointer
	i32					type;
	i32					data;
	i32					running;

	i32					getType(i32 instruction);
	i32					getData(i32 instruction);
	void				fetch();
	void				decode();
	void				execute();
	void				doPrimitive();

	public:
	StackVM(void);
	~StackVM(void);
	void				run();
	void				loadProgram(std::vector<i32> prog);

};

#endif
