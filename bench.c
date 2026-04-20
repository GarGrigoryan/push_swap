#include "push_swap.h"

static void	print_percent(float disorder, int fd)
{
	int	pct_int;
	int	pct_dec;
	float	pct;

	pct = disorder * 100.0f;
	pct_int = (int)pct;
	pct_dec = (int)((pct - (float)pct_int) * 100.0f + 0.5f);
	if (pct_dec >= 100)
	{
		pct_int++;
		pct_dec = 0;
	}
	ft_putnbr_fd(pct_int, fd);
	write(fd, ".", 1);
	if (pct_dec < 10)
		write(fd, "0", 1);
	ft_putnbr_fd(pct_dec, fd);
	write(fd, "%\n", 2);
}

static char	*resolve_strategy(int strategy, float disorder, int len)
{
	if (len <= 5)
		return ("Adaptive / O(n^2)");
	if (strategy == 1)
		return ("Simple / O(n^2)");
	if (strategy == 2)
		return ("Medium / O(n*sqrt(n))");
	if (strategy == 3)
		return ("Complex / O(n log n)");
	if (disorder < 0.2f)
		return ("Adaptive / O(n^2)");
	if (disorder < 0.5f)
		return ("Adaptive / O(n*sqrt(n))");
	return ("Adaptive / O(n log n)");
}

static void	print_ops_line1(t_ops *ops, int fd)
{
	write(fd, "[bench] sa:  ", 13);
	ft_putnbr_fd(ops->sa, fd);
	write(fd, "  sb:  ", 7);
	ft_putnbr_fd(ops->sb, fd);
	write(fd, "  ss:  ", 7);
	ft_putnbr_fd(ops->ss, fd);
	write(fd, "  pa:  ", 7);
	ft_putnbr_fd(ops->pa, fd);
	write(fd, "  pb:  ", 7);
	ft_putnbr_fd(ops->pb, fd);
	write(fd, "\n", 1);
}

static void	print_ops_line2(t_ops *ops, int fd)
{
	write(fd, "[bench] ra:  ", 13);
	ft_putnbr_fd(ops->ra, fd);
	write(fd, "  rb:  ", 7);
	ft_putnbr_fd(ops->rb, fd);
	write(fd, "  rr:  ", 7);
	ft_putnbr_fd(ops->rr, fd);
	write(fd, "  rra:  ", 8);
	ft_putnbr_fd(ops->rra, fd);
	write(fd, "  rrb:  ", 8);
	ft_putnbr_fd(ops->rrb, fd);
	write(fd, "  rrr:  ", 8);
	ft_putnbr_fd(ops->rrr, fd);
	write(fd, "\n", 1);
}

void	print_bench(t_ops *ops, float disorder, int strategy, int len)
{
	int		total;
	char	*name;

	total = ops->pa + ops->pb + ops->ra + ops->rb + ops->rr
		+ ops->rra + ops->rrb + ops->rrr + ops->sa + ops->sb + ops->ss;
	name = resolve_strategy(strategy, disorder, len);
	write(2, "[bench] disorder:  ", 19);
	print_percent(disorder, 2);
	write(2, "[bench] strategy:  ", 19);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
	write(2, "[bench] total_ops:  ", 20);
	ft_putnbr_fd(total, 2);
	write(2, "\n", 1);
	print_ops_line1(ops, 2);
	print_ops_line2(ops, 2);
}
