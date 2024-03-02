/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   something_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/02 01:50:00 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	something_sort(t_ht ht_a, t_ht ht_b)
{
	t_ht	temp;
	int		count = 0, i = 0;
	temp.head = ht_a.head;
	while (ht_a.head)
	{
		while (temp.head->content < temp.head->next->content)
			count++;
		if (temp.head->content > temp.head->next->content)
		{
			while (i < count)
			{
				push(&ht_a, &ht_b, 'b');
				i++;
			}
		}
		temp.head = temp.head->next;
	}
	ht_b.head = NULL;
}
/*//! FORGET RADIX */
// to get the element with maximum value
int getMax(int nums[], int n) {
    int max = nums[0];
    int i = 1;
    while (i < n)	{
        if (nums[i] > max)
            max = nums[i];
		i++;
	}
    return max;
}
void CountSort(int nums[], int n, int exp) {
    // to store a sorted array
    int output[n];
    // to keep count of values
    int i = 0, cnt[10] = { 0 };
    // count number of values
    while (i < n)	{
        cnt[(nums[i] / exp) % 10]++;
		i++;
	}
    // count index for each
	i = 1;
    while (i < 10)	{
        cnt[i] += cnt[i - 1];
		i++;
	}
    // place the elements at a particular index to sort the array
	i = (n - 1);
    while (i >= 0)	{
        output[cnt[(nums[i] / exp) % 10] - 1] = nums[i];
        cnt[(nums[i] / exp) % 10]--;
		i--;
    }
    // copy output in nums
	i = 0;
    while (i < n)	{
        nums[i] = output[i];
		i++;
	}
}
void RadixSort(int nums[], int n) {
    int m = getMax(nums, n), exp = 1;

    // call CountSort algorithm for each digit
    while (m / exp > 0)
	{
        CountSort(nums, n, exp);
		exp *= 10;
	}
}
