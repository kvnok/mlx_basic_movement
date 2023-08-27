#include "stuff.h"

#define WIDTH 640
#define HEIGHT 640

#define BLOCKSIZE 40

static mlx_image_t* image;

int32_t r_color = 0;
int32_t g_color = 255;
int32_t b_color = 0;
int32_t a_color = 255;

int32_t pixel_select(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void fill_square(void* param)
{
	for (int32_t i = 0; i < image->width; ++i)
	{
		for (int32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = pixel_select(
				r_color, // R
				g_color, // G
				b_color, // B
				a_color  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ok_movement(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (image->instances[0].y != 0)
			image->instances[0].y -= BLOCKSIZE;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (image->instances[0].x != 0)
			image->instances[0].x -= BLOCKSIZE;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (image->instances[0].y != HEIGHT - BLOCKSIZE)
			image->instances[0].y += BLOCKSIZE;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (image->instances[0].x != WIDTH - BLOCKSIZE)
			image->instances[0].x += BLOCKSIZE;
	}
}

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "bouncing", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, BLOCKSIZE, BLOCKSIZE)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, fill_square, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_key_hook(mlx, &ok_movement, NULL);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
