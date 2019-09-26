/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

//#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "harness.h"
#include "queue.h"
/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q) {
        printf("Fail to new Queue\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    if (!q)
        return;
    list_ele_t *ptr = NULL;
    while (q->head) {
        ptr = q->head;
        q->head = q->head->next;
        free(ptr->value);
        free(ptr);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    // printf("%p\n",(void*)s);//used to debug
    if (!q)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        printf("Allocate fail!!\n");
        return false;
    }

    /*  char *in;
      in = malloc((strlen(s)+1) * sizeof(char));
      memset(in , 0 , sizeof(s));
      strncpy(in , s , strlen(s));
     */
    char *in = malloc((strlen(s) + 1) * sizeof(char));
    if (!in) {
        free(newh);
        return false;
    }
    strcpy(in, s);
    newh->value = in;
    newh->next = q->head;
    if (!q->tail)
        q->tail = newh;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return false;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        printf("Allocate fail!!\n");
        return false;
    }
    /*
    char *in;
    in = malloc((strlen(s)+1) * sizeof(char));
    memset(in , 0 , sizeof(s));
    strncpy(in , s , strlen(s));
   */
    char *in = malloc((strlen(s) + 1) * sizeof(char));  //+1 is a point
    if (!in) {
        free(newt);
        return false;
    }
    strcpy(in, s);
    newt->value = in;
    newt->next = NULL;
    if (!q->tail && !q->head) {
        q->tail = newt;
        q->head = newt;
    } else {
        if (!q->tail) {
            q->tail = newt;

        } else {
            q->tail->next = newt;
            q->tail = newt;
        }
    }
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q)
        return false;
    list_ele_t *rm = NULL;  // do not malloc for rm ptr , it will cause a block
                            // can't re removed
    // char *temp = malloc((strlen(q->head->value)+1) * sizeof(char));
    if (!q->head)
        return false;
    rm = q->head;
    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    q->head = q->head->next;
    free(rm->value);
    free(rm);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q)
        return;
    list_ele_t *pre;
    list_ele_t *middle;
    list_ele_t *last;
    pre = q->head;
    middle = NULL;
    last = NULL;
    while (pre) {
        last = middle;
        middle = pre;
        pre = pre->next;
        middle->next = last;
    }
    q->tail = q->head;
    q->head = middle;
}
