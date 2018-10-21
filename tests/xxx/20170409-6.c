#include <stdio.h>
#include <stdlib.h> //for exit
int main(void) {
	char fname[] = "grade.txt";
	char name[80];
	FILE *f;
	int cnt = 0;
	if ((f = fopen(fname, "w")) == NULL) { //파일 오픈 실패 시
		puts("파일오픈 실패"); //모니터에 표시
		exit(1);
	}
	printf("이름을 입력하세요 \n");
	fgets(name, 80, stdin);
	while (!feof(stdin)) {//입력받은 내용이 끝이 아니라면 파일에 적기
		fprintf(f, "%d", ++cnt);
		fputs(name, f);
		puts("again \n");
		fgets(name, 80, stdin); //다시 입력 받음
	}
	fclose(f);


	/*
	char text[] = "55512345";
	int i;
	FILE *fp = fopen("num.txt", "w");
	for (i = 0; i < sizeof(text) - 1; i++)
		fputc(text[i], fp); //파일에 배열들을 저장
	fclose(fp);
	*/
}