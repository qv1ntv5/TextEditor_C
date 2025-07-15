#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void print_binary(unsigned int value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

void print_termios_flags(struct termios *raw) {
    printf("=== TERMIOS STRUCTURE ANALYSIS ===\n");
    printf("c_iflag: %u (0x%x)\n", raw->c_iflag, raw->c_iflag);
    printf("c_oflag: %u (0x%x)\n", raw->c_oflag, raw->c_oflag);
    printf("c_cflag: %u (0x%x)\n", raw->c_cflag, raw->c_cflag);
    printf("c_lflag: %u (0x%x)\n", raw->c_lflag, raw->c_lflag);
    
    printf("\n=== c_lflag DETAILED ANALYSIS ===\n");
    printf("c_lflag value: %u\n", raw->c_lflag);
    printf("c_lflag binary: ");
    print_binary(raw->c_lflag, 16);
    printf("\n");
    
    printf("\n=== INDIVIDUAL FLAGS IN c_lflag ===\n");
    printf("ECHO flag value: %u (0x%x)\n", ECHO, ECHO);
    printf("ECHO binary:     ");
    print_binary(ECHO, 16);
    printf("\n");
    
    printf("ICANON flag value: %u (0x%x)\n", ICANON, ICANON);
    printf("ICANON binary:     ");
    print_binary(ICANON, 16);
    printf("\n");
    
    printf("ISIG flag value: %u (0x%x)\n", ISIG, ISIG);
    printf("ISIG binary:       ");
    print_binary(ISIG, 16);
    printf("\n");
    
    printf("\n=== FLAG STATUS ===\n");
    printf("ECHO is %s\n", (raw->c_lflag & ECHO) ? "ON" : "OFF");
    printf("ICANON is %s\n", (raw->c_lflag & ICANON) ? "ON" : "OFF");
    printf("ISIG is %s\n", (raw->c_lflag & ISIG) ? "ON" : "OFF");
}

int main() {
    struct termios original, modified;
    
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &original);
    
    printf("ORIGINAL TERMINAL SETTINGS:\n");
    print_termios_flags(&original);
    
    // Make a copy to modify
    modified = original;
    
    printf("\n\n=== BITWISE OPERATION DEMONSTRATION ===\n");
    printf("We want to turn OFF the ECHO flag using: c_lflag &= ~(ECHO)\n\n");
    
    printf("Step 1: Original c_lflag\n");
    printf("c_lflag:     ");
    print_binary(modified.c_lflag, 16);
    printf(" (%u)\n", modified.c_lflag);
    
    printf("\nStep 2: ECHO flag\n");
    printf("ECHO:        ");
    print_binary(ECHO, 16);
    printf(" (%u)\n", ECHO);
    
    printf("\nStep 3: ~(ECHO) - bitwise NOT of ECHO\n");
    printf("~(ECHO):     ");
    print_binary(~ECHO, 16);
    printf(" (%u)\n", (unsigned short)~ECHO);
    
    printf("\nStep 4: c_lflag & ~(ECHO) - AND operation\n");
    unsigned int result = modified.c_lflag & ~ECHO;
    printf("Result:      ");
    print_binary(result, 16);
    printf(" (%u)\n", result);
    
    // Actually perform the operation
    modified.c_lflag &= ~(ECHO);
    
    printf("\nMODIFIED TERMINAL SETTINGS (ECHO turned OFF):\n");
    print_termios_flags(&modified);
    
    printf("\n\n=== TURNING ECHO BACK ON ===\n");
    printf("To turn ECHO back ON, we use: c_lflag |= ECHO\n");
    
    printf("Current c_lflag: ");
    print_binary(modified.c_lflag, 16);
    printf(" (%u)\n", modified.c_lflag);
    
    printf("ECHO flag:       ");
    print_binary(ECHO, 16);
    printf(" (%u)\n", ECHO);
    
    modified.c_lflag |= ECHO;
    
    printf("After OR:        ");
    print_binary(modified.c_lflag, 16);
    printf(" (%u)\n", modified.c_lflag);
    
    printf("\nFINAL RESULT (ECHO turned back ON):\n");
    printf("ECHO is %s\n", (modified.c_lflag & ECHO) ? "ON" : "OFF");
    
    return 0;
}