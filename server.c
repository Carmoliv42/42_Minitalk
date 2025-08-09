#include "minitalk.h"

static void put_pid(int pid)
{
    char buf[12]; // suficiente para guardar um int e o '\0'
    int i = 10;

    buf[11] = '\0';
    if (pid == 0)
    {
        write(1, "0", 1);
        return;
    }
    while (pid > 0 && i >= 0)
    {
        buf[i--] = (pid % 10) + '0';
        pid /= 10;
    }
    write(1, &buf[i + 1], 10 - i);
}

static void handler(int sig, siginfo_t *info, void *context)
{
    //(void)info;
    (void)context;
    static unsigned char c = 0;
    static int bits = 0;
    //static pid_t client_pid = 0;
    static pid_t last_pid = 0;

    if (sig != SIGUSR1 && sig != SIGUSR2)
        return; // Ignora sinais não esperados
  if (last_pid != info->si_pid && bits == 0)
    {
        write(1, "\nMensagem cliente PID: ", 24);
        put_pid(info->si_pid);
        write(1, "\n", 1);
        last_pid = info->si_pid;
    }

    /*if (client_pid != info->si_pid)
    {
        client_pid = info->si_pid; // Atualiza PID do cliente
        bits = 0; // Reseta contagem de bits
        c = 0; // Reseta caractere acumulado
        ft_printf("Mensagem cliente PID: %d\n", client_pid); // Imprime novo PID
    }*/
    /* Acumula bit (MSB -> LSB): shift e seta LSB com o bit recebido */
    c <<= 1;
    if (sig == SIGUSR1)
        c |= 1; /* SIGUSR1 representa 1, SIGUSR2 representa 0 */

    bits++;
    if (bits == 8)
    {
        if (c == 0)
            write(1, "\n", 1); /* Se caractere nulo, imprime nova linha */
        else
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