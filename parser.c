#include "push_swap.h"

int ft_isdigit(int x)
{
    return (x > 47 && x < 58);
}

void    free_stack(t_stack *stack)
{
    t_node  *curr;
    t_node  *tmp;

    if (!stack || !stack->top) 
        return ;
    curr = stack->top;
    while (curr)
    {
        tmp = curr->next;
        free(curr);       
        curr = tmp;       
    }
    stack->top = NULL; 
}

int ft_atoi(const char *str, int *error)
{
    unsigned int    i;
    int             sign;
    long            result;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (!ft_isdigit(str[i]))
    {
        *error = 1;
        return (0);
    }    
    while (str[i] >= 48 && str[i] <= 57)
    {
        result = result * 10 + (str[i] - 48);
        i++;
    }
    if (str[i] != '\0')
    {
        *error = 2;
        return (0);
    }
    if (result * sign > INT_MAX || result * sign < INT_MIN)
    {
        *error = 3;
        return (0);
    }
    return ((int)(result * sign));
}

int flag_checker(char **argv)
{
    if (!argv || !argv[1])
        return (0);
    if (!ft_strncmp(argv[1], "--simple", 8))
        return (1);
    else if (!ft_strncmp(argv[1], "--medium", 8))
        return (2);
    else if (!ft_strncmp(argv[1], "--complex", 8))
        return (3);
    else if (!ft_strncmp(argv[1], "--adaptive", 8))
        return (4);
    else 
        return (0);
}

int is_duplicate(t_node *stack, int num)
{
    t_node *curr;

    if (!stack)
        return (0);
    curr = stack;
    while (curr)
    {
        if (num == curr->num)
            return (1);
        curr = curr->next;
    }
    return (0);
}

void parse_arguments(int argc, char **argv, t_stack *stack_a)
{
    int i;
    int j;
    int num;
    int flag;
    char **str_2d;
    int error;

    if (argc < 2)
       return ;
    flag = flag_checker(argv);
    i = (flag) ? 2 : 1;
    while (i < argc)
    {
        j = 0;
        str_2d = ft_split(argv[i], ' ');
        while (str_2d && str_2d[j])
        {
            error = 0;
            num = ft_atoi(str_2d[j], &error);
            if (error || is_duplicate(stack_a->top, num))
            {
                free_all_mem(str_2d);
                free_stack(stack_a);
                write(2, "Error\n", 6);
                exit(1);
            }
            stack_add_back(stack_a, stack_new(num));
            j++;
        }
        free_all_mem(str_2d);
        i++;
    }
}