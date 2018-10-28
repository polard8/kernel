#include <stdio.h>
#define MAXLINE 1000

int getlinelength(char s[], int maxline) {
  int c, i;

  for (i = 0;(i < maxline - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i) {
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    ++i;
  }

  s[i] = '\0';

  return i;
}

void copy(char to[], char from[]) {
  int i;

  i = 0;

  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
}

int main() {
  int len, max = 0;
  char line[MAXLINE], longest[MAXLINE];

  while ((len = getlinelength(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }

  if (max > 0) {
    printf("%s", longest);
  }

  return 0;
}
