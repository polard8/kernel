/*
 * File: main.c 
 *
 * Descrição: 
 *     Arquivo principal de IDLE.BIN.
 *     IDLE.BIN é um processo com apenas uma thread.
 *     IDLE.BIN é um aplicativo de 32bit em user mode. 
 *
 *     Esse programa deverá ser chamado sempre que o sistema estiver ocioso,
 * ou com falta de opções viáveis. Então esse programa deve ficar responsável 
 * por alguma rotina de manutenção do equilíbrio de sitema, ou por gerência de 
 * energia, com o objetivo de poupar energia nesse momento de ociosidade.
 *
 * O processo idle pode solicitar que processos de gerencia de energia entrem em
 * atuação. Pois a chamada do processo idle em si já é um indicativo de ociosidade
 * do sistema. Pode-se também organizar bancos de dados, registros, memória, buffer,
 * cache etc.
 *
 *     O sistema pode configurar o que esse processo faz quando a máquina 
 * está em idle mode. Quando não há nenhum processo pra rodar ou a cpu se 
 * encontra ociosa, pode-se usar alguma rotina otimizada presente neste 
 * programa. Parece que a intel oferece sujestões pra esse caso, não sei.
 * 
 * Obs: O entry point está em head.s
 *      Agora idle pode fazer systemcalls. 
 *
 * @todo: Criar argumento de entrada.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Revisão.
 *     ...
 */
 
 
//
// Includes.
// 
 
#include <types.h>
#include <stddef.h>


//#importante
//presizamos só disso.
#include <stdlib.h>
#include <stdio.h>   


#include <ctype.h>
#include "api.h"      //api.
#include "tprintf.h" 






//===============================================================================
// mini yacc begin
//===============================================================================


//assert:

/*
 #ifndef __DEBUG
 #define assert(ignore)  ((void)0)
 #else
 #undef assert
 #undef __myassert
 #define assert(expression)  \
  ((void)((expression) ? 0 : (__myassert (#expression, __FILE__, __LINE__), 0)))
 
 #define __myassert(expression, file, line)  \
  __myassfail("Failed assertion `%s' at line %d of `%s'.",    \
        expression, line, file)
 
 static void
 __myassfail(const char *format,...)
 {
    va_list arg;
    static char mystderr[0x80];
    va_start(arg, format);
    (void)vsprintf(&mystderr[0], format, arg);    
    while(1);
    va_end(arg);
 }
 #endif
*/

/*% clang -g -Wall -Wextra % -o #
 * miniyacc - LALR(1) grammars for C
 * See LICENSE for copyright and license details.
 */
 
 
 //#importante 
 //#todo 
 //Fazer o header assert.h do jeito que esse programa precisa.
 
#define assert(ignore)  ((void)0)
 
//#include <assert.h> //falta esse
//#include <ctype.h>  //em cima
//#include <stdio.h>  //em cima
//#include <stdlib.h>  //em cima
//#include <string.h> //em cima

typedef int Sym;
typedef struct Rule Rule;
typedef struct TSet TSet;
typedef struct Info Info;
typedef struct Term Term;
typedef struct Item Item;
typedef struct Row Row;

#define S ((Sym) -1)
#define Red(n) (- (n+2)) /* involutive, Red(Red(x)) == x */
#define GetBit(s,n) (s[n/32] & (1<<(n%32)))
#define SetBit(s,n) (s[n/32] |= 1<<(n%32))

enum {
	IdntSz = 64,
	MaxRhs = 32,
	MaxTk = 500,
	MaxNt = 500,
	MaxRl = 800,
	MaxTm = 1000,

	TSetSz = (MaxTk+31)/32,
	Sym0 = MaxTk
};

struct Rule {
	Sym lhs;
	Sym rhs[MaxRhs];
	char *act;
	int actln;
	int prec;
};

struct TSet {
	unsigned t[TSetSz];
};

struct Info {
	int nul;
	TSet fst;
	int prec;
	enum {
		ANone,
		ALeft,
		ARight,
		ANonassoc
	} assoc;
	char name[IdntSz];
	char type[IdntSz];
};

struct Term {
	Rule *rule;
	int dot;
	TSet lk;
};

struct Item {
	int id;
	int nt;
	Term ts[MaxTm];
	Item **gtbl;
	int dirty;
};

struct Row {
	int def;
	int ndef;
	int *t;
};

char srs[] = "shift/reduce conflict state %d token %s\n";
char rrs[] = "reduce/reduce conflict state %d token %s\n";

Item i0; /* temporary item */

int nrl, nsy, nst, ntk;
Rule rs[MaxRl]; /* grammar rules (ordered, rcmp) */
Info is[MaxTk+MaxNt]; /* symbol information */
Item **st; /* LALR(1) states (ordered, icmp) */
Row *as;   /* action table [state][tok] */
Row *gs;   /* goto table   [sym][state] */
Sym sstart;/* start symbol */
Item *ini; /* initial state */
int doty;  /* type-checking enabled */

int srconf, rrconf;
int actsz;
int *act;
int *chk;
int *adsp;
int *gdsp;

int lineno = 1;
char *srca;
FILE *fin;
FILE *fout;
FILE *fgrm;
FILE *fhdr;

void
die(char *s)
{
	fprintf(stderr, "%s (on line %d)\n", s, lineno);
	exit(1);
}

void *
yalloc(size_t n, size_t o)
{
	void *p;

	p = calloc(n, o);
	if (!p)
		die("out of memory");
	return p;
}

int
rcmp(const void *a, const void *b)
{
	return ((Rule *)a)->lhs - ((Rule *)b)->lhs;
}

Rule *
rfind(Sym lhs)
{
	Rule *r;
	Rule k;

	k.lhs = lhs;
	r = bsearch(&k, rs, nrl, sizeof *r, rcmp);
	if (r != 0)
		while (r > rs && r[-1].lhs == lhs)
			r--;
	return r;
}

int
slen(Sym *l)
{
	int n;

	for (n=0; *l!=S; n++, l++);
	return n;
}

void
tszero(TSet *ts)
{
	memset(ts, 0, sizeof *ts);
}

int
tsunion(TSet *tsa, TSet *tsb)
{
	int n;
	unsigned *a, *b, c, t;

	c = 0;
	a = tsa->t;
	b = tsb->t;
	n = (31+ntk)/32;
	while (n-- > 0) {
		t = *a;
		*a |= *b++;
		c |= t ^ *a++;
	}
	return !!c;
}

void
first(TSet *ts, Sym *stnc, TSet *last)
{
	Sym f;

	f = stnc[0];
	if (f == S) {
		if (last)
			tsunion(ts, last);
		return;
	}
	if (f < ntk) {
		SetBit(ts->t, f);
		return;
	}
	if (is[f].nul)
		first(ts, stnc+1, last);
	tsunion(ts, &is[f].fst);
}

