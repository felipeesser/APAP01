# APAP01
Comparação entre algoritmos  

para gerar os registros das listas formadas basta compilar e executar os arquivos "selection.c" e "bubble.c": 

-----------------------------

gcc selection.c -o selection  
./selection  
gcc bubble.c -o bubble  
./bubble  

-----------------------------

Os arquivos contidos nas pastas "arquivosbubble" e "arquivosselection" do repositório correspondem, respectivamente, ao registro das listas geradas para os algoritmos bubble sort e selection sort com tamanho variando de 1000 a 25000, tamanho de passo igual a 100, e valores sorteados entre 0 a 2000 ou 0 a n².  
Os gráficos foram gerados com base nos arquivos contidos na pasta "geradoresGraficos" e estão localizados na pasta "graficos".  
Para gerar os gráficos a ferramenta gnuplot foi utilizada com os seguintes comandos:  

-----------------------------

plot "heapSort.dat" with lines,"metCaixas.dat" with lines,"selectionTime" with lines,"bubbleTime" with lines  

plot "heapSort.dat" with lines,"metCaixas.dat" with lines,"selectionTime" with lines,"bubbleTime" with 
lines,"heapSortTipo2.dat" with lines,"metCaixasTipo2.dat" with lines,"selectionTime2" with lines,"bubbleTime2" with lines

plot "heapSort.dat" with lines,"selectionTime" with lines,"bubbleTime" with lines  

plot "heapSort.dat" with lines,"metCaixasTipo2.dat" with lines,"selectionTime" with lines,"bubbleTime" with lines

plot "heapSort.dat" with lines,"metCaixas.dat" with lines   

plot "selectionTime" with lines,"bubbleTime" with lines  

plot "selectionTime" with lines,"selectionTime2" with lines

plot "bubbleTime" with lines,"bubbleTime2" with lines

plot "heapSort.dat" with lines,"metCaixas.dat" with lines

plot "heapSort.dat" with lines,"heapSortTipo2.dat" with lines

plot "metCaixas.dat" with lines,"metCaixasTipo2.dat" with lines

plot "heapSort.dat" with lines,"metCaixasTipo2.dat" with lines

