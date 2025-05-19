Projeto de P.I. desenvolvido durante o 3º semestre do curso de Big Data no Agronegócio.
Este produto utiliza dois módulos LoRa, sendo um configurado como transmissor de dados e o outro como receptor. 
O módulo transmissor está integrado a dois sensores: o DHT11, responsável por captar a temperatura e a umidade do ar, e o sensor LDR, que mede a luminosidade.

O objetivo da combinação desses sensores é possibilitar a comunicação dos dados do transmissor para o receptor via rádio, o qual o LoRa trabalha. Para exibir essas informações captadas, foi criada uma página web utilizando HTML, CSS e JavaScript. 
A atualização dos dados na página é feita por meio da Fetch API do JavaScript, onde os dados capturados são convertidos para arquivo JSON e a API Fetch, consume esses arquivos lendo e enviando para as tags HTML, assim atualizando os dados da página em tempo real.
