
## Instruções para execução do projeto.

### Pré-requisitos
O projeto foi desenvolvido em sistema operacional UNIX Ubuntu 20.04, portanto, é altamente recomendado que este seja 
executado em plataformas similares. O único pré requisito para a execução do projeto é a instalação do compilador GCC. 
Para verificar se sua máquina possui o GCC instalado, execute o seguinte comando:
```
gcc --version
```
o resultado deve ser:
```
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
Caso seu sistema operacional não reconheça o comando, instale o GCC e tente novamente.

**Versão do GCC utilizado para desenvolvimento do projeto: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0**


### Executando o projeto
**Passo 1:** entre no diretório do projeto via terminal e conceda permissão de execução para o arquivo run.sh por meio do seguinte comando:
```
$ chmod +x run.sh
```

**Passo 2:** em seguida, execute o script de execução por meio do comando:
```
$ ./run.sh
```
O resultado será escrito no arquivo lidos.dat.