void
ginit()
{
	int chg;
	Rule *r;
	Info *i;
	Sym *s;
	TSet ts;

	do {
		chg = 0;
		for (r=rs; r-rs<nrl; r++) {
			i = &is[r->lhs];
			for (s=r->rhs; *s!=S; s++)
				if (!is[*s].nul)
					goto nonul;
			chg |= i->nul == 0;
			i->nul = 1;
		nonul:
			tszero(&ts);
			first(&ts, r->rhs, 0);
			chg |= tsunion(&i->fst, &ts);
		}
	} while (chg);
}

int
tcmp(Term *a, Term *b)
{
	int c;

	c = a->rule - b->rule;
	if (c==0)
		c = a->dot - b->dot;
	return c;
}

int
tcmpv(const void *a, const void *b)
{
	return tcmp((Term *)a, (Term *)b);
}

void
iclose(Item *i)
{
	int smap[MaxNt];
	Rule *r;
	Term *t, t1;
	Sym s, *rem;
	int chg, n, m;

	t1.dot = 0;
	memset(smap, 0, sizeof smap);
	for (n=0; n<i->nt; n++) {
		t = &i->ts[n];
		s = t->rule->lhs-Sym0;
		if (t->dot==0)
		if (smap[s]==0)
			smap[s] = n;
	}
	do {
		chg = 0;
		for (n=0; n<i->nt; n++) {
			t = &i->ts[n];
			rem = &t->rule->rhs[t->dot];
			s = *rem++;
			if (s < Sym0 || s == S)
				continue;
			r = rfind(s);
			if (!r)
				die("some non-terminals are not defined");
			tszero(&t1.lk);
			first(&t1.lk, rem, &t->lk);
			m = smap[s-Sym0];
			if (m)
				for (; r-rs<nrl && r->lhs==s; r++, m++)
					chg |= tsunion(&i->ts[m].lk, &t1.lk);
			else {
				m = i->nt;
				smap[s-Sym0] = m;
				for (; r-rs<nrl && r->lhs==s; r++, m++) {
					if (m>=MaxTm)
						die("too many terms in item");
					t1.rule = r;
					i->ts[m] = t1;
				}
				i->nt = m;
				chg = 1;
			}
		}
	} while (chg);
}

void
igoto(Item *i, Sym s)
{
	Term *t, *t1;
	int n;

	i0.nt = 0;
	for (n=0, t=i->ts; n<i->nt; n++, t++) {
		if (t->rule->rhs[t->dot] != s)
			continue;
		t1 = &i0.ts[i0.nt++];
		*t1 = *t;
		t1->dot++;
	}
	qsort(i0.ts, i0.nt, sizeof i0.ts[0], tcmpv);
}

int
icmp(Item *a, Item *b)
{
	Term *ta, *tb, *ma, *mb;
	int c;

	ta = a->ts;
	tb = b->ts;
	ma = ta+a->nt;
	mb = tb+b->nt;
	for (;;) {
		if (ta==ma || ta->dot==0)
			return -(tb<mb && tb->dot);
		if (tb==mb || tb->dot==0)
			return +(ta<ma && ta->dot);
		if ((c=tcmp(ta++, tb++)))
			return c;
	}
}

int
stadd(Item **pi)
{
	Item *i, *i1;
	int lo, hi, mid, n, chg;

	/* http://www.iq0.com/duffgram/bsearch.c */
	i = *pi;
	lo = 0;
	hi = nst - 1;
	if (hi<0 || icmp(i, st[hi])>0)
		hi++;
	else if (icmp(i, st[lo])<=0)
		hi = lo;
	else
		while (hi-lo!=1) {
			mid = (lo+hi)/2;
			if (icmp(st[mid], i)<0)
				lo = mid;
			else
				hi = mid;
		}
	if (hi<nst && icmp(st[hi], i)==0) {
		chg = 0;
		i1 = st[hi];
		for (n=0; n<i->nt; n++)
			chg |= tsunion(&i1->ts[n].lk, &i->ts[n].lk);
		i1->dirty |= chg;
		*pi = i1;
		return chg;
	} else {
		st = realloc(st, ++nst * sizeof st[0]);
		if (!st)
			die("out of memory");
		memmove(&st[hi+1], &st[hi], (nst-1 - hi) * sizeof st[0]);
		i->gtbl = yalloc(nsy, sizeof i->gtbl[0]);
		i->dirty = 1;
		i1 = yalloc(1, sizeof *i1);
		*i1 = *i;
		*pi = st[hi] = i1;
		return 1;
	}
}

void
stgen()
{
	Sym s;
	Rule *r;
	Item *i, *i1;
	Term tini;
	int n, chg;

	ini = &i0;
	r = rfind(Sym0);
	tini.rule = r;
	tini.dot = 0;
	tszero(&tini.lk);
	SetBit(tini.lk.t, 0);
	i0.nt = 0;
	i0.ts[i0.nt++] = tini;
	stadd(&ini);
	do {
		chg = 0;
		for (n=0; n<nst; n++) {
			i = st[n];
			if (!i->dirty)
				continue;
			i->dirty = 0;
			iclose(i);
			for (s=0; s<nsy; s++) {
				igoto(i, s);
				i1 = &i0;
				if (!i1->nt) {
					i->gtbl[s] = 0;
					continue;
				}
				chg |= stadd(&i1);
				i->gtbl[s] = i1;
			}
		}
	} while (chg);
}

int
resolve(Rule *r, Sym s, int st)
{
	if (!r->prec || !is[s].prec) {
	conflict:
		if (fgrm)
			fprintf(fgrm, srs, st, is[s].name);
		srconf++;
		return ARight;
	}
	if (r->prec==is[s].prec) {
		if (is[s].assoc == ANone)
			goto conflict;
		return is[s].assoc;
	} else
		if (r->prec<is[s].prec)
			return ARight;
		else
			return ALeft;
}

void
tblset(int *tbl, Item *i, Term *t)
{
	int act;
	Sym s;

	s = t->rule->rhs[t->dot];
	if (s!=S) {
		/* shift */
		if (s>=ntk)
			return;
		assert(i->gtbl[s]);
		act = ARight;
		if (tbl[s] && tbl[s] != i->gtbl[s]->id) {
			assert(tbl[s]<=0);
			act = resolve(&rs[Red(tbl[s])], s, i->id-1);
		}
		switch (act) {
		case ARight:
			tbl[s] = i->gtbl[s]->id;
			break;
		case ANonassoc:
			tbl[s] = -1;
			break;
		}
	} else
		/* reduce */
		for (s=0; s<ntk; s++) {
			if (!GetBit(t->lk.t, s))
				continue;
			/* default to shift if conflict occurs */
			if (!tbl[s])
				act = ALeft;
			else if (tbl[s]<0) {
				if (fgrm)
					fprintf(fgrm, rrs, i->id-1, is[s].name);
				rrconf++;
				act = ARight;
			} else
				act = resolve(t->rule, s, i->id-1);
			switch (act) {
			case ALeft:
				tbl[s] = Red(t->rule-rs);
				break;
			case ANonassoc:
				tbl[s] = -1;
				break;
			}
		}
}

