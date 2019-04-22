Programar "Intrepretador" que executa instruções de um ficheiro de texto.

As variáveis "var" são do tipo Int ou Char.

Leitura: ler(var);

Escrita: escrever(var);

Atribuição: var = número; var = character;

Aritmétricas:
Soma: "var = var + var;"
Subtração: "var = var - var;"
Multiplicação: "var = var * var;"
Divisao: "var = var / var;" (sensível a números negativos)

If: "if var goto Label;"
Goto: "goto Label;"
Label: "label Label;" 

Terminar o programa: "quit;"

Sensível a linhas em branco (erro de Segmentation Fault). O programa acaba com uma instrução "quit;" ou quando não existe mais instruções.

Feito para funcionar com o seguinte exemplo:
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
