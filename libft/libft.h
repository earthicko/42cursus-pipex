/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:37 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/08 12:10:39 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// contains: malloc, free, write, va_start, va_arg, va_copy, va_end
#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define CODE_OK 0
# define CODE_ERROR_GENERIC -1
# define CODE_ERROR_IO -2
# define CODE_ERROR_MALLOC -3
# define CODE_ERROR_SCOPE -4

# define SYMBOL_ALTFORM '#'
# define SYMBOL_BLANK ' '
# define SYMBOL_SIGN '+'
# define SYMBOL_LEFT '-'
# define SYMBOL_ZEROPAD '0'
# define SYMBOL_CHAR 'c'
# define SYMBOL_STR 's'
# define SYMBOL_PTR 'p'
# define SYMBOL_SDEC1 'd'
# define SYMBOL_SDEC2 'i'
# define SYMBOL_UDEC 'u'
# define SYMBOL_LHEX 'x'
# define SYMBOL_UHEX 'X'
# define SYMBOL_PCENT '%'
# define SYMBOL_NULL "(null)"
# define CHARSET_DEC "0123456789"
# define CHARSET_LHEX "0123456789abcdef"
# define CHARSET_UHEX "0123456789ABCDEF"
# define PREFIX_LHEX "0x"
# define PREFIX_UHEX "0X"
# define PREFIX_POS "+"
# define PREFIX_NEG "-"
# define PREFIX_BLANK " "
# define L_PREFIX_HEX 2
# define L_PREFIX_POS 1
# define L_PREFIX_NEG 1
# define L_PREFIX_BLANK 1

typedef long long			t_ll;
typedef unsigned long long	t_ull;
typedef unsigned int		t_uint;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_fdbuff
{
	int		fd;
	char	*buff;
}	t_fdbuff;

typedef struct s_conv
{
	int		i_conv;
	char	*s;
	char	*e;
	int		minwidth;
	int		precision;
	int		f_left;
	int		f_zeropad;
	int		f_precision;
	int		f_minwidth;
	int		f_altform;
	int		f_blank;
	int		f_sign;
}	t_conv;

enum e_conv
{
	PLAIN = 0,
	CHAR,
	STR,
	PTR,
	SDEC,
	UDEC,
	LHEX,
	UHEX,
	PCENT
};

enum e_bool
{
	FALSE = 0,
	TRUE
};

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_fdbuff	*init_fdbuff(int fd);
void		del_fdbuff(void *fdbuff);
t_list		*init_fdlist(t_list **head, int init_fd);
void		*del_fdlist(t_list **buff_list, t_list *target);
t_fdbuff	*loc_fdbuff(t_list *node);
int			is_ending_char(char c);
char		*get_next_line(int fd);
//			ft_printf.c      
int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
//			create_str.c      
char		*cstr_nchars(int n, char c);
char		*cstr_nbr(t_conv *conv, t_ll nbr, char *charset);
char		*cstr_prefix(t_conv *conv, t_ll num, t_ll base);
char		*cstr_padding(t_conv *conv, int len_rest);
//			create_str_utils.c      
int			cstr_nbr_fill_str(char *buf, t_ll nbr, char *base, int l_base);
char		*cstr_sign(t_conv *conv, t_ll num);
int			append_hex_prefix(t_conv *conv, t_ll num, t_ll base, char **buf);
int			append_precision(t_conv *conv, t_ll num, t_ll base, char **buf);
//			ft_numlen.c      
int			ft_numlen_base(t_ll num, t_ll base);
//			ft_str_utils.c      
int			ft_strappend(char **body, const char *tail);
char		*ft_strmerge(int n_str, ...);
//			fwrite_chr.c      
int			fwrite_plain(int fd, t_conv *conv);
int			fwrite_char(int fd, t_conv *conv, int c);
int			fwrite_str(int fd, t_conv *conv, char *str);
//			fwrite_num.c      
int			fwrite_int(int fd, t_conv *conv, int num, char *charset);
int			fwrite_uint(int fd, t_conv *conv, t_uint num, char *charset);
//			fwrite_ptr.c      
int			fwrite_ptr(int fd, t_conv *conv, void *ptr);
//			fwrite_utils.c      
char		*merge_num_buffers(t_conv *conv, char **buf);
void		abort_fwrite(char **bufs);
int			add_padding(t_conv *conv, char **buf);
//			parse_format.c      
int			parse_format(t_list **convs, const char *format);
//			parse_format_utils.c      
void		parse_printf_flags(t_conv *conv, char **format);
void		parse_printf_minwidth(t_conv *conv, char **format);
void		parse_printf_precision(t_conv *conv, char **format);
int			parse_printf_conv(t_conv *conv, char **fmt);
//			t_conv.c      
t_conv		*create_conv(void);
void		del_conv(void *conv);
#endif
