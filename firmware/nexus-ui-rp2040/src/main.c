#include "pico/stdlib.h"
#include "board_config.h"
#include "hoja.h"

// Se o hoja_task não está no hoja.h, ele pode estar aqui:
#include "utilities/hooks.h" 

int main() {
    stdio_init_all();

    // Esta função está no seu hoja.h (linha 35)
    hoja_init();

    while (true) {
        // Tente comentar a linha abaixo se o erro persistir 
        // apenas para ver se o resto compila.
        // hoja_task(); 
        
        // No motor HOJA, muitas vezes o processamento é via interrupção.
        // Se não houver hoja_task, o hoja_init já configura os timers.
        sleep_ms(1);
    }
}