/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:46:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/10 15:56:29 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


// void test_iteri(unsigned int index,char *str)
// {
// 	while (str)
// 	{
// 		*str = *str - 32;
// 		str++;
// 	}
// }

// char test_mapi(unsigned int index,char c)
// {
// 	c -= 32;
// 	return (c);
// }
// void ft_lstprint(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s\n",lst->content);
// 		lst = lst->next;
// 	}
// 	printf("--------------------\n");
// }

// void del_iter(void *content)
// {
// 	int i = 0;
// 	char *str;
// 	str = (char *)content;
// 	while(str[i])
// 	{
// 		str[i] -=  32;
// 		i++;
// 	}
// }

// void *del_map(void *content)
// {
// 	int i = 0;
// 	char *str;
// 	str = (char *)content;
// 	while(str[i])
// 	{
// 		str[i] -=  32;
// 		i++;
// 	}
// 	return(str);
// }

// void del_clear(void *content)
// {
// 	free(content);
// }

// int	main (void)
// {
	/*-----------------Part 1-------------------*/
	/*ft_strlen*/
	// char *str = "print 7";
	// printf("%d\n",ft_strlen(str));
	
	/*ft_memcpy*/
	// char dst[] = "hello";
	// char src[] = "yahia";
	// printf("%s\n",ft_memcpy(NULL, NULL, 2));
	
	/*ft_memmove*/
	// char src[] = "abcde";
	// printf("%s\n",ft_memcpy(src + 2, src, 4));
	
	/*ft_memset*/
	// char src[] = "abcde";
	// printf("%s\n",ft_memset(src, 65, 5));
	// int tab[] = {1,2,3,4};
	// ft_memset(tab, 1, 5);
	// for(int i=0;i<4;i++)
	// 	printf("|%d|",tab[i]);
	
	/*ft_bzero*/
	// char src[] = "abcde";
	// ft_bzero(src, 3);
	// printf("%s\n",src);
	
	/*ft_memcmp*/
	// int dst[] = {1,2,3};
	// int src[] = {1,2,4};
	// printf("%d\n",ft_memcmp(dst, src, 3));
	
	/*ft_memchr*/
	// int dst[] = {1,2,3};
	// printf("%p\n",ft_memchr(dst, 1, 4));
	
	/*ft_atoi*/
	// char src[] = "999999999999999999";
	// printf("%d\n",ft_atoi(src));
	// printf("%d\n",atoi(src));
	// 9223372036854775807
	//-0000000000000000123
	// 9999999999999999999
	// 184467440737095516151
	
	
	/*ft_strchr*/
	// char src[] = "Helalo yahya";
	// printf("%s\n",ft_strchr(src, 'l'));
	
	/*ft_strrchr*/
	// char src[] = "Helalo yahya";
	// printf("%s\n",strrchr(src, 'l'));
	
	/*ft_strnstr*/
	// char src[] = "Helalo yahya";
	// printf("%s\n",ft_strnstr(src, "ya", 9));
	
	/*ft_strncmp*/
	// char dst[] = "hello";
	// char src[] = "yahia";
	// printf("%d\n",strncmp(NULL, NULL, 2));
	
	/*ft_strlcpy*/
	// char dst[] = "hello";
	// char src[] = "yahia";
	// printf("%zu\t%s\n",ft_strlcpy(dst, src, 8),dst);
	
	/*ft_strlcat*/
	// char dst[] = "hello";
	// char src[] = "yahia";
	// printf("%zu\t%s\n",ft_strlcat(dst, src, 9),dst);
	
	/*ft_strlcat*/
	// char dst[] = "hello";
	// char src[] = "yahia";
	// printf("%zu\t%s\n",ft_strlcat(dst, src, 9),dst);
	
	/*-----------------File Descriptor-------------------*/

	/*ft_strdup*/
	// char src[] = "yahia";
	// printf("%s\n",ft_strdup(src));
	
	/*ft_substr*/
	// char src[] = "yahia";
	// printf("%s\n",ft_substr(src, 3, 9));
	
	/*ft_strjoin*/
	// char s1[] = "yahia";
	// char s2[] = "loutfi";
	// printf("%s\n",ft_strjoin(s1, s2));
	
	/*ft_strtrim*/
	// char s1[] = "/*- ya*hia /*-";
	// char c[] = "/*-";
	// printf("%s\n",ft_strtrim(s1, c));
	
	/*ft_split*/
	// char str[] = "-12-3-456-";
	// char c = '-';
	// char **array = ft_split(str, c);
	// for(int i=0; i<4; i++)
	// 	printf("%s\t",array[i]);
	
	/*ft_itoa*/
	// int nbr = -123456;
	// printf("%s",ft_itoa(nbr));
	
	/*ft_strmapi*/
	// char str[] = "hello";
	// printf("%s\n",ft_strmapi(str,ft_test_mapi));
	
	/*ft_striteri*/
	// char str[] = "hello";
	// ft_striteri(str,ft_test_iteri);
	// printf("%s\n",str);
	
	
	/*-----------------File Descriptor-------------------*/
	// int fd = 0;
	// mode_t mode = O_RDONLY | O_WRONLY;
	// fd = creat("test.txt", mode);
	
	/*ft_putchar_fd*/
	// ft_putchar_fd('h',fd);

	/*ft_putstr_fd*/
	// ft_putstr_fd("hello",fd);
	
	/*ft_putendl_fd*/
	// ft_putendl_fd("hello",fd);
	
	/*ft_putnbr_fd*/
	// ft_putnbr_fd(25,fd);
	
	/*-----------------Linked List-------------------*/
	// t_list *head = NULL;
	// t_list *second = NULL;
	// t_list *last = NULL;
	// t_list *new = NULL;
	// int len = 0;
	
	// head = ft_lstnew(ft_strdup("head"));
	// second = ft_lstnew(ft_strdup("second"));
	// printf("%s\n",head->content);
	// ft_lstadd_front(&head, second);
	// last = ft_lstlast(head);
	// printf("%s\n",last->content);
	// ft_lstadd_back(&head, second);
	// ft_lstprint(head);
	// len = ft_lstsize(head);
	// printf("%d\n",len);
	// ft_lstdelone(second,del);
	// ft_lstprint(head);
	// ft_lstclear(&second,del);
	// ft_lstprint(head);
	// ft_lstiter(head,del);
	// ft_lstprint(head);
	// new = ft_lstmap(head,del_map,del_clear);
	// ft_lstprint(new);
// 	return (0);
// }