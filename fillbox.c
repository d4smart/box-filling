/*=============================================================================
#     FileName: fillbox.c
#         Desc: search, expand and compute 
#       Author: d4smart
#        Email: d4smart@foxmail.com
#     HomePage: https://github.com/d4smart/box-filling
#      Version: 0.0.1
#   LastChange: 2016-05-29 21:08:30
=============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define true 1
#define false 0

typedef struct _Ball {
  double x;
  double y;
  double r;
} Ball;

typedef struct _listNode {
  struct _listNode * next;
  int isblock;
  Ball ball;
} listNode;



void insert(Ball ball, int isblock);
double distance(Ball b1, Ball b2);
double m_abs(double num);
int judge(Ball b);
void freeBox();
void putBall();

void putBlock(double x, double y);


listNode *head = NULL;
double step = 1/128.0;
int num = 0;
double r2 = 0;

int main(int argc, char *argv[])
{

  int n, blocks, i;
  printf("\n\nEnter the number of balls and blocks (to put blocks add number and position): ");
  while(scanf("%d%d", &n, &blocks) != EOF)
  {
    num = 0, r2 = 0;
    for(i = 0; i < blocks; i ++)
    {
      double x, y;
      scanf("%lf%lf", &x, &y);
      putBlock(x, y);
    }
    printf("\nnum\t x\t  y\t  r\t sum(r^2)\n");
    for(i = 0; i < n; i ++)
    {
      putBall();
    }

    printf("\nsum of R^2:\t %lf\n", r2);
    freeBox();
    printf("\n\nEnter the number of balls and blocks (to put blocks add number and position): ");
  }

  printf("\n");
  return 0;
}
void putBlock(double x, double y)
{
  Ball ball = {x, y, 0};
  insert(ball, true);
}
void freeBox()
{
  while(head)
  {
    listNode *tmp = head;
    head = tmp->next;
    free(tmp);
  }
}
void insert(Ball ball, int isblock)
{
  listNode * node = (listNode *)malloc(sizeof(listNode));
  node->isblock = isblock;
  node->ball = ball;
  node->next = head;
  head = node;
}
void putBall()
{
  Ball ball = {-1 + step, -1 + step, 0};
  Ball maxBall = ball;
  int i, j;
  for (i = 0; ball.x < 1; ++i) {
    ball.x += step;
    ball.y = -1 + step;
    for (j = 0; ball.y < 1; ++j) {
      ball.y += step;
      ball.r = 0;
      double rstep = 0.1;
      while(rstep >= 0.00001)
      {
        if(ball.r > maxBall.r)
        {
          maxBall = ball;
        }
        /*printf("%lf, %lf, %lf\n",ball.x, ball.y, ball.r);*/
        ball.r += rstep;
        if(!judge(ball))
        {
          ball.r -= rstep;
          rstep /= 10;
        }
      }
    }
  }
  if(judge(maxBall)){
    insert(maxBall, false);
    num++;
    r2 += maxBall.r * maxBall.r;
      printf("%d\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, r2);
  }
}

int judge(Ball b)
{
  if((m_abs(b.x) + b.r) > 1 || (m_abs(b.y) + b.r) > 1)
  {
    return false;
  }
  listNode *tmp = head;
  while(tmp)
  {
    Ball ball = tmp->ball;
    if(distance(b, ball) < b.r + ball.r )
    {
      return false;
    }
    tmp = tmp->next;
  }
  return true;
}
double m_abs(double num)
{
  if(num > 0)
    return num;
  return 0 - num;
}

double distance(Ball b1, Ball b2)
{
  double x1 = b1.x;
  double y1 = b1.y;
  double x2 = b2.x;
  double y2 = b2.y;
  return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5);
}
