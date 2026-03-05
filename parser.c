//Logic to handle argv, check for flags (like --simple),
//and validate that inputs are unique integers within the int range



#include "push_swap.h"


int	ft_isdigit(int x)
{
	return (x > 47 && x < 58);
}

int	ft_atoi(const char *str, int *error)
{
	unsigned int	i;
	int				sign;
	long			result;

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
    if(!ft_isdigit(str[i])){
        *error = 1; // format error only sign 
        return 0;
    }    
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
    if(str[i] != '\0'){
        *error = 2; // format error not a number
        return 0;
    }
    if(result * sign > INT_MAX || result * sign < INT_MIN){
        *error = 3; // int overflow
        return 0;
    }
	return ((int)(result * sign));
}


int flag_checker(char **argv){

    if(!ft_strncmp(argv[1], "--simple", 8))
        return 1;
    else if (!ft_strncmp(argv[1], "--medium", 8))
        return 2;
    else if(!ft_strncmp(argv[1], "--complex", 8))
        return 3;
    else if (!ft_strncmp(argv[1], "--adaptive", 8))
        return 4;
    else 
        return 0;

}


is_duplicate(t_node *stack, int num){
if(!stack)
    return 0;

t_node *curr;
curr = stack;

    while(curr){
        if(num == curr->num)
            return 1;
        curr = curr->next;
    }
return 0;
}

void parse_arguments(int argc, char **argv, t_node **stack_a){

    int i;
    int j;
    int num;
    int flag;
    char **str_2d;
    int error;

    error = 0;
    j = 0;
    i = 1;

    if(argc < 2)
       return;
    flag = flag_checker(argv);
    if(flag){
        i = 2;
    }
    while(i < argc){
        j = 0;
        str_2d = ft_split(argv[i], ' ');
        while(str_2d[j]){
            num = ft_atoi(str_2d[j], &error);
            if(error || is_duplicate(stack_a, num)){
                if (!error)
                    error = 4;
                free_all_mem(str_2d, j);
                //stex hly pti nodery datarkem nor return 
                return;
            }
            add_to_stack(stack_a, num); // es funkcian hly pti grvi (libft add back )
            j++;
        }
        free_all_mem(str_2d, j);
        i++;
    }

    return;
}

