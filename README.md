# BM32OS

Operational System designed using the language cminus for the BM_CORE architecture as the final project for the Laboratory of Operational Systems lecture.

## Directory organization

**SYSTEM_CODE** contains the OS files, which includes it's source code and the respective bios code for the system.

**PROGRAM_FILES** contains the programs used as processes during process scheduling.

## Notes

For better **BM32OS** understanding, it's worth checking the architecture that supports it here, which is by itself a whole other project.

Some of the process files use different system calls since they support UART communication.

The format used on this project is actually '.cminus', '.c' extension is used here only for better highlighting.
