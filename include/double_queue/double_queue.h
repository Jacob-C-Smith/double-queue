/** !
 * Include header for double queue library
 * 
 * @file double_queue/double_queue.h 
 * 
 * @author Jacob Smith
 */

// Include guard
#pragma once

// sync submodule
#include <sync/sync.h>

// Standard library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Memory management macro
#ifndef DOUBLE_QUEUE_REALLOC
#define DOUBLE_QUEUE_REALLOC(p, sz) realloc(p,sz)
#endif

// Forward declarations
struct double_queue_s;

// Type definitions
/** !
 *  @brief The type definition of a double queue struct
 */
typedef struct double_queue_s double_queue;

// Allocaters
/** !
 *  Allocate memory for a double queue
 *
 * @param pp_double_queue return
 *
 * @sa double_queue_destroy
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_create ( double_queue **const pp_double_queue );

// Constructors
/** !
 *  Construct a double queue with a specific number of entries
 *
 * @param pp_double_queue return
 *
 * @sa double_queue_create
 * @sa double_queue_from_contents
 * @sa double_queue_destroy
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_construct ( double_queue **const pp_double_queue );

/** !
 *  Construct a double queue from a void pointer array
 *
 * @param pp_double_queue return
 * @param pp_contents     pointer to array of void pointers to use as double queue contents.
 * @param size            number of double queue entries. 
 *
 * @sa double_queue_construct
 * @sa double_queue_destroy
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_from_contents ( double_queue **const pp_double_queue, void * const* const pp_contents, size_t size );

// Accessors
/** !
 *  Get the element at the front of the double queue
 *
 * @param p_double_queue double queue
 *
 * @sa double_queue_rear
 *
 * @return element value on success, null pointer on error
 */
DLLEXPORT int double_queue_front ( const double_queue *const p_double_queue, void **const pp_value );

/** !
 *  Get the element at the rear of the double queue
 *
 * @param p_double_queue double queue
 *
 * @sa double_queue_front
 *
 * @return element on success, null pointer on error
 */
DLLEXPORT int double_queue_rear ( const double_queue *const p_double_queue, void **const pp_value );

/** !
 *  Check if a double queue is empty
 *
 * @param p_double_queue double queue
 *
 * @sa double_queue_full
 *
 * @return true if double queue is empty else false
 */
DLLEXPORT bool double_queue_empty ( const double_queue *const p_double_queue );

// Mutators
/** !
 *  Add an element to the front of a double queue
 *
 * @param p_double_queue the double queue
 * @param data           element to add to the double queue
 *
 * @sa double_queue_dequeue_front
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_enqueue_front ( double_queue *const p_double_queue, void *const data );

/** !
 *  Remove an element from the front of a double queue
 *
 * @param p_double_queue the double queue
 * @param pp_value       return
 *
 * @sa double_queue_enqueue_front
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_dequeue_front ( double_queue *const p_double_queue, void **const pp_value );

/** !
 *  Add an element to the rear of a double queue
 *
 * @param p_double_queue the double queue
 * @param data           element to add to the double queue
 *
 * @sa double_queue_dequeue_rear
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_enqueue_rear ( double_queue *const p_double_queue, void *const data );

/** !
 *  Remove an element from the rear of a double queue
 *
 * @param p_double_queue the double queue
 * @param pp_value       return
 *
 * @sa double_queue_enqueue_rear
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_dequeue_rear ( double_queue *const p_double_queue, void **const pp_value );

// Destructors
/** !
 *  Destroy and deallocate a double queue
 *
 * @param pp_double_queue pointer to double queue
 *
 * @sa double_queue_create
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int double_queue_destroy ( double_queue **const pp_double_queue );
