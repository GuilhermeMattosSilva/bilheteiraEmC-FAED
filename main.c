#include "basededados.h"
#include "utilizadores.h"

int main()
{
    if (!ligarBD())
    {
        return 1;
    }

    login();

    desligarBD();

    return 0;
}