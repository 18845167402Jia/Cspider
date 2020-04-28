#include <Cspider.h>


int Cspider_Queue_Del(queue_t * q,url_t* node)
{
	if(q->size == 0)
	{
		return 0;
	}
	*node = q->urlarr[q->rear];
	q->rear = (q->rear + 1)%q->max;
	--q->size;
	return 1;
}