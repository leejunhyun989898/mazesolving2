#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10

typedef struct {      // ��ü!
	short r;
	short c;
	short dir;
} element;


typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

typedef struct {
	element data2[MAX_STACK_SIZE];
	int top2;
} StackType2;
// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

void init_stack2(StackType2 *s2)
{
	s2->top2 = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_empty2(StackType2 *s2)
{
	return (s2->top2 == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
int is_full2(StackType2 *s2)
{
	return (s2->top2 == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
void push2(StackType2* s2, element item)
{
	if (is_full(s2)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s2->data2[++(s2->top2)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
	}
	else return s->data[(s->top)--];
}
// �����Լ�
element pop2(StackType2* s2)
{
	if (is_empty2(s2)) {
		fprintf(stderr, "���� ���� ����\n");
	}
	else return s2->data2[(s2->top2)--];
}
// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 


element here = { 1,0 }, entry = { 1,0 }, save = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1','1','1','1','1'},
	{'e','1','0','1','0','0','0','1','0','1'},
	{'0','0','0','1','0','0','0','1','0','1'},
	{'0','1','0','0','0','1','1','0','0','1'},
	{'1','0','0','0','1','0','0','0','0','1'},
	{'1','0','0','0','1','0','0','0','0','1'},
	{'1','0','0','0','0','0','1','0','1','1'},
	{'1','0','1','1','1','0','1','1','0','1'},
	{'1','1','0','0','0','0','0','0','0','x'},
	{'1','1','1','1','1','1','1','1','1','1'}
};

// ��ġ�� ���ÿ� ����
void push_loc(StackType* s,StackType2 *s2, int r, int c)
{
    if (r < 0 || c < 0) return;

    if (maze[r][c] == '0') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
        // �� �� �ִ� ��� ����
        maze[r][c] = '*';
    }
    else if (maze[r][c] == '.') {
        return;
    }
    else if (maze[r][c] == 'x') {
        // Ż�� ����� ���, Ż�� ��ο� �߰�
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s2, tmp);
    }
}
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }

}
int main(void)
{
    int r, c;
    StackType s;
    StackType2 s2;

    init_stack(&s);
    init_stack2(&s2);
    here = entry;
    maze_print(maze);
    printf("\n");

    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';

        // �� ���� Ž��
        push_loc(&s, &s2, r + 1, c);
        push_loc(&s, &s2, r - 1, c);
        push_loc(&s, &s2, r, c + 1);
        push_loc(&s, &s2, r, c - 1);

        printf("[%d %d] ", r, c);

        if (is_empty(&s)) {
            // �̷� Ż�� ����
            return 0;
        }

        // ���� ��� ����
        here = pop(&s);

        if (r == 8 && c == 8) {
            // Ż�� ��ο� ������ ���, Ż�� ��� ���
            push(&s, here); // ������ ������ ��θ� ����
            printf("Ż�� ���: ");

            while (!is_empty2(&s2)) {
                // Ż�� ��ο� �ִ� ��� ��ġ ���
                save = pop(&s2);
                printf("[%d %d]", save.r, save.c);
            }
            printf("\n");
        } else {
            printf("-> ");
        }
    }

    printf("---------------------------------\n");

    return 0;
}