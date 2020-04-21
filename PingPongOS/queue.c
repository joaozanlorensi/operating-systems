#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int queue_exists(queue_t** queue);
int element_exists(queue_t* element);
int queue_empty(queue_t** queue);
int element_in_other_queue(queue_t* element);
int element_in_queue(queue_t** queue, queue_t* elem);

/*
int main(){
    queue_t first_element;
    first_element.data = 'a';
    queue_t second_element;
    second_element.data = 'b';
    queue_t third_element;
    third_element.data = 'c';
    
    queue_t *queue;

    
    fprintf(stderr, queue_exists(&queue)?"":"Error: the queue doesn't exist\n");
    fprintf(stderr, queue_empty(queue)?"Error: the queue is empty\n":"");
    fprintf(stderr, element_exists(&first_element)?"":"Error: the element doesn't exist\n");
    fprintf(stderr, element_in_other_queue(&first_element)?"Error: the element is already in another queue\n":"");
    fprintf(stderr, element_in_queue(&first_element, &queue)?"":"Error: the element is not in this queue\n");
    

    first_element.next = &second_element;
    first_element.prev = &second_element;
    second_element.next = &first_element;
    second_element.prev = &first_element;

    queue = &first_element;

    //printf("Queue size: %d\n\n", queue_size(queue));
    third_element.next = NULL;
    third_element.prev = NULL;

    //queue_remove(&queue, &third_element);
    queue_append(&queue, &third_element);
    printf("Queue size: %d\n\n", queue_size(queue));
    queue_remove(&queue, &third_element);
    printf("Queue size: %d\n\n", queue_size(queue));
    
    queue_print("fila: ", queue, print_elem);

    return 0;
}
*/

int queue_exists(queue_t **queue){
    return (queue != NULL)? 1:0;
}

int queue_empty(queue_t** queue){
    return (*queue == NULL)? 1:0;
}

int element_exists(queue_t* element){
    return (element != NULL)? 1:0;
}

int element_in_other_queue(queue_t* element){
    return (element->next != NULL && element->prev != NULL)? 1:0;
}

int element_in_queue(queue_t** queue, queue_t* elem){
    queue_t *first = *queue;
    queue_t *aux = *queue;
    int elem_in_queue = 1;

    while(aux != elem){
        aux = aux->next;
        if (aux == first){
            elem_in_queue = 0;
            break;
        }
    }
    return elem_in_queue;
}

int queue_size(queue_t* queue){
    int counter = !queue_empty(&queue);
    if (counter != 0){
        queue_t* first = queue;
        while(queue->next != first){
            queue = queue->next;
            counter ++;
        }
    }
    return counter;
}

void queue_append(queue_t** queue, queue_t* elem){
    fprintf(stderr, queue_exists(queue)?"":"Error (queue_append): the queue doesn't exist\n");
    fprintf(stderr, element_exists(elem)?"":"Error (queue_append): the element doesn't exist\n");
    fprintf(stderr, element_in_other_queue(elem)?"Error (queue_append): the element is already in another queue\n":"");
    
    if (!queue_exists(queue) || !element_exists(elem) || element_in_other_queue(elem))
        return;
    
    // Creates queue with one element
    if(queue_empty(queue)){
        elem->next = elem;
        elem->prev = elem;
        *queue = elem;
        return;
    }

    queue_t *first = *queue;
    queue_t *aux = *queue;

    while(aux->next != first){
        aux = aux->next;
    }

    elem->next = first;
    elem->prev = aux;
    aux->next = elem;
    first->prev = elem;

    return;
}

queue_t *queue_remove(queue_t** queue,  queue_t* elem){
    fprintf(stderr, queue_exists(queue)?"":"Error (queue_remove): the queue doesn't exist\n");
    fprintf(stderr, queue_empty(queue)?"Error (queue_remove): the queue is empty\n":"");
    fprintf(stderr, element_exists(elem)?"":"Error (queue_remove): the element doesn't exist\n");
    fprintf(stderr, element_in_queue(queue, elem)?"":"Error (queue_remove): the element is not in this queue\n");
    
    if (!queue_exists(queue) || queue_empty(queue) || !element_exists(elem) || !element_in_queue(queue, elem))
        return NULL;
    
    if (queue_size(*queue) == 1){
        elem->prev = NULL;
        elem->next = NULL;
        *queue = NULL;
        return elem;
    }

    queue_t *aux = *queue;
    queue_t *first = *queue;

    while(aux->next != elem){
        aux = aux->next;
    }

    aux->next = elem->next;
    aux = aux->next;
    aux->prev = elem->prev;

    if (elem == first){
        *queue = elem->next;
    }
    else{
        *queue = first;
    }

    elem->next = NULL;
    elem->prev = NULL;

    return elem;
}

void queue_print(char* name, queue_t* queue, void print_elem (void*)){
    queue_t *first = queue;
    queue_t *aux = queue;

    printf("[ ");
    while(aux != first){
        print_elem(aux);
        aux = aux->next;
    }
    printf(" ]");
    return;
}