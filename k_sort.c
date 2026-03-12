#include "push_swap.h"


int calculate_chunk_size(int size) {
    if (size <= 100)
        return (15);
    else if (size <= 500)
        return (30);
    else 
        return (45); 
}



void k_sort_distribution(t_stack *stack_a, t_stack *stack_b, t_ops *ops) {
    int i;
    int len;
    int chunk_size;

    len = get_stack_length(stack_a);
    chunk_size = calculate_chunk_size(len); 

    i = 0;
    while (stack_a->top) {
        if (stack_a->top->index <= i) {
            pb(stack_a, stack_b, ops);
            i++;
        } else if (stack_a->top->index <= i + chunk_size) {
            pb(stack_a, stack_b, ops);
            rb(stack_b, ops);
            i++;
        } else {
            ra(stack_a, ops);
        }
    }
}

static int find_max_pos(t_stack *stack_b) {
    t_node *curr;
    int max_index;
    int max_pos;
    int pos;

    if (!stack_b || !stack_b->top)
        return (-1);
    curr = stack_b->top;
    max_index = curr->index;
    max_pos = 0;
    pos = 0;
    while (curr) {
        if (curr->index > max_index) {
            max_index = curr->index;
            max_pos = pos;
        }
        curr = curr->next;
        pos++;
    }
    return (max_pos);
}

void push_back_to_a(t_stack *stack_a, t_stack *stack_b, t_ops *ops) {
    int size;
    int max_pos;

    while (stack_b->top) {
        size = get_stack_length(stack_b);
        max_pos = find_max_pos(stack_b);

        if (max_pos <= size / 2) {
            while (max_pos > 0) {
                rb(stack_b, ops);
                max_pos--;
            }
        } 
        else {
            while (max_pos < size) {
                rrb(stack_b, ops);
                max_pos++;
            }
        }
        pa(stack_a, stack_b, ops);
    }
}