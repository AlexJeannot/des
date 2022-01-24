#include "../../incs/md5.h"

size_t  ft_strlen(const char *s)
{
	unsigned int    i;

	i = 0;
    if (s != NULL) {
        while (s[i])
            i++; 
    }
	return (i);
}

void	ft_strncat(char *dest, const char *src, size_t n)
{
	unsigned int	lendest;
	unsigned int	cmp;

	lendest = ft_strlen(dest);
	cmp = 0;
	while (cmp < n && src[cmp])
	{
		dest[lendest + cmp] = src[cmp];
		cmp++;
	}
	dest[lendest + cmp] = '\0';
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_strncpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;

	if (!dest)
		return ;
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destcpy;
	unsigned char	*srccpy;
	unsigned int	cmp;

	cmp = 0;
	destcpy = (unsigned char *)dest;
	srccpy = (unsigned char *)src;
	if (!n || destcpy == srccpy)
		return (dest);
	while (n > cmp)
	{
		destcpy[cmp] = srccpy[cmp];
		cmp++;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		*str = (unsigned char)c;
		str++;
		n--;
	}
	return (s);
}

void    ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	cmp;

	cmp = 0;
	while (s[cmp])
	{
		ft_putchar_fd(s[cmp], fd);
		cmp++;
	}
}