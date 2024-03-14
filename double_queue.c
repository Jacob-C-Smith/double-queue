#include <double_queue/double_queue.h>

struct double_queue_node_s
{
	void *content; 
	struct double_queue_node_s *prev,
	                           *next;
};

struct double_queue_s
{
	struct double_queue_node_s *front,
                               *rear;
	mutex _lock;
};

int double_queue_create ( double_queue **const pp_double_queue )
{

	// Argument check
	if ( pp_double_queue == (void *) 0 ) goto no_double_queue;

	// Initialized data
	double_queue *ret = DOUBLE_QUEUE_REALLOC(0, sizeof(double_queue));

	// Error check
	if ( ret == (void *)0 ) goto no_mem;

	// Zero set
	memset(ret, 0, sizeof(double_queue));

	// Return the queue
	*pp_double_queue = ret;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"pp_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}
 
int double_queue_construct ( double_queue **const pp_double_queue )
{

	// Argument check
	if ( pp_double_queue == (void *) 0 ) goto no_double_queue;

	// Initialized data
	double_queue *p_double_queue = 0;

	// Allocate for a queue
	if ( double_queue_create(pp_double_queue) == 0 ) goto failed_to_create_queue;

	// Get a pointer to the allocated memory
	p_double_queue = *pp_double_queue;

	// Create a mutex
    if ( mutex_create(&p_double_queue->_lock) == 0 ) goto failed_to_create_mutex;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"pp_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
				// Error
				return 0;
		}

		// Queue errors
		{
			failed_to_create_queue:
				#ifndef NDEBUG
					printf("[double queue] Failed to create queue in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			
			failed_to_create_mutex:
                #ifndef NDEBUG
                    printf("[double queue] Failed to create mutex in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
		}
	}
}
 
int double_queue_from_contents ( double_queue **const pp_double_queue, void* const* const pp_contents, size_t size )
{

	// Argument check
	if ( pp_double_queue == (void *) 0 ) goto no_double_queue;
	if ( pp_contents     == (void *) 0 ) goto no_double_queue_contents;
	if ( size            ==          0 ) goto no_double_queue_contents;

	// Construct a queue
	if ( double_queue_construct(pp_double_queue) == 0 ) goto failed_to_construct_queue;
	
	// Iterate over each item
	for (size_t i = 0; i < size; i++)

		// Add the item to the queue
		double_queue_enqueue_rear(*pp_double_queue, pp_contents[i]);
	
	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"p_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
				// Error
				return 0;

			no_double_queue_contents:
				#ifndef NDEBUG
					printf("[double queue] Queue has no contents in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}

		// Queue errors
		{
			failed_to_construct_queue:
				#ifndef NDEBUG
					printf("[double queue] Failed to construct queue in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}
	}
}

int double_queue_front ( const double_queue *const p_double_queue, const void ** const pp_value )
{

	// Argument check
	if ( p_double_queue == (void *) 0 ) goto no_double_queue;

	// Lock
	mutex_lock(p_double_queue->_lock);

	// State check
	if ( double_queue_empty(p_double_queue) ) goto no_double_queue_contents;

	// Return a pointer to the caller
	if ( pp_value )
		*pp_value = ((struct double_queue_node_s *)(p_double_queue->front))->content;
	
	// Unlock
	mutex_unlock(p_double_queue->_lock);

	// Exit
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"p_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
				// Error
				return 0;

			no_double_queue_contents:
				#ifndef NDEBUG
					printf("[double queue] Queue has no contents in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}
	}
}
 
int double_queue_rear ( const double_queue *const p_double_queue, const void **const pp_value )
{

	// Argument check
	if ( p_double_queue == (void *) 0 ) goto no_double_queue;
	
	// Lock
	mutex_lock(p_double_queue->_lock);

	// State check
	if ( double_queue_empty(p_double_queue) ) goto no_double_queue_contents;

	// Return a pointer to the rear element
	if ( pp_value )
		*pp_value = ((struct double_queue_node_s *)(p_double_queue->rear))->content;
	
	// Unlock
	mutex_unlock(p_double_queue->_lock);

	// Exit
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"p_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
				// Error
				return 0;

			no_double_queue_contents:
				#ifndef NDEBUG
					printf("[double queue] Queue has no contents in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Unlock
				mutex_unlock(p_double_queue->_lock);

				// Error
				return 0;
		}
	}
}
  
bool double_queue_empty ( const double_queue *const p_double_queue )
{
	
	// Argument check
	if ( p_double_queue == (void *)0 ) goto no_double_queue;

	// Lock
	mutex_lock(p_double_queue->_lock);

	// Initialized data
	bool ret = ( p_double_queue->front == 0 );

	// Unlock
	mutex_unlock(p_double_queue->_lock);
	
	// Success
	return ret;
	
	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for parameter \"p_double_queue\" in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
				// Error
				return 0;
		}
	}
}

