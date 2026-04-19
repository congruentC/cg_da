// cg_da.h

#ifndef cgda_H
#define cgda_H

#include <stddef.h>

typedef struct {
    void *data;
    int length;
    int capacity;
    size_t elem_size;
}cgda;

// Initializes the dynamic array.
// Specify the element size in bytes
cgda cgda_init(int capacity, size_t elem_size);

// Append an element to the dynamic array
void cgda_push(cgda *arr, void *elem);

// Remove and return the last element. Writes
// the last elemen into the "out" buffer.
void cgda_pop(cgda *arr, void *out);

// Double the current capacity of the dynamic array
static void cgda_resize(cgda *arr);

// Returns 1 if empty, 0 otherwise
int cgda_isempty(cgda *arr);

// Returns the current number of elements
int cgda_count(cgda *arr);

// Returns the current capacity
int cgda_cap(cgda *arr);

// Deallocate the dynamic array
void cgda_free(cgda *arr);

// Insert an element at a specified index "idx".
// The elements to the right of "idx", including
// the old element are shifted right.
// Caller's responsibility to only insert elements
// of the same data type.
void cgda_insert(cgda *arr, int idx, void *elem);

// Removes an element at a specified index "idx".
// The elements to the right of "idx" are shifted left.
void cgda_remove(cgda *arr, int idx);

#ifdef CGDA_IMPLEMENTATION


// -------------------------------------------

#include <stdlib.h>
#include <string.h>

cgda cgda_init(int capacity, size_t elem_size){
    cgda arr;
    arr.data = malloc(capacity * elem_size );
    arr.length = 0;
    arr.capacity = capacity;
    arr.elem_size = elem_size;
    return arr;
}

static void cgda_resize(cgda *arr){
    void *tmp = realloc(arr->data, arr->capacity * 2 * arr->elem_size);

    if (!tmp){
        abort();
    }
    arr->data = tmp;
    arr->capacity *= 2;
}

void cgda_push(cgda *arr, void *elem){
    if (arr->length == arr->capacity){
        cgda_resize(arr);
    }
    memcpy((char *)arr->data + arr->length * arr->elem_size, elem, arr->elem_size);
    arr->length++;
}

void cgda_insert(cgda *arr, int idx, void *elem){
   if (arr->length == arr->capacity) cgda_resize(arr);
    memmove(
        (char *)arr->data + (idx + 1) * arr->elem_size,
        (char *)arr->data + idx * arr->elem_size,
        (arr->length - idx) * arr->elem_size);
    memcpy((char *)arr->data + idx * arr->elem_size, elem, arr->elem_size);
    arr->length++;
}

void cgda_remove(cgda *arr, int idx){
    memmove(
        (char *)arr->data + idx * arr->elem_size,
        (char *)arr->data + (idx + 1) * arr->elem_size,
        (arr->length - idx - 1) * arr->elem_size);
    arr->length--;
}

void cgda_pop(cgda *arr, void *out){
    arr->length--;
    memcpy(out, (char *)arr->data + arr->length * arr->elem_size, arr->elem_size);
}

int cgda_count(cgda *arr){
    return arr->length;
}

int cgda_isempty(cgda *arr){
    return arr->length == 0;
}

int cgda_cap(cgda *arr){
    return arr->capacity;
}

void cgda_free(cgda *arr){
    free(arr->data);
    arr->data = NULL;
    arr->length = 0;
    arr->capacity = 0;
}
#endif // CGDA_IMPLEMENTATION
#endif // CGDA_H
