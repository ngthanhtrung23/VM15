#include <spoj.h>
#include <cstdio>

int main()
{
	spoj_init();

	int test, sig, mem, memMax = 0, tc = 0;
	double score, scoreAll=0, time, timeAll = 0;
	char status[4];

	while (fscanf(spoj_p_in, "%d %3s %lf %d %lf %d\n", &test, status, &score, &sig, &time, &mem) == 6)
	{
		fprintf(spoj_p_info, "test %d - %s (score=%lf, sig=%d, time=%lf, mem=%d)\n", test, status, score, sig, time, mem);
		if (status[0] == 'A')
		{
			if (mem > memMax) memMax = mem;
			timeAll += time;
			scoreAll += score;
		}
		tc++;
	}
	fprintf(spoj_score, "AC %.2lf 0 %lf %d\n", 100.*scoreAll/tc, timeAll, memMax);
}