void
setdef(Row *r, int w, int top)
{
	int n, m, x, cnt, def, max;

	max = 0;
	def = -1;
	r->ndef = 0;
	for (n=0; n<w; n++) {
		x = r->t[n];
		if (x==0)
			r->ndef++;
		if (x>=top || x==0)
			continue;
		cnt = 1;
		for (m=n+1; m<w; m++)
			if (r->t[m]==x)
				cnt++;
		if (cnt>max) {
			def = x;
			max = cnt;
		}
	}
	r->def = def;
	if (max!=0)
		/* zero out the most frequent entry */
		for (n=0; n<w; n++)
			if (r->t[n]==def) {
				r->t[n] = 0;
				r->ndef++;
			}
}

void
tblgen()
{
	Row *r;
	Item *i;
	int n, m;

	for (n=0; n<nst; n++)
		st[n]->id = n+1;
	as = yalloc(nst, sizeof as[0]);
	gs = yalloc(nsy-MaxTk, sizeof gs[0]);
	/* fill action table */
	for (n=0; n<nst; n++) {
		r = &as[n];
		r->t = yalloc(ntk, sizeof r->t[0]);
		for (i=st[n], m=0; m<i->nt; m++)
			tblset(r->t, i, &i->ts[m]);
		setdef(r, ntk, -1);
		r->def = Red(r->def); /* Red(-1) == -1 */
	}
	/* fill goto table */
	for (n=MaxTk; n<nsy; n++) {
		r = &gs[n-MaxTk];
		r->t = yalloc(nst, sizeof r->t[0]);
		for (m=0; m<nst; m++)
			if (st[m]->gtbl[n])
				r->t[m] = st[m]->gtbl[n]->id;
		setdef(r, nst, nst+1);
	}
}

int
prcmp(const void *a, const void *b)
{
	return (*(Row **)a)->ndef - (*(Row **)b)->ndef;
}

void
actgen()
{
	Row **o, *r;
	int n, m, t, dsp, nnt;

	actsz = 0;
	o = yalloc(nst+nsy, sizeof o[0]);
	act = yalloc(nst*nsy, sizeof act[0]);
	chk = yalloc(nst*nsy, sizeof chk[0]);
	adsp = yalloc(nst, sizeof adsp[0]);
	for (n=0; n<nst*nsy; n++)
		chk[n] = -1;
	/* fill in actions */
	for (n=0; n<nst; n++)
		o[n] = &as[n];
	qsort(o, nst, sizeof o[0], prcmp);
	for (n=0; n<nst; n++) {
		r = o[n];
		dsp = 0;
		for (m=0; m<ntk && r->t[m]==0; m++)
			dsp--;
	retrya:
		/* The invariant here is even
		 * trickier than it looks.
		 */
		for (t=0; t<ntk; t++)
			if ((m=dsp+t)>=0 && chk[m]>=0)
			if ((r->t[t] && (chk[m]!=t || act[m]!=r->t[t]))
			|| (!r->t[t] && chk[m]==t)) {
				dsp++;
				goto retrya;
			}
		adsp[r-as] = dsp;
		for (t=0; t<ntk; t++)
			if (r->t[t]) {
				chk[dsp+t] = t;
				act[dsp+t] = r->t[t];
				if (dsp+t>=actsz)
					actsz = dsp+t+1;
			}
	}
	/* fill in gotos */
	nnt = nsy-MaxTk;
	gdsp = yalloc(nnt, sizeof gdsp[0]);
	for (n=0; n<nnt; n++)
		o[n] = &gs[n];
	qsort(o, nnt, sizeof o[0], prcmp);
	for (n=0; n<nnt; n++) {
		r = o[n];
		dsp = 0;
		for (m=0; m<nst && r->t[m]==0; m++)
			dsp--;
	retryg:
		for (t=m; t<nst; t++)
			if (chk[dsp+t]>=0 && r->t[t]) {
				dsp++;
				goto retryg;
			}
		gdsp[r-gs] = dsp;
		for (t=m; t<nst; t++)
			if (r->t[t]) {
				chk[dsp+t] = ntk+(r-gs);
				act[dsp+t] = r->t[t];
				if (dsp+t>=actsz)
					actsz = dsp+t+1;
			}
	}
	free(o);
}

void
aout(char *name, int *t, int n)
{
	int i;

	fprintf(fout, "short %s[] = {", name);
	for (i=0; i<n; i++) {
		if (i % 10 == 0)
			fprintf(fout, "\n");
		fprintf(fout, "%4d", t[i]);
		if (i != n-1)
			fprintf(fout, ",");
	}
	fprintf(fout, "\n};\n");
}

void
tblout()
{
	int *o, n, m;

	fprintf(fout, "short yyini = %d;\n", ini->id-1);
	fprintf(fout, "short yyntoks = %d;\n", ntk);
	o = yalloc(nrl+nst+nsy, sizeof o[0]);
	for (n=0; n<nrl; n++)
		o[n] = slen(rs[n].rhs);
	aout("yyr1", o, nrl);
	for (n=0; n<nrl; n++)
		o[n] = rs[n].lhs-MaxTk;
	aout("yyr2", o, nrl);
	for (n=0; n<nst; n++)
		o[n] = as[n].def;
	aout("yyadef", o, nst);
	for (n=0; n<nsy-MaxTk; n++) {
		o[n] = gs[n].def;
		assert(o[n]>0 || o[n]==-1);
		if (o[n]>0)
			o[n]--;
	}
	aout("yygdef", o, nsy-MaxTk);
	aout("yyadsp", adsp, nst);
	aout("yygdsp", gdsp, nsy-MaxTk);
	for (n=0; n<actsz; n++)
		if (act[n]>=0)
			act[n]--;
	aout("yyact", act, actsz);
	aout("yychk", chk, actsz);
	for (n=0; n<128; n++) {
		o[n] = 0;
		for (m=0; m<ntk; m++)
			if (is[m].name[0]=='\'')
			if (is[m].name[1]==n)
				assert(!o[n]), o[n] = m;
	}
	m = 128;
	for (n=1; n<ntk; n++) {
		if (is[n].name[0]=='\'')
			continue;
		fprintf(fout, "#define %s %d\n", is[n].name, m);
		if (fhdr)
			fprintf(fhdr, "#define %s %d\n", is[n].name, m);
		o[m++] = n;
	}
	aout("yytrns", o, m);
	if (fhdr) {
		fputs("int yyparse(void);\n", fhdr);
		fputs("#ifndef YYSTYPE\n", fhdr);
		fputs("#define YYSTYPE int\n", fhdr);
		fputs("#endif\n", fhdr);
		fputs("extern YYSTYPE yylval;\n", fhdr);
		fputs("#endif\n", fhdr);
	}
	free(o);
}

