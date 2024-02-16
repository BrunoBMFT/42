//#include <stdlib.h>
//#include <stdio.h>

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

int ft_list_size(t_list *begin_list)
{
    int i = 0;
    while (begin_list)
    {
        begin_list = begin_list->next;
        i++;
    }
    return (i);
}

/*int main(void)
{
    t_list *node = malloc(sizeof(t_list));
    node->data = "hi";
    node->next = malloc(sizeof(t_list));
    node->next->data = "hello";
    node->next->next = NULL;
    int ret = ft_list_size(node);
    printf("%d", ret);
}*/