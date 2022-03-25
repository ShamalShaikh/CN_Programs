struct sum_in
{
	long arg1;
	long arg2;
};
struct sum_out
{
	long res1;
};
program SUM_PROG
{
	version SUM_VERS
	{
		sum_out SUMPROC(sum_in)=1;
	} =1;
}= 0x3123000;