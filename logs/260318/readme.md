# **twinStick**

Aqui está o resumo técnico consolidado para o seu guia de desenvolvimento:

## **1\. Arquitetura de Software (Repositórios)**

* **Mestre (RP2040):** Use o [**HOJA-LIB-RP2040**](https://github.com/HandHeldLegend/HOJA-LIB-RP2040). Ele gerenciará a lógica dos Shift Registers, o display OLED, o menu de navegação e a máquina de estados dos modos (Switch, XInput, etc.).  
* **Rádios (ESP32):** Use o [**HOJA-ESP32-Baseband**](https://github.com/HandHeldLegend/HOJA-ESP32-Baseband). Este firmware transforma o ESP32 em um "escravo" que obedece às ordens do Pico via I2C, lidando com a pilha pesada do Bluetooth Classic do Switch.

## **2\. Fluxo de Comunicação Bidirecional**

Para que o seu Pico saiba o status do Bluetooth (ex: "Conectado", "Vibrando"), a comunicação seguirá este padrão:

1. **Pico \-\> ESP32 (Escrita I2C):** Envia o pacote de botões/analógicos e comandos de troca de modo.  
2. **ESP32 \-\> Pico (Leitura I2C):** O Pico solicita um "report" de status. O ESP32 responde com dados de conexão e comandos de **Rumble** (vibração) vindos do console.  
3. **Pino IRQ (Interrupção):** Fundamental no seu caso. Quando o Switch manda o controle vibrar, o ESP32 puxa um pino de interrupção para o nível baixo, avisando o Pico: *"Ei, tenho uma atualização de status, me leia agora\!"*.

## **3\. Configuração para 2 Players e Multi-Modos**

* **Endereçamento I2C:** Você precisará definir endereços diferentes no firmware baseband de cada ESP32 (ex: 0x50 para Player 1 e 0x51 para Player 2).  
* **Troca de Modos:** No menu do seu display (gerido pelo Pico), ao selecionar "XInput", o Pico enviará um comando I2C específico que reinicia o rádio do ESP32 naquele perfil.

## **4\. Hardware e Shift Registers**

Como você usará Shift Registers (74HC165) para os inputs, o **PIO (Programmable I/O)** do RP2040 é sua arma secreta. Ele pode ler todos esses botões em microssegundos sem sobrecarregar a CPU que está cuidando do display.

---

**Qual o próximo passo que você deseja atacar?**

1. **Esquema Elétrico:** Quer ajuda para definir os pinos de SDA/SCL, IRQ e a conexão dos Shift Registers no Pico?  
2. **Estrutura de Código:** Quer que eu detalhe como seria a struct de dados para enviar os inputs do Player 2 via I2C?