void
stdump()
{
	Term *t;
	Sym *s1;
	int n, m, d, act;
	Rule *r;
	Row *ar;

	if (!fgrm)
		return;
	for (r=rs; r-rs<nrl; r++) {
		fprintf(fgrm, "\n%03d: %s ->", (int)(r-rs), is[r->lhs].name);
		for (s1=r->rhs; *s1!=S; s1++)
			fprintf(fgrm, " %s", is[*s1].name);
	}
	fprintf(fgrm, "\n");
	for (m=0; m<nst; m++) {
		fprintf(fgrm, "\nState %d:\n", m);
		for (t=st[m]->ts; t-st[m]->ts<st[m]->nt; t++) {
			r = t->rule;
			d = t->dot;
			if (d==0 && t!=st[m]->ts)
				continue;
			fprintf(fgrm, "  %s ->", is[r->lhs].name);
			for (s1=r->rhs; *s1!=S; s1++, d--)
				fprintf(fgrm, " %s%s", d ? "" : ". ", is[*s1].name);
			if (!d)
				fprintf(fgrm, " .");
			fprintf(fgrm, "\n");
		}
		fprintf(fgrm, "\n");
		ar = &as[m];
		for (n=0; n<ntk; n++) {
			act = ar->t[n];
			if (!act)
				continue;
			if (act==-1)
				fprintf(fgrm, "  %s error (nonassoc)\n", is[n].name);
			else if (act<0)
				fprintf(fgrm, "  %s reduce with rule %d\n", is[n].name, Red(act));
			else
				fprintf(fgrm, "  %s shift and go to %d\n", is[n].name, act-1);
		}
		if (ar->def != -1)
			fprintf(fgrm, "  * reduce with rule %d\n", ar->def);
	}
}

enum {
	TIdnt,
	TTokchr, /* 'c' */
	TPP, /* %% */
	TLL, /* %{ */
	TLangle, /* < */
	TRangle, /* > */
	TSemi, /* ; */
	TBar, /* | */
	TColon, /* : */
	TLBrack, /* { */
	TUnion,
	TType,
	TToken,
	TRight,
	TLeft,
	TNonassoc,
	TPrec,
	TStart,
	TEof
};

struct {
	char *name;
	int tok;
} words[] = {
	{ "%%", TPP },
	{ "%union", TUnion },
	{ "%type", TType },
	{ "%token", TToken },
	{ "%right", TRight },
	{ "%left", TLeft },
	{ "%nonassoc", TNonassoc },
	{ "%prec", TPrec },
	{ "%start", TStart },
	{ 0, 0 }
};

char idnt[IdntSz];

int
istok(int c)
{
	return isalnum(c) || c=='_' || c=='%';
}

int
nexttk()
{
	int n;
	char c, *p;

	while (isspace(c=fgetc(fin)))
		if (c == '\n')
			lineno++;
	switch (c) {
	case '<':
		return TLangle;
	case '>':
		return TRangle;
	case ';':
		return TSemi;
	case '|':
		return TBar;
	case ':':
		return TColon;
	case '{':
		return TLBrack;
	case EOF:
		return TEof;
	case '\'':
		idnt[0] = '\'';
		idnt[1] = fgetc(fin);
		idnt[2] = '\'';
		idnt[3] = 0;
		if (fgetc(fin)!='\'')
			die("syntax error, invalid char token");
		return TTokchr;
	}
	p = idnt;
	while (istok(c)) {
		*p++ = c;
		if (p-idnt >= IdntSz-1)
			die("identifier too long");
		c = fgetc(fin);
	}
	*p = 0;
	if (strcmp(idnt, "%")==0)
	if (c=='{')
		return TLL;
	ungetc(c, fin);
	for (n=0; words[n].name; n++)
		if (strcmp(idnt, words[n].name) == 0)
			return words[n].tok;
	return TIdnt;
}

char *
cpycode()
{
	int c, nest, in, len, pos;
	char *s;

	len = 64;
	s = yalloc(len+1, 1);
	s[0] = '{';
	pos = 1;
	nest = 1;
	in = 0;

	while (nest) {
		c = fgetc(fin);
		if (in) {
			if (c == in)
			if (s[pos-1] != '\\')
				in = 0;
		} else {
			if (c == '"' || c == '\'')
				in = c;
			if (c == '{')
				nest++;
			if (c == '}')
				nest--;
			if (c == EOF)
				die("syntax error, unclosed code block");
			if (c == '\n')
				lineno++;
		}
		if (pos>=len)
		if (!(s=realloc(s, len=2*len+1)))
			die("out of memory");
		s[pos++] = c;
	}
	s[pos] = 0;
	return s;
}

int
gettype(char *type)
{
	int tk;

	tk = nexttk();
	if (tk==TLangle) {
		if (nexttk()!=TIdnt)
			die("syntax error, ident expected after <");
		strcpy(type, idnt);
		if (nexttk()!=TRangle)
			die("syntax error, unclosed <");
		return nexttk();
	} else {
		type[0] = 0;
		return tk;
	}
}

Sym
findsy(char *name, int add)
{
	int n;

	for (n=0; n<nsy; n++) {
		if (n == ntk) {
			if (name[0]=='\'') {
				if (ntk>=MaxTk)
					die("too many tokens");
				ntk++;
				strcpy(is[n].name, name);
				return n;
			}
			n = MaxTk;
		}
		if (strcmp(is[n].name, name)==0)
			return n;
	}
	if (add) {
		if (nsy>=MaxTk+MaxNt)
			die("too many non-terminals");
		strcpy(is[nsy].name, name);
		return nsy++;
	} else
		return nsy;
}

