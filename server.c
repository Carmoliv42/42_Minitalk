#include "minitalk.h"

static void handler(int sig, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    static unsigned char c = 0;
    static int bits = 0;

    /* Acumula bit (MSB -> LSB): shift e seta LSB com o bit recebido */
    c <<= 1;
    if (sig == SIGUSR1)
        c |= 1; /* SIGUSR1 representa 1, SIGUSR2 representa 0 */

    bits++;
    if (bits == 8)
    {
        /* Escreve o caractere completo */
        write(1, &c, 1);
        /* Reseta para o próximo byte */
        bits = 0;
        c = 0;
    }
}

int main(void)
{
    struct sigaction sa;

    /* Imprime PID com ft_printf (fora do handler é seguro) */
    ft_printf("Server PID: %d\n", getpid());

    /* Zera estrutura e configura */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction SIGUSR1");
        return (1);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("sigaction SIGUSR2");
        return (1);
    }

    /* Espera por sinais */
    while (1)
        pause();

    return (0);
}