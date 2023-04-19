#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10

typedef struct {      // 교체!
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
// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

void init_stack2(StackType2 *s2)
{
	s2->top2 = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_empty2(StackType2 *s2)
{
	return (s2->top2 == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
int is_full2(StackType2 *s2)
{
	return (s2->top2 == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
void push2(StackType2* s2, element item)
{
	if (is_full(s2)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s2->data2[++(s2->top2)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
	}
	else return s->data[(s->top)--];
}
// 삭제함수
element pop2(StackType2* s2)
{
	if (is_empty2(s2)) {
		fprintf(stderr, "스택 공백 에러\n");
	}
	else return s2->data2[(s2->top2)--];
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 


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

// 위치를 스택에 삽입
void push_loc(StackType* s,StackType2 *s2, int r, int c)
{
    if (r < 0 || c < 0) return;

    if (maze[r][c] == '0') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
        // 갈 수 있는 경로 저장
        maze[r][c] = '*';
    }
    else if (maze[r][c] == '.') {
        return;
    }
    else if (maze[r][c] == 'x') {
        // 탈출 경로인 경우, 탈출 경로에 추가
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

        // 네 방향 탐색
        push_loc(&s, &s2, r + 1, c);
        push_loc(&s, &s2, r - 1, c);
        push_loc(&s, &s2, r, c + 1);
        push_loc(&s, &s2, r, c - 1);

        printf("[%d %d] ", r, c);

        if (is_empty(&s)) {
            // 미로 탈출 실패
            return 0;
        }

        // 다음 경로 선택
        here = pop(&s);

        if (r == 8 && c == 8) {
            // 탈출 경로에 도달한 경우, 탈출 경로 출력
            push(&s, here); // 다음에 진행할 경로를 저장
            printf("탈출 경로: ");

            while (!is_empty2(&s2)) {
                // 탈출 경로에 있는 모든 위치 출력
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