kilo: kilo.c 
	$(CC) kilo.c -o kilo -Wall -Wextra -pedantic -std=c99

# 1. We are declaring that we want to build 'kilo' binary from 'kilo.c'.
# 2. We are declaring the build command through the follwoing statements:
#		- $(CC) is a variable that make expands automatically to 'cc'.
#		- 'Wall' stands for “all Warnings”, and gets the compiler to warn you when it sees code in your program that might not technically be wrong, but is considered bad or questionable usage of the C language.
#		- 'Wextra' and 'pedantic' turn on even more warnings.
#		- 'std=c99' specifies the exact version of the C language standard we’re using.

# This can be launched by writting 'make' in the terminal on the same folder. Is worth to mention that: It may output make: `kilo' is up to date.. It can tell that the current version of kilo.c has already been compiled by looking at each file’s last-modified timestamp. If kilo was last modified after kilo.c was last modified, then make assumes that kilo.c has already been compiled, and so it doesn’t bother running the compilation command. If kilo.c was last modified after kilo was, then make recompiles kilo.c