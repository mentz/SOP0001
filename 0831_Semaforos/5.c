semaphore S = 1;

void compra()
{
	while (1)
	{
		int ID = reserva_banco();
		down(&S);
		banco[ID] = 1; // reserva o banco
		if (faz_pagamento() != SUCESSO)
			banco[ID] = 0; // libera o banco
		up(&S);
	}
}
