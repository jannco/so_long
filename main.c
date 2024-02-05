#include <mlx.h>
#include <stdlib.h>

int	main()
{
	void *mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	free(mlx_ptr);
	return (0);
}
