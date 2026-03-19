Entendido. Com base em todas as nossas conversas e nas especificações técnicas do seu projeto **Hub de Controle Dual-Player** de alto nível, aqui está o **Esquemático Consolidado** final.

Este diagrama reflete a arquitetura final que definimos:

1. **Mestre:** Raspberry Pi Pico (RP2040).  
2. **Display:** TFT IPS Ultra-Wide (Bar Type) 2.25" com driver ST7789.  
3. **Rádios Bluetooth:** 2x ESP32 (WROOM/WROVER) independentes via I2C.  
4. **Inputs (Botões):** Shift Registers 74HC165 encadeados via SPI.  
5. **Inputs (Analógicos):** ADC Externo ADS1015 para Player 2 (via I2C) e leitura direta no RP2040 para Player 1\.  
6. **Gerenciamento de Energia:** Fonte 5V USB com Regulador 3.3V externo de 1A+ (padrão AMS1117-3.3).

## **Esquemático Elétrico Completo (Diagrama de Conexões)**

## **Mapa de Pinagem do RP2040 (Resumo Final)**

Esta é a tabela de referência que você usará para montar sua PCB ou protoboard:

| Grupo | Sinal | Pino Pico (GPIO) | Conecta em... | Notas |
| :---- | :---- | :---- | :---- | :---- |
| **I2C (Bus 0\)** | **SDA** | **GP4** (6) | SDA (ESP32 \#1, \#2, ADS1015) | Precisa de Pull-up 4.7kΩ |
|  | **SCL** | **GP5** (7) | SCL (ESP32 \#1, \#2, ADS1015) | Precisa de Pull-up 4.7kΩ |
| **Status/Rumble** | **IRQ P1** | **GP6** (9) | GPIO19 (ESP32 \#1) | Pulled-up internamente |
|  | **IRQ P2** | **GP7** (10) | GPIO19 (ESP32 \#2) | Pulled-up internamente |
| **Inputs (SPI1)** | **LATCH (PL)** | **GP13** (17) | Pino 1 (PL) de todos os 74HC165 |  |
|  | **SCK** | **GP10** (14) | Pino 2 (CP) de todos os 74HC165 |  |
|  | **MISO** | **GP12** (16) | Pino 9 (Q7) do *último* 74HC165 |  |
| **Display (SPI0)** | **SCK** | **GP18** (24) | SCK do Display ST7789 |  |
|  | **MOSI (SDA)** | **GP19** (25) | SDA/MOSI do Display ST7789 |  |
|  | **DC/RS** | **GP16** (21) | DC do Display ST7789 |  |
|  | **CS** | **GP17** (22) | CS do Display ST7789 |  |
|  | **RESET** | **GP20** (26) | Reset do Display ST7789 |  |
| **Analógicos P1** | **JOY\_X** | **GP26** (31) | X-Axis Potenciômetro P1 |  |
|  | **JOY\_Y** | **GP27** (32) | Y-Axis Potenciômetro P1 |  |
|  | **C\_X** | **GP28** (34) | C-Stick X-Axis P1 |  |
| **Menu** | **MENU\_BTNS** | **GP13-17** | 5 Botões de Navegação (Menu) | Configurado como INPUT\_PULLUP |
| **Alimentação** | **VCC 3.3V** | **3V3\_OUT** (36) | Saída do Regulador Externo | **NÃO USE O REGULADOR DO PICO\!** |
|  | **GND** | **GND** (3, 8, etc.) | Comum a todo o sistema |  |

## **Notas de Montagem e Próximos Passos**

1. **Regulador de Tensão:** Este é o ponto mais crítico do seu hardware. Os dois ESP32 transmitindo Bluetooth Classic e o backlight do display de 2.25" IPS consumirão picos de até **1A**. O regulador de 3.3V externo (tipo AMS1117-3.3) é **obrigatório**. Não tente alimentar pela porta USB do Pico.  
2. **I2C Pull-ups:** Não esqueça dos resistores de 4.7kΩ ligando o SDA e o SCL ao 3.3V. Sem eles, a comunicação com os ESP32s e o ADS1015 falhará.  
3. **Endereços I2C:**  
   * **ESP32 \#1:** Deve ser configurado via firmware (HOJA Baseband) para o endereço 0x50 (padrão).  
   * **ESP32 \#2:** Deve ser reconfigurado no firmware para o endereço 0x51.  
   * **ADS1015 (P2 Analógico):** Conecte o pino ADDR do módulo ao GND para fixar o endereço em 0x48.

**Este esquemático resume meses de desenvolvimento e todas as nossas discussões. Com ele, você tem tudo o que precisa para projetar sua PCB ou montar seu protótipo.**