void
getdecls()
{
	int tk, prec, p, a, c, c1, n;
	Info *si;
	char type[IdntSz], *s;

	strcpy(is[0].name, "$");
	ntk = 1;
	strcpy(is[Sym0].name, "@start");
	nsy = MaxTk+1;
	sstart = S;
	prec = 0;
	tk = nexttk();
	for (;;)
	switch (tk) {
	case TStart:
		tk = nexttk();
		if (tk!=TIdnt)
			die("syntax error, ident expected after %start");
		sstart = findsy(idnt, 1);
		if (sstart<ntk)
			die("%start cannot specify a token");
		tk = nexttk();
		break;
	case TUnion:
		tk = nexttk();
		if (tk!=TLBrack)
			die("syntax error, { expected after %union");
		fprintf(fout, "#line %d \"%s\"\n", lineno, srca);
		s = cpycode();
		fprintf(fout, "typedef union %s yyunion;\n", s);
		fprintf(fout, "#define YYSTYPE yyunion\n");
		if (fhdr) {
			fprintf(fhdr, "typedef union %s yyunion;\n", s);
			fprintf(fhdr, "#define YYSTYPE yyunion\n");
		}
		free(s);
		doty = 1;
		tk = nexttk();
		break;
	case TLeft:
		p = ++prec;
		a = ALeft;
		goto addtoks;
	case TRight:
		p = ++prec;
		a = ARight;
		goto addtoks;
	case TNonassoc:
		p = ++prec;
		a = ANonassoc;
		goto addtoks;
	case TToken:
		p = 0;
		a = ANone;
	addtoks:
		tk = gettype(type);
		while (tk==TIdnt || tk==TTokchr) {
			si = 0;
			n = findsy(idnt, 0);
			if (n>=MaxTk && n<nsy)
				die("non-terminal redeclared as token");
			if (n==nsy) {
				if (ntk>=MaxTk)
					die("too many tokens");
				n = ntk++;
			}
			si = &is[n];
			strcpy(si->name, idnt);
			strcpy(si->type, type);
			si->prec = p;
			si->assoc = a;
			tk = nexttk();
		}
		break;
	case TType:
		tk = gettype(type);
		if (type[0]==0)
			die("syntax error, type expected");
		while (tk==TIdnt) {
			si = 0;
			n = findsy(idnt, 1);
			if (n<ntk)
				die("token redeclared as non-terminal");
			if (n==nsy) {
				nsy++;
			}
			si = &is[n];
			strcpy(si->name, idnt);
			strcpy(si->type, type);
			tk = nexttk();
		}
		break;
	case TLL:
		fprintf(fout, "#line %d \"%s\"\n", lineno, srca);
		for (;;) {
			c = fgetc(fin);
			if (c == EOF)
				die("syntax error, unclosed %{");
			if (c == '%') {
				c1 = fgetc(fin);
				if (c1 == '}') {
					fputs("\n", fout);
					break;
				}
				ungetc(c1, fin);
			}
			if (c == '\n')
				lineno++;
			fputc(c, fout);
		}
		tk = nexttk();
		break;
	case TPP:
		return;
	case TEof:
		die("syntax error, unfinished declarations");
	default:
		die("syntax error, declaration expected");
	}
}

void
getgram()
{
	extern char *retcode;
	int tk;
	Sym hd, *p, s;
	Rule *r;

	for (;;) {
		tk = nexttk();
		if (tk==TPP || tk==TEof) {
			if (sstart==S)
				die("syntax error, empty grammar");
			r = &rs[nrl++];
			r->lhs = Sym0;
			r->rhs[0] = sstart;
			r->rhs[1] = 0;
			r->rhs[2] = S;
			r->act = retcode;
			qsort(rs, nrl, sizeof rs[0], rcmp);
			return;
		}
		if (tk!=TIdnt)
			die("syntax error, production rule expected");
		if (nexttk()!=TColon)
			die("syntax error, colon expected after production's head");
		hd = findsy(idnt, 1);
		if (sstart==S)
			sstart = hd;
		do {
			if (nrl>=MaxRl-1)
				die("too many rules");
			r = &rs[nrl++];
			r->lhs = hd;
			r->act = 0;
			p = r->rhs;
			while ((tk=nexttk())==TIdnt || tk==TTokchr || tk==TPrec) {
				if (tk==TPrec) {
					tk = nexttk();
					if (tk!=TIdnt
					|| (s=findsy(idnt, 0))>=ntk)
						die("token expected after %prec");
					r->prec = is[s].prec;
					continue;
				}
				s = findsy(idnt, 1);
				*p++ = s;
				if (s<ntk && is[s].prec>0)
					r->prec = is[s].prec;
				if (p-r->rhs >= MaxRhs-1)
					die("production rule too long");
			}
			*p = S;
			if (tk==TLBrack) {
				r->actln = lineno;
				r->act = cpycode();
				tk = nexttk();
			}
		} while (tk==TBar);
		if (tk!=TSemi)
			die("syntax error, ; or | expected");
	}
}

void
actout(Rule *r)
{
	long l;
	int i, ar;
	char c, *p, *ty, tya[IdntSz];

	ar = slen(r->rhs);
	p = r->act;
	i = r->actln;
	if (!p)
		return;
	while ((c=*p++))
	switch (c) {
	case '\n':
		i++;
	default:
		fputc(c, fout);
		break;
	case '$':
		c = *p++;
		if (c == '$') {
			fprintf(fout, "yyval");
			if (doty) {
				ty = is[r->lhs].type;
				if (!ty[0]) {
					lineno = i;
					die("$$ has no type");
				}
				fprintf(fout, ".%s", ty);
			}
		}
		else if (c == '<') {
			ty = tya;
			while (istok(*p) && ty-tya<IdntSz-1)
				*ty++ = *p++;
			*ty = 0;
			if (*p++!='>') {
				lineno = i;
				die("unclosed tag field");
			}
			ty = tya;
			c = *p++;
			if (c == '$') {
				fprintf(fout, "yyval.%s", ty);
			} else {
				if (!isdigit(c)) {
					lineno = i;
					die("number or $ expected afer tag field");
				}
				goto readnum;
			}
		}
		else if (isdigit(c)) {
			ty = 0;
		readnum:
			l = strtol(p-1, &p, 10);
			if (l > ar) {
				lineno = i;
				die("invalid $n");
			}
			fprintf(fout, "ps[%d].val", (int)l);
			if (doty) {
				if (!ty && l>0)
					ty = is[r->rhs[l-1]].type;
				if (!ty || !ty[0]) {
					lineno = i;
					die("$n has no type");
				}
				fprintf(fout, ".%s", ty);
			}
		}
		else {
			fputc('$', fout);
			fputc(c, fout);
		}
	}
	fputs("\n", fout);
}

void
codeout()
{
	extern char *code0[], *code1[];
	char **p;
	Rule *r;
	int n, c;

	for (p=code0; *p; p++)
		fputs(*p, fout);
	for (n=0; n<nrl; n++) {
		fprintf(fout, "\tcase %d:\n", n);
		r = &rs[n];
		fprintf(fout, "#line %d \"%s\"\n", r->actln, srca);
		actout(r);
		fputs("\t\tbreak;\n", fout);
	}
	for (p=code1; *p; p++)
		fputs(*p, fout);
	fprintf(fout, "#line %d \"%s\"\n", lineno, srca);
	while ((c=fgetc(fin))!=EOF)
		fputc(c, fout);
}

