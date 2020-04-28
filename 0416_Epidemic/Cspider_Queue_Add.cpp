#include <Cspider.h>


int Cspider_Queue_Add(queue_t* q,url_t node)   
{
	if(q->size == q->max)
	{
		return 0;
	}
	q->urlarr[q->front] = node;
	q->front = (q->front + 1)% q->max;
	++q->size;
	return 1;
}