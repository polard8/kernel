#include <stdio.h>
#include <string.h>

void escape(char *s, char *t) {
  int length = strlen(s);
  int j = 0;

  for (int i = 0; i < length; i++, j++) {
    switch(s[i]) {
      case '\n': ;
        t[j] = '\\';
        t[j + 1] = 'n';
        j++;
        break;
      case '\t': ;
        t[j] = '\\';
        t[j + 1] = 't';
        j++;
        break;
      default:
        t[j] = s[i];
        break;
    }
  }

  t[j + 1] = '\0';
}

int main() {
  char s[100] = "test\n\t";
  char t[100];

  escape(s, t);
  printf("%s\n", t);

  return 0;
}
