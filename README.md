# LC-3 Virtual Machine

## Overview
This project is a virtual machine (VM) implementation for the LC-3 (Little Computer 3) computer, a simple educational computer architecture. The LC-3 VM simulates the behavior of an LC-3 computer, enabling users to load and execute LC-3 machine code programs.

The LC-3 architecture is designed to teach computer science concepts such as assembly language programming, computer architecture, and systems programming. It features a simplified instruction set, making it an ideal platform for educational purposes.

---

## Features
- **Full LC-3 Instruction Set**: Implements all 16 opcodes of the LC-3 instruction set.
- **Memory Simulation**: 16-bit addressable memory space (65,536 locations).
- **Register Simulation**: Includes all eight general-purpose registers (R0–R7), a program counter (PC), and condition flags (N, Z, P).
- **Trap Routine Support**: Supports built-in trap routines like input, output, and halting.
- **Interrupt Handling**: Handles memory-mapped I/O.
- **Input/Output**: Simulates basic keyboard input and screen output.

---

## Requirements
- A C compiler (GCC, Clang, or MSVC).
- Standard C library support.
- A terminal for running and interacting with the virtual machine.

---

## Getting Started


### Build the Project
1. Create a local directory to host the project files.
2. clone the project from Github.
  ```bash
  git clone https://github.com/Nickodhiambo/Virtual-Machine.git
  ```
3. Compile the source code:
   ```bash
   gcc lc3.c -o lc3-vm
   ```

### Run the Virtual Machine
Load an LC-3 program file (e.g., `program.obj`):
```bash
./lc3-vm program.obj
```

---

## How It Works
The LC-3 VM emulates the LC-3 architecture as follows:

### Memory
- The VM simulates 65,536 16-bit memory locations.
- Memory-mapped I/O locations:
  - `0xFE00`: Keyboard status register.
  - `0xFE02`: Keyboard data register.

### Registers
- **General-purpose registers**: R0–R7.
- **Program Counter (PC)**: Points to the next instruction to execute.
- **Condition Flags**:
  - **N**: Negative.
  - **Z**: Zero.
  - **P**: Positive.

### Instruction Execution
The VM fetches, decodes, and executes instructions:
1. Fetch: Read the instruction from memory at the address pointed to by the PC.
2. Decode: Determine the instruction opcode and operands.
3. Execute: Perform the operation and update the machine state.

### Trap Routines
- **GETC (0x20)**: Read a single character from the keyboard.
- **OUT (0x21)**: Output a single character to the screen.
- **PUTS (0x22)**: Output a null-terminated string to the screen.
- **HALT (0x25)**: Halt the program.

---

## LC-3 Opcodes
Below is a summary of supported opcodes:

| Opcode | Instruction    | Description                                |
|--------|----------------|--------------------------------------------|
| 0x1    | ADD            | Add two registers or a register and a constant |
| 0x5    | AND            | Bitwise AND                                |
| 0xF    | TRAP           | Execute a system call                     |
| ...    | Others         | Refer to LC-3 ISA documentation for details |

---

## Example Usage
1. Write an LC-3 assembly program (`example.asm`):
   ```asm
   .ORIG x3000
   LEA R0, HELLO
   PUTS
   HALT
   HELLO .STRINGZ "Hello, World!"
   .END
   ```

2. Assemble the program using an LC-3 assembler to produce an object file (`example.obj`).
3. Load and run the object file in the VM:
   ```bash
   ./lc3-vm example.obj
   ```
   Output:
   ```
   Hello, World!
   ```

---

## Development Notes
- **Extensibility**: The VM is modular; additional features like debugging tools can be implemented by extending the existing framework.
- **Error Handling**: The VM includes basic error handling for invalid instructions and memory access violations.
- **Testing**: Use provided LC-3 test programs to verify functionality.

---

## Contributing
Contributions are welcome! Please:
1. Fork the repository.
2. Create a feature branch.
3. Submit a pull request with a detailed description.

---

## Resources
- [LC-3 ISA Documentation](https://people.cs.pitt.edu/~jmisurda/teaching/cs447/notes/lc3arch.pdf)
- [Introduction to LC-3 Assembly Programming](https://link_to_resource)

---

## License
This project is licensed under the MIT License. See the LICENSE file for details.

---

## Contact
For questions or feedback, please reach out to nodhiambo01@gmail.com.