int double_queue_enqueue_front ( double_queue *const p_double_queue,  void *const data )
{

	// Argument check
	if ( p_double_queue == (void *) 0 ) goto no_double_queue;

	// Lock
	mutex_lock(p_double_queue->_lock);

	// Initialized data
	struct double_queue_node_s *e = p_double_queue->front, // E comes before F(ront)
	                           *f = DOUBLE_QUEUE_REALLOC(0, sizeof(struct double_queue_node_s));
	
	// Error check
	if ( f == (void *) 0 ) goto no_mem;

	// Zero set
	memset(f, 0, sizeof(struct double_queue_node_s));

	// Walk to the start from the rear
	if ( !e )
		e = p_double_queue->rear = p_double_queue->front = f;
	
	// Default
	else
	{

		// Walk the list
		while ( e->prev != 0 ) e = e->prev;
		
		e->prev = f;
		f->next = e;
		p_double_queue->front = f;
	}

	f->content = data;
	
	// Unlock
	mutex_unlock(p_double_queue->_lock);

	// Success
	return 1;
		
	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"p_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int double_queue_dequeue_front ( double_queue *const p_double_queue, const void **const pp_value )
{
	
	// Argument check
	if ( p_double_queue == (void *) 0 ) goto no_double_queue;
	
	// Lock
	mutex_lock(p_double_queue->_lock);
	
	// State check
	if ( p_double_queue->front == 0 ) goto queue_empty;

	// Initialized data
	struct double_queue_node_s *ret_m = 0;

	ret_m = ((struct double_queue_node_s *)(p_double_queue->front));

	// Remove the front
	if (p_double_queue->front != p_double_queue->rear)
		p_double_queue->front = ((struct double_queue_node_s *)(p_double_queue->front))->next;
	else
		p_double_queue->front = 0,
		p_double_queue->rear  = 0;
	

	// If the caller specified a return...
	if ( pp_value )
		
		// ... return the content to the caller
		*pp_value = ret_m->content;

	// Free the memory
	(void) DOUBLE_QUEUE_REALLOC(ret_m, 0);
		
	// Unlock
	mutex_unlock(p_double_queue->_lock);
	
	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"p_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Queue errors
		{
			queue_empty:

				// No output...
				
				// Unlock
				mutex_unlock(p_double_queue->_lock);

				// Error
				return 0;
		}
	}
}

int double_queue_enqueue_rear ( double_queue *const p_double_queue,  void *const data )
{

	// Argument check
	if ( p_double_queue == (void *) 0 ) goto no_double_queue;

	// Lock
	mutex_lock(p_double_queue->_lock);

	// Initialized data
	struct double_queue_node_s *q = p_double_queue->rear, // Q comes before R(ear)
	                    *r = DOUBLE_QUEUE_REALLOC(0, sizeof(struct double_queue_node_s));
	
	// Error check
	if ( r == (void *) 0 ) goto no_mem;

	// Zero set
	memset(r, 0, sizeof(struct double_queue_node_s));

	// Walk to the end from the rear
	if ( !q )
		q = p_double_queue->front = p_double_queue->rear = r;
	
	// Default
	else
	{

		// Walk the list
		while ( q->next != 0 ) q = q->next;
		
		q->next = r;
		r->prev = q;
		p_double_queue->rear = r;
	}

	r->content = data;
	
	// Unlock
	mutex_unlock(p_double_queue->_lock);

	// Success
	return 1;
		
	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"p_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int double_queue_dequeue_rear ( double_queue *const p_double_queue, const void **const pp_value )
{
	
	// Argument check
	if ( p_double_queue == (void *) 0 ) goto no_double_queue;
	
	// Lock
	mutex_lock(p_double_queue->_lock);
	
	// State check
	if ( p_double_queue->rear == 0 ) goto queue_empty;

	// Initialized data
	struct double_queue_node_s *ret_m = 0;

	ret_m = ((struct double_queue_node_s *)(p_double_queue->rear));

	// Remove the rear
	if (p_double_queue->rear != p_double_queue->front)
		p_double_queue->rear = ((struct double_queue_node_s *)(p_double_queue->rear))->prev;
	else
		p_double_queue->rear = 0,
		p_double_queue->front = 0;
	

	// If the caller specified a return...
	if ( pp_value )
		
		// ... return the content to the caller
		*pp_value = ret_m->content;

	// Free the memory
	(void) DOUBLE_QUEUE_REALLOC(ret_m, 0);
		
	// Unlock
	mutex_unlock(p_double_queue->_lock);
	
	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"p_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Queue errors
		{
			queue_empty:

				// No output...
				
				// Unlock
				mutex_unlock(p_double_queue->_lock);

				// Error
				return 0;
		}
	}
}

int double_queue_destroy ( double_queue **const pp_double_queue )
{

	// Argument check
	if ( pp_double_queue == (void *) 0 ) goto no_double_queue;

	// Initialized data
	double_queue *p_double_queue = *pp_double_queue;
	
	// Lock
	mutex_lock(p_double_queue->_lock);

	// No more queue for end user
	*pp_double_queue = 0;

	// Unlock
	mutex_unlock(p_double_queue->_lock);

	// Empty the queue
	while ( double_queue_empty(p_double_queue) == false )
	{
		double_queue_dequeue_front(p_double_queue, 0);
	}	

	// Free the memory
	(void)DOUBLE_QUEUE_REALLOC(p_double_queue, 0);
		
	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_double_queue:
				#ifndef NDEBUG
					printf("[double queue] Null pointer provided for \"pp_double_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}
