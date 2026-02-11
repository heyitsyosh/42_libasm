#ifndef LIBASM_H
# define LIBASM_H

# include <stddef.h> // size_t
#include <sys/types.h> // ssize_t

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

ssize_t	ft_read(int fd, void *buf, size_t count);
ssize_t	ft_write(int fd, const void *buf, size_t count);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);

int		ft_atoi_base(char *str, char *base);
void	ft_list_push_front(t_list **list_head, void *data);
int		ft_list_size(t_list *list_head);
void	ft_list_sort(t_list **list_head, int (*cmp)());
void	ft_list_remove_if(t_list **list_head, void *data_ref, \
							int (*cmp)(), void (*free_fct)(void *));

#endif
