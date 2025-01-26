all:
	gcc -o main main.c CasamentoExato/BMSH.c CasamentoExato/KMP.c Criptografia/cifra.c
	./main