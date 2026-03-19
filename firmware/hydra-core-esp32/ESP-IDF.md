# ESP-IDF

> Tentando aprender

***

## Preparar o Sistema (Dependencies)

O MacOS precisa de algumas ferramentas de compilação básicas. Abra o Terminal e instale via Homebrew:

```sh
brew install cmake ninja dfu-util python3
```

### Instalar o ESP-IDF (Framework da Espressif)

O HOJA exige o framework oficial. Recomendo a versão estável mais recente (v5.x):

```sh
# Crie um diretório para o SDK
mkdir -p ~/esp
cd ~/esp

# Clone o repositório do framework
git clone --recursive https://github.com/espressif/esp-idf.git

# Instale as ferramentas para o chip ESP32
cd esp-idf
./install.sh esp32
```

### Configurar Variáveis de Ambiente

Toda vez que você abrir um novo terminal para compilar, precisará "ativar" o ambiente.
Adicione essa linha ao seu ~/.zshrc para não precisar digitar sempre

```sh
alias get_idf=". $HOME/esp/esp-idf/export.sh"
```

## Clonando o REPO do jeito certo

Clonando REPO recursivo:

```bash
git  clone  --recursive https://github.com/xxx/xxx.git
```

Clonando tudo mesmo:

```shell
git  submodule update --init  --recursive
```

## Iniciando o ESP-IDF

Ative o ambiente

```sh
get_idf
```

### Configurar o Hardware

O HOJA usa um sistema de menu para definir os pinos e o tipo de controle:

```sh
idf.py menuconfig
```

Navegue até as opções do HOJA Configuration. É aqui que você define se ele vai se comportar como Switch, X-Input, etc., e mapeia os GPIOs dos botões do seu Arcade.

### Compilar

```sh
idf.py build
```

*Isso vai gerar os arquivos binários e a tabela de partições na pasta `/build`.*

## Gravar no Chip

### Listar Portas Seriais (Para o ESP32)

Identifique a porta USB (geralmente `/dev/cu.usbserial-X`)

Este é o comando que você usará 99% das vezes com o ESP-IDF. Ele mostra o "caminho" que você deve passar para o `idf.py -p`.

```sh
ls /dev/cu.*
```

### O que procurar no resultado

>Se o seu ESP32 usa o chip CP210x, aparecerá algo como: `/dev/cu.usbserial-1410`
>
>Se usa o chip CH340, aparecerá algo como: `/dev/cu.wchusbserial-1410`
>
>Se for um ESP32-S3 com USB nativo, pode aparecer como: `/dev/cu.usbmodem...`

### Gravando

```sh
idf.py -p /dev/cu.usbserial-LIST_SUA_PORTA flash monitor
```

*(O comando `monitor` abre o log em tempo real para você ver o controle iniciando).*

***
***
***

![Prototype](https://qwkrhmrswlcdizqyajwo.supabase.co/storage/v1/object/public/images/e42f1210-ef2e-4722-aa25-abe56a6b5daa/1bd11580-fd0e-458d-8530-12a0907a19c0.jpeg)
