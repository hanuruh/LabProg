Programa quase completo.
Por algum motivo ou uma mudança que foi feita provavelmente na hashtable recebo sempre erro de segmentation fault.

Não é sensivel a espaçamento. O programa acaba com uma instrução "quit;" ou quando não existe mais instruções.

Feito para funcionar com o seguinta exemplo:
ler(k);
p= 6 + k;
if p goto L1;
p = p/2;
escrever(p);
goto L2;
label L1;
p = 2*p;
escrever(p);
label L2;
quit;

Para executar $./main file.txt

Trabalho feito por:
Ana Moreira - 201704728