void
init(int ac, char *av[])
{
	int c, vf, df;
	char *pref, buf[100], *opt;

	(void) ac;
	pref = "y";
	vf = df = 0;
	for (av++; av[0] && av[0][0]=='-'; av++)
		for (opt = &av[0][1]; (c = *opt); opt++)
			switch (c) {
			case 'v':
				vf = 1;
				break;
			case 'd':
				df = 1;
				break;
			case 'b':
				if ((pref = *++av))
					break;
			default:
			usage:
				fputs("usage: myacc [-vd] [-b file_prefix] grammar\n", stderr);
				exit(1);
			}

	if (!(srca = *av))
		goto usage;
	fin = fopen(srca, "r");
	if (strlen(pref) + 10 > sizeof buf)
		die("-b prefix too long");
	sprintf(buf, "%s.tab.c", pref);
	fout = fopen(buf, "w");
	if (vf) {
		sprintf(buf, "%s.output", pref);
		fgrm = fopen(buf, "w");
	}
	if (df) {
		sprintf(buf, "%s.tab.h", pref);
		fhdr = fopen(buf, "w");
		if (fhdr) {
			fprintf(fhdr, "#ifndef Y_TAB_H_\n");
			fprintf(fhdr, "#define Y_TAB_H_\n");
		}
	}
	if (!fin || !fout || (!fgrm && vf) || (!fhdr && df))
		die("cannot open work files");
}


//========================
// miniyacc_main
//

int miniyacc_main(int ac, char *av[]) {

	init(ac, av);
	getdecls();
	getgram();
	ginit();
	stgen();
	tblgen();
	stdump();
	actgen();
	tblout();
	codeout();

	if (srconf)
		fprintf(stderr, "%d shift/reduce conflicts\n", srconf);
	if (rrconf)
		fprintf(stderr, "%d reduce/reduce conflicts\n", rrconf);

	exit(0);
}

/* Glorious macros.
	|sed 's|.*|"&\\n",|'
*/

char *retcode = "\t\tyyval = ps[1].val; return 0;";

char *code0[] = {
"\n",
"#ifndef YYSTYPE\n",
"#define YYSTYPE int\n",
"#endif\n",
"YYSTYPE yylval;\n",
"\n",
"int\n",
"yyparse()\n",
"{\n",
"	enum {\n",
"		StackSize = 100,\n",
"		ActSz = sizeof yyact / sizeof yyact[0],\n",
"	};\n",
"	struct {\n",
"		YYSTYPE val;\n",
"		int state;\n",
"	} stk[StackSize], *ps;\n",
"	int r, h, n, s, tk;\n",
"	YYSTYPE yyval;\n",
"\n",
"	ps = stk;\n",
"	ps->state = s = yyini;\n",
"	tk = -1;\n",
"loop:\n",
"	n = yyadsp[s];\n",
"	if (tk < 0 && n > -yyntoks)\n",
"		tk = yytrns[yylex()];\n",
"	n += tk;\n",
"	if (n < 0 || n >= ActSz || yychk[n] != tk) {\n",
"		r = yyadef[s];\n",
"		if (r < 0)\n",
"			return -1;\n",
"		goto reduce;\n",
"	}\n",
"	n = yyact[n];\n",
"	if (n == -1)\n",
"		return -1;\n",
"	if (n < 0) {\n",
"		r = - (n+2);\n",
"		goto reduce;\n",
"	}\n",
"	tk = -1;\n",
"	yyval = yylval;\n",
"stack:\n",
"	ps++;\n",
"	if (ps-stk >= StackSize)\n",
"		return -2;\n",
"	s = n;\n",
"	ps->state = s;\n",
"	ps->val = yyval;\n",
"	goto loop;\n",
"reduce:\n",
"	ps -= yyr1[r];\n",
"	h = yyr2[r];\n",
"	s = ps->state;\n",
"	n = yygdsp[h] + s;\n",
"	if (n < 0 || n >= ActSz || yychk[n] != yyntoks+h)\n",
"		n = yygdef[h];\n",
"	else\n",
"		n = yyact[n];\n",
"	switch (r) {\n",
0
};

char *code1[] = {
"	}\n",
"	goto stack;\n",
"}\n",
0
};







//===============================================================================
// mini yacc end
//===============================================================================


struct node 
{ 
	int key; 
	struct node *left, *right; 
}; 

// A utility function to create a new BST node 
struct node *newNode(int item) 
{ 
	struct node *temp = (struct node *)malloc(sizeof(struct node)); 
	temp->key = item; 
	temp->left = temp->right = NULL; 
	return temp; 
} 

// A utility function to do inorder traversal of BST 
void inorder(struct node *root) 
{ 
	if (root != NULL) 
	{ 
		inorder(root->left); 
		printf("%d \n", root->key); 
		inorder(root->right); 
	} 
} 


//Em ordem
void exibirEmOrdem(struct node *root){
    if(root != NULL){
        exibirEmOrdem(root->left);
        printf("%d ", root->key);
        exibirEmOrdem(root->right);
    }
}



//Pré-ordem
void exibirPreOrdem(struct node *root){
    if(root != NULL){
        printf("%d ", root->key);
        exibirPreOrdem(root->left);
        exibirPreOrdem(root->right);
    }
}


//Pós-ordem
void exibirPosOrdem(struct node *root){
    if(root != NULL){
        exibirPosOrdem(root->left);
        exibirPosOrdem(root->right);
        printf("%d ", root->key);
    }
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key) 
{ 
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key); 

	/* Otherwise, recur down the tree */
	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 

	/* return the (unchanged) node pointer */
	return node; 
} 


// Driver Program to test above functions 
// C program to demonstrate insert operation in binary search tree 
int bst_main() 
{ 
	/* Let us create following BST 
           50 
          /  \ 
        30    70 
        / \   / \ 
       20 40 60 80 */
	
	struct node *root = NULL; 
	
	root = insert ( root, 50 ); 
	
	insert(root, 30); 
	insert(root, 20); 
	insert(root, 40); 
	insert(root, 70); 
	insert(root, 60); 
	insert(root, 80); 

	// print inoder traversal of the BST 
	//inorder(root); 
	
	printf("\n\n");
	printf("[50 30 20 40 70 60 80]");
	printf("\n\n");
	
	printf("\n\n em ordem: \n");
	exibirEmOrdem(root);
	
	printf("\n\n pre ordem: \n");
	exibirPreOrdem(root);
	
	printf("\n\n pos ordem: \n");
	exibirPosOrdem(root);

	printf("\n\n");
	
	return 0; 
}; 


