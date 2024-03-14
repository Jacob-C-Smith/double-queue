#include <stdio.h>

#include <double_queue/double_queue.h>

int main ( int argc, const char *argv[] )
{

	// Supress compiler warnings
	(void) argc;
	(void) argv;

	// Initialized data
	double_queue *p_double_queue = 0;
	void         *value          = 0;
	char         *pp_contents[]  = { "First!", "Second!", "Third!", "Fourth!", "Fifth!", "Sixth!", 0x0 };

	// Construct a queue
	double_queue_construct(&p_double_queue);
	
	// Add three elements to the queue
	double_queue_enqueue_rear(p_double_queue, "First!");
	double_queue_enqueue_rear(p_double_queue, "Second!");
	double_queue_enqueue_rear(p_double_queue, "Third!");

	// Empty the queue and print each element
	while ( double_queue_empty(p_double_queue) == false )
	{

		// Initialized data
		void *v = 0;

		// Dequeue an item
		double_queue_dequeue_front(p_double_queue, &v);

		// Print the element
		printf("%s\n", (char *) v);
	}
	
	printf("\n");

	// Fill up the queue
	double_queue_from_contents(&p_double_queue, (void **)pp_contents, 6);
	double_queue_dequeue_front(p_double_queue, 0);
	double_queue_dequeue_front(p_double_queue, 0);
	double_queue_dequeue_front(p_double_queue, 0);

	// Empty the full queue
	while ( double_queue_empty(p_double_queue) == false )
	{

		// Initialized data
		void *v = 0;

		// Dequeue an item
		double_queue_dequeue_front(p_double_queue,&v);

		// Print the element
		printf("%s\n", (char *) v);
	}

	// Cause an underflow
	if ( double_queue_dequeue_front(p_double_queue, &value) == 0 )
		printf("Detected queue underflow!\n");

	// Destroy the double queue
	double_queue_destroy(&p_double_queue);

	// Success
	return 0;
}