int n = 1;
semaphore S0 = 0, S1 = 0;

void x()
{
	n *= 16;
	up(&S0);
}

void y()
{
	down(&S1);
	n /= 7;
}

void z()
{
	down(&S0);
	n += 40;
	up(&S1);
}
