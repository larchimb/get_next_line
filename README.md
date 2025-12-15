*This project has been created as part of the 42 curriculum by larchimb.*

# Get Next Line

## Description

Get Next Line is a 42 project that implements a function capable of reading a file line by line. Each call returns the next line, including the newline character if present.


## Instructions


Here you got a main function to try the code :

```
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = NULL;
		str = get_next_line(fd);
	}
	close(fd);
}
```

Before compiling this code you need to create a file "test.txt", you can put every thing you want in to test the function.
To compile the code : (you can change 42 by the number you want)

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

If you don't use "-D BUFFER_SIZE=42", BUFFER_SIZE will be at 10.



## Algorithm explanation


The function works as follows:

-- Uses a static buffer to keep leftover data between calls.

-- Reads from the file until a newline is found (fullfill_complete_line).

-- Builds the complete line using dynamic concatenation (ft_strjoin_free).

-- Extracts the exact line to return (trim_to_the_line).

-- Cleans the static buffer, keeping only unread data (ft_strchrcpy).

-- If no more data is available, the function returns NULL.


## Bonus

The bonus version works similarly, but instead of one static buffer, a static array of buffers is used—one for each file descriptor.
This allows the function to handle multiple file descriptors simultaneously.
The static buffer array is sized to the maximum number of possible file descriptors (from 0 to 1024).

For the bonus you will use this line to compile :

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_bonus_utils.c
```

## Library

My library contain the functions from my file "get_next_line_utils.c" and the main function. There is a condition to handle the case where the "-D BUFFER_SIZE" flag is not used.

## Resources

- video : </br>
	- https://youtu.be/-Mt2FdJjVno

- web site : </br>
	- https://www.geeksforgeeks.org/c/static-variables-in-c/ </br>
	- https://www.markdownguide.org/basic-syntax/?utm_source=chatgpt.com

- Others : </br>
	- 42'students