//===============================================================================




//
// Variáveis internas.
//

//Idle application support.
int idleStatus;
int idleError;
//...

//Idle driver support.
int driverInitialized;
//...


/*
struct idle
{
	struct thread_d *current_idle_thread;
	//int
}
*/

//
// Protótipos.
//
int TEST_PRINTF(void);
int TEST_PRINTF2(void);
int TEST_PRINTF3(void);

void idleLoop();
void driverInitialize();      // processo sendo considerado um driver servidor.
void driverUninitialize();    // desinicializa.
int idleInit();               // processo sendo consideredo cliente.
unsigned long idleServices(unsigned long number);  //Principal.
//...




//Another loop.
void idleLoop(){
    while(1){}	
};

 




/*
 * driverInitialize:
 *     O Kernel solicitou a rotina de inicialização do processo Idle na forma 
 * de driver. Faremos uma chamada ao Kernel dizendo que o driver está 
 * inicializado. Na chamada passaremos alguns parâmetros, como: O número do 
 * serviço, 129 e o código de confirmação, 1234. 4321.
 *
 */
void driverInitialize()
{
	//printf("Idle: Initializing driver ...\n");
	//refresh_screen();

	driverInitialized = 1;	
	//system_call( 129, 4321, 4321, 4321 );	
	
done:	
	printf("IDLE.BIN: Initialized.\n");
	refresh_screen();
	return;
};


/*
 * driverUninitialize:
 *     This method is called to uninitialize the driver object. In a real 
 * driver, this is where the driver would clean up any resources held by 
 * this driver. (m$)
 */
void driverUninitialize()
{
	//
	// Dúvidas??
	// Devemos nos preparar para desinicializar o driver.
	// Desalocaremos os recursos usadados pelo driver, como memória, 
	// arquivos abertos ...
	// Obs: Não sei se atribuição do próprio driver liberar os recursos.
	// Mas de toda forma, no mínimo devemos avisar o Kernel que os recursos 
	// não são mais necessários.
	// @todo: Podemos enviar um comando para o kernel pedindo pra que ele não 
	// link esse driver ao sistema, ou que deixe ele não inicializado.
	//

	//printf("Idle: Unitializing driver ...\n");
	//refresh_screen();

	driverInitialized = 0;	
	
	//Faremos uma chamada para o Kernel 'deslinkar' o driver.
	//talvez 128. 127 126..???
	//system_call( ?? , 4321, 4321, 4321 ); 		
	
done:	
	printf("IDLE.BIN: Uninitialized.\n");
	refresh_screen();
	return;
};


/*
 * idleInit:
 *     Inicializando a aplicação Idle.
 */
int idleInit()
{
	idleStatus = 0;
	idleError = 0;
	
	//printf("Idle: Initializing idle application ..\n");
	//refresh_screen();
	//...
	return (int) 0;
};


/*
 *****************************************************************************
 * idleServices:
 *     Essa função oferece serviços de acordo com o número passado via 
 * argumento.
 * Essa deve ficar por último e ter acesso à qualquer rotina acima ou em
 * bibliotecas incluídas.
 */
unsigned long idleServices(unsigned long number)
{
    // Checar se o driver está inicializado.
	if(driverInitialized != 1){
		return (unsigned long) 1;    //erro
	}
	
	
	//
	// Selecionar o serviço.
	//
	
    switch(number)
    {
		case 0:
		    printf("Idle Driver: NULL service.\n");
		    idleLoop();
			break;
			
		case 1:
		    printf("Idle Driver: service 1.\n");
		    //idleLoop();
			break;

        //...			
		
		default:
		    printf("Idle Driver: default service.\n");        
			//idleLoop();
			break;
	};	
	
	
done:
    refresh_screen(); 
    return (unsigned long) 0;	
};



/*
 ==================================================================================
 * iNICIALIZAÇÃO GENÉRICA PARA TESTE DE APLICATIVO.
 */

int testtest_main (){
	
	printf("\n");
	printf("Initilizing TBST.BIN ...\n\n");
	
	
    libcInitRT();
    stdioInitialize();		

	bst_main(); 
	 
	/*
	if ( isxdigit('a') )
	{
		printf("isxdigit a\n");
	}
	
	if ( isxdigit('f') )
	{
		printf("isxdigit f\n");
	}

	if ( isxdigit('0') )
	{
		printf("isxdigit 0\n");
	}

	if ( isxdigit('9') )
	{
		printf("isxdigit 9\n");
	}	
	*/
	
	
	/*
	if ( isalpha('a') )
	{
		printf("isalpha a\n");
	}
	
	if ( isalpha('z') )
	{
		printf("isalpha z\n");
	}

	if ( isalpha('A') )
	{
		printf("isalpha A\n");
	}

	if ( isalpha('Z') )
	{
		printf("isalpha Z\n");
	}	
	*/
	
	//isalnum(int c)
	
	/*
	if ( isalnum('a') )
	{
		printf("isalnum a\n");
	}
	
	if ( isalnum('z') )
	{
		printf("isalnum z\n");
	}

	if ( isalnum('0') )
	{
		printf("isalnum 0\n");
	}

	if ( isalnum('9') )
	{
		printf("isalnum 9\n");
	}
	*/
	
	//#todo 
	//vamos fazer rotinas de teste nas funções 
	//de ctype.h na libc do Gramado 0.4
	
	

	
	
	/*
	printf("\n");
	printf("===============\n");
	printf("Testando printf, printf nao tradicional\n");	
	TEST_PRINTF();
    	
	//printf("\n");	
	//printf("===============\n");
	//printf("Testando printf2, printf tradicional\n");	
	//TEST_PRINTF2();	 
	
	printf("\n");	
	printf("===============\n");
	printf("Testando printf3, printf tradicional \n");	
	TEST_PRINTF3();	

    */ 	
	
	printf("DONE.");	
	refresh_screen();
	return 0;
};




/*
 * TEST_PRINTF2:
 *     Essa função testa a função printf() e seus recursos.
 *     Obs: We can implement this test in user mode.
 * Obs:
 *     If you compile this file with
 *     gcc -Wall $(YOUR_C_OPTIONS) -DTEST_PRINTF -c printf.c
 * you will get a normal warning:
 *   printf.c:214: warning: spurious trailing `%' in format
 * this line is testing an invalid % at the end of the format string.
 *
 * this should display (on 32bit int machine) :
 *
 * Hello world!
 * printf test
 * (null) is null pointer
 * 5 = 5
 * -2147483647 = - max int
 * char a = 'a'
 * hex ff = ff
 * hex 00 = 00
 * signed -3 = unsigned 4294967293 = hex fffffffd
 * 0 message(s)
 * 0 message(s) with %
 * justif: "left      "
 * justif: "     right"
 *  3: 0003 zero padded
 *  3: 3    left justif.
 *  3:    3 right justif.
 * -3: -003 zero padded
 * -3: -3   left justif.
 * -3:   -3 right justif.
 *
 */
	
	
	
