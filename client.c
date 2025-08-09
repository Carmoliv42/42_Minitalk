#include <unistd.h>
#include "minitalk.h"

static void send_char(int pid, unsigned char c)
{
    int i = 7;
    while (i >= 0)
    {
        if ((c >> i) & 1)
        {
            if (kill(pid, SIGUSR1) == -1)
            {
                perror("Erro ao enviar SIGUSR1");
                exit(1);
            }
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
            {
                perror("Erro ao enviar SIGUSR2");
                exit(1);
            }
        }
        usleep(700); // Pequeno atraso para não perder sinais
        i--;
    }
}

int main(int argc, char **argv)
{
    int i;
    int pid;

    if (argc != 3)
    {
        printf("Uso: %s <PID> \"mensagem\"\n", argv[0]);
        return (1);
    }

    pid = ft_atoi(argv[1]);
    if (pid <= 0)
    {
        printf("PID inválido!\n");
        return (1);
    }

    i = 0;
    while (argv[2][i] != '\0')
    {
        send_char((int)pid, (unsigned char)argv[2][i]);
        i++;
    }

    /* Envia caractere nulo opcional para marcar fim da string */
    send_char((int)pid, 0);

    return (0);
}