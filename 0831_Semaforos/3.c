semaforo cpu_mem = 0, cpu_disco = 0, mem_disco = 0, gerente = 0;


void gerente()
{
	while (1)
	{
		r = libera_recursos();
	
		if ((r[0] == CPU && r[1] == MEM) || (r[1] == CPU && r[0] == MEM))
			up(&cpu_mem);

		if ((r[0] == CPU && r[1] == DISCO) || (r[1] == CPU && r[0] == DISCO))
			up(&cpu_disco);

		if ((r[0] == MEM && r[1] == DISCO) || (r[1] == MEM && r[0] == DISCO))
			up(&mem_disco);

		down(&gerente);
	}
}


void consome_mem_cpu()
{
	while (1)
	{
		down(&cpu_mem);
		consome_mem();
		consome_cpu();
		up(&gerente);
	}
}

void consome_mem_disco()
{
	while (1)
	{
		down(&mem_disco);
		consome_mem();
		consome_disco();
		up(&gerente);
	}
}

void consome_cpu_disco()
{
	while (1)
	{
		down(&cpu_disco);
		consome_cpu();
		consome_disco();
		up(&gerente);
	}
}