//testando 
//não tradicional, mas funciona.

int TEST_PRINTF(void)
{


	
	int mi;
	int i = 5;
	unsigned int bs = sizeof(int)*8;

	char *np = 0;	
	char *ptr = "Hello world!";
	char buf[80];
	
	

	mi = (1 << (bs-1)) + 1;
	
//	vsync();
	
	printf("%s\n", ptr);
	printf("printf test\n");
	printf("%s is null pointer\n", np);
	printf("%d = 5\n", i);
	printf("%d = - max int\n", mi);
	printf("char %c = 'a'\n", 'a');
	printf("hex %x = ff\n", 0xff);
	printf("hex %02x = 00\n", 0);
	printf("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf("%d %s(s)%", 0, "message");
	printf("\n");
	printf("%d %s(s) with %%\n", 0, "message");
	
    sprintf(buf, "justif: \"%-10s\"\n", "left"); 
    printf("%s", buf);
	
    sprintf(buf, "justif: \"%10s\"\n", "right"); 
    printf("%s", buf);
	
    sprintf(buf, " 3: %04d zero padded\n", 3); 
    printf("%s", buf);
	
    sprintf(buf, " 3: %-4d left justif.\n", 3); 
    printf("%s", buf);
	
    sprintf(buf, " 3: %4d right justif.\n", 3); 
    printf("%s", buf);
	
    sprintf(buf, "-3: %04d zero padded\n", -3); 
    printf("%s", buf);
	
    sprintf(buf, "-3: %-4d left justif.\n", -3); 
    printf("%s", buf);
	
    sprintf(buf, "-3: %4d right justif.\n", -3); 
    printf("%s", buf);


done:
	return (int) 0;
};



/*
 * TEST_PRINTF:
 *     Essa função testa a função printf() e seus recursos.
 *     Obs: We can implement this test in user mode.
 * Obs:
 *     If you compile this file with
 *     gcc -Wall $(YOUR_C_OPTIONS) -DTEST_PRINTF -c printf.c
 * you will get a normal warning:
 *   printf.c:214: warning: spurious trailing `%' in format
 * this line is testing an invalid % at the end of the format string.
 *
 * this should display (on 32bit int machine) :
 *
 * Hello world!
 * printf test
 * (null) is null pointer
 * 5 = 5
 * -2147483647 = - max int
 * char a = 'a'
 * hex ff = ff
 * hex 00 = 00
 * signed -3 = unsigned 4294967293 = hex fffffffd
 * 0 message(s)
 * 0 message(s) with %
 * justif: "left      "
 * justif: "     right"
 *  3: 0003 zero padded
 *  3: 3    left justif.
 *  3:    3 right justif.
 * -3: -003 zero padded
 * -3: -3   left justif.
 * -3:   -3 right justif.
 *
 */
	
 //testando a tradicional, incompleta
//não funciona, estamos implementando. 
int TEST_PRINTF2(void)
{


	
	int mi;
	int i = 5;
	unsigned int bs = sizeof(int)*8;

	char *np = 0;	
	char *ptr = "Hello world!";
	char buf[80];
	
	

	mi = (1 << (bs-1)) + 1;
	
//	vsync();
	
	printf2("%s\n", ptr);
	printf2("printf test\n");
	printf2("%s is null pointer\n", np);
	printf2("%d = 5\n", i);
	printf2("%d = - max int\n", mi);
	printf2("char %c = 'a'\n", 'a');
	printf2("hex %x = ff\n", 0xff);
	
	/*
	//podemos cancelar esse teste
	printf2("hex %02x = 00\n", 0);
	
	printf2("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf2("%d %s(s)%", 0, "message");
	printf2("\n");
	printf2("%d %s(s) with %%\n", 0, "message");
	
    sprintf(buf, "justif: \"%-10s\"\n", "left"); 
    printf2("%s", buf);
	
    sprintf(buf, "justif: \"%10s\"\n", "right"); 
    printf2("%s", buf);
	
    sprintf(buf, " 3: %04d zero padded\n", 3); 
    printf2("%s", buf);
	
    sprintf(buf, " 3: %-4d left justif.\n", 3); 
    printf2("%s", buf);
	
    sprintf(buf, " 3: %4d right justif.\n", 3); 
    printf2("%s", buf);
	
    sprintf(buf, "-3: %04d zero padded\n", -3); 
    printf2("%s", buf);
	
    sprintf(buf, "-3: %-4d left justif.\n", -3); 
    printf2("%s", buf);
	
    sprintf(buf, "-3: %4d right justif.\n", -3); 
    printf2("%s", buf);
    */

done:
	return (int) 0;
};



int TEST_PRINTF3(void)
{


	
	int mi;
	int i = 5;
	unsigned int bs = sizeof(int)*8;

	char *np = 0;	
	char *ptr = "Hello world!";
	char buf[80];
	
	

	mi = (1 << (bs-1)) + 1;
	
//	vsync();
	
	printf3("%s\n", ptr);
	printf3(" _(string 1 2 3 4)_ \n");
	printf3("%s is null pointer\n", np);
	
	
	printf3("%d = 5\n", i);
	printf3("%d = - max int\n", mi);
	printf3("char %c = 'a'\n", 'a');
	printf3("hex %x = ff\n", 0xff);
	printf3("hex %02x = 00\n", 0);
	printf3("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf3("%d %s(s)%", 0, "message");
	printf3("\n");
	printf3("%d %s(s) with %%\n", 0, "message");
	
    sprintf(buf, "justif: \"%-10s\"\n", "left"); 
    printf3("%s", buf);
	
    sprintf(buf, "justif: \"%10s\"\n", "right"); 
    printf3("%s", buf);
	
    sprintf(buf, " 3: %04d zero padded\n", 3); 
    printf3("%s", buf);
	
    sprintf(buf, " 3: %-4d left justif.\n", 3); 
    printf3("%s", buf);
	
    sprintf(buf, " 3: %4d right justif.\n", 3); 
    printf3("%s", buf);
	
    sprintf(buf, "-3: %04d zero padded\n", -3); 
    printf3("%s", buf);
	
    sprintf(buf, "-3: %-4d left justif.\n", -3); 
    printf3("%s", buf);
	
    sprintf(buf, "-3: %4d right justif.\n", -3); 
    printf3("%s", buf);

done:
	return (int) 0;
};


//
// End.
//

