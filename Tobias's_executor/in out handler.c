/*
	Check/Create Output_New
	Output -> Output_Backup
	Output_New -> Output

	Same for Input

	Reset function
*/
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_iostruct
{
	int		mode;
	char	*string;
	int		Output_Backup;
	int		Input_Backup;

}			t_iostruct;

t_iostruct	init_io(void)
{
	t_iostruct	ret;

	ret.mode = -1;
	ret.string = NULL;
	ret.Output_Backup = 1;
	ret.Input_Backup = 0;
	return (ret);
}

t_iostruct	io_handler(t_iostruct io_data)
{
	int	fd;
	int	out;

	out = 0;
	if (io_data.mode == -1)
		return ;
	if (io_data.mode == 0)
		out = set_input(io_data);
	if (io_data.mode == 1 || io_data.mode == 3)
		out = set_output(io_data);
	if (io_data.mode == 2)
		out = heredoc();
	if (out == -1)
		exit(-1);
	return (io_data);
}

int	set_output(t_iostruct io_data)
{
	int	fd;

	if (io_data.mode == 1)
		fd = open(io_data.string, O_WRONLY | O_CREAT, 0777);
	else
		fd = open(io_data.string, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (perror("open"), -1);
	io_data.Input_Backup = dup(STDIN_FILENO);
	if (io_data.Input_Backup == -1 || dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup"), -1);
	io_data.mode = -1;
	return (0);
}

int	set_input(t_iostruct io_data)
{
	int fd;

	fd = open(io_data.string, O_RDONLY, 0777);
	if (fd == -1)
		return (perror("open"), -1);
	io_data.Input_Backup = dup(STDIN_FILENO);
	if (io_data.Input_Backup == -1 || dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup"), -1);
	io_data.mode = -1;
	return (0);
}

int heredoc();