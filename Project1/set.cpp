

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "set.h"

symset phi, declbegsys, statbegsys, facbegsys, relset;

//�����Ա�s1,s2���շǽ���ķ�ʽ�ϲ�
symset uniteset(symset s1, symset s2)
{
	symset s;
	snode* p;

	s1 = s1->next;
	s2 = s2->next;

	s = p = (snode*)malloc(sizeof(snode));
	while (s1 && s2)
	{
		p->next = (snode*)malloc(sizeof(snode));
		p = p->next;
		if (s1->elem < s2->elem)
		{
			p->elem = s1->elem;
			s1 = s1->next;
		}
		else
		{
			p->elem = s2->elem;
			s2 = s2->next;
		}
	}

	while (s1)
	{
		p->next = (snode*)malloc(sizeof(snode));
		p = p->next;
		p->elem = s1->elem;
		s1 = s1->next;

	}

	while (s2)
	{
		p->next = (snode*)malloc(sizeof(snode));
		p = p->next;
		p->elem = s2->elem;
		s2 = s2->next;
	}

	p->next = NULL;

	return s;
} // uniteset

  //�����Ա��в���ؼ���Ϊelem��Ԫ��
void setinsert(symset s, int elem)
{
	snode* p = s;
	snode* q;

	while (p->next && p->next->elem < elem)
	{
		p = p->next;
	}

	q = (snode*)malloc(sizeof(snode));
	q->elem = elem;
	q->next = p->next;
	p->next = q;
} // setinsert

//�������Ա�
symset createset(int elem, .../* SYM_NULL */)
{
	va_list list;
	symset s;

	s = (snode*)malloc(sizeof(snode));
	s->next = NULL;

	va_start(list, elem);
	while (elem)
	{
		setinsert(s, elem);
		elem = va_arg(list, int);
	}
	va_end(list);
	return s;
} // createset

//ɾ�����Ա��ͷ���Ӧ�Ŀռ�
void destroyset(symset s)
{
	snode* p;

	while (s)
	{
		p = s;
		p->elem = -1000000;
		s = s->next;
		free(p);
	}
} // destroyset

//�����Ա�Ѱ�ҹؼ���Ϊelem��Ԫ��
int inset(int elem, symset s)
{
	s = s->next;
	while (s && s->elem < elem)
		s = s->next;

	if (s && s->elem == elem)
		return 1;
	else
		return 0;
} // inset

  // EOF set.c
