#include "FundamentalCyclesFinder.h"

void Graph::FundamentalCyclesFinder::Save(int start, int end)
{
	cycle s;
	int i = start;
	while (i != end)
	{
		s.c.push_back(ftr[i]);
	}
	sol->insert(s);
}

void Graph::FundamentalCyclesFinder::findProc(int vnum)
{
	++depth;
//	stk.push_back(vnum);
	used[vnum] = depth;
	for (auto it : (*gr)[vnum])
	{
		if (used[it.to] == -1)
		{
			ftr[it.to] = vnum;
			findProc(it.to);
		}
		else if (ftr[vnum] == it.to && used[vnum]>used[it.to])
		{
			Save(vnum, it.to);
		}
	}

//	stk.pop_back();
}

void Graph::FundamentalCyclesFinder::run(T_Graph &G, set<cycle>& fc)
{
	gr = &G;
	ftr.resize(gr->size());
	used.resize(gr->size());
	for (int i = 0; i < used.size(); ++i)
	{
		used[i] = -1;
		ftr[i] = -1;
	}
	findProc(0);
}

procedure Init(var yes : Boolean);
{ Переназначение меток вершин }
{ их порядковыми номерами в списке смежности }
{ yes - признак правильной структуры списка смежности }
var
i, j, m :Integer;
begin
for i: = 1 to n do
for j : = 1 to Nbr[i] do
begin
yes : = FALSE;
for m: = 1 to n do
if Adj[Fst[i] + j] = Vtx[m] then
begin
yes : = TRUE;
Adj[Fst[i] + j] : = m;
break;
end;
if Not yes then exit;
end;
end;

procedure PrintCycle(x:Integer;
var C : TypeVertex;
nC:Integer); {Печать цикла из стека}
begin
Write(f, jC, ')');
repeat
Write(f, Vtx[C[nC]]:3);
nC: = nC - 1;
until C[nC] = x;
Writeln(f);
end;

procedure Cycle(x, y:Integer);
var
i, v : Integer;
begin
count : = count + 1;
Mark[x]: = count;
for i: = 1 to Nbr[x] do
begin
v : = Adj[Fst[x] + i];
nC: = nC + 1;
C[nC]: = v;
if Mark[v] = 0 then
Cycle(v, x)
else
if (Mark[v]<Mark[x]) And(v<>y) then
	begin
{
	Обратное ребро в пройденную вершину - найден цикл
}
jC: = jC + 1;
PrintCycle(v, C, nC);
end;
nC: = nC - 1;
end;
end;


procedure DepthCycle;
{Проход в глубину за циклами}
var
v : Integer;
begin
jC : = 0; {Счетчик числа циклов}
nC: = 0; {С - стек циклов пустой }
count: = 0; {Номер метки вершины}
for v: = 1 to n do Mark[v] : = 0;
for v: = 1 to n do
if Mark[v] = 0 then
begin
nC : = nC + 1;
C[nC] : = v;
Cycle(v, 0);
nC: = nC - 1;
end;
end;

var{ Main }
i, j : Integer;
yes: Boolean;
begin{ Main }
Assign(f, 'Cycle.in');
Reset(f); {Файл открыт для чтения}
{Ввод списка смежности}
Read(f, n); {Количество строк в списке}
Fst[1] : = 0; {Указатель начала первой строки списка}
for i: = 1 to n do
begin
Read(f, Vtx[i]); {Метка вершины}
Read(f, Nbr[i]); {Количество вершин в списке}
for j: = 1 to Nbr[i] do
Read(f, Adj[Fst[i] + j]);
{Список смежных вершин}
Fst[i + 1]: = Fst[i] + Nbr[i]; {Указатель начала следующей строки в списке}
end;
Close(f);
Assign(f, 'Cycle.out');
Rewrite(f); {Файл открыт для записи}
Init(yes);
if Not yes then
begin
WriteLn(f, 'Плохая структура смежности графа!');
Close(f);
exit;
end;
DepthCycle;
Close(f);
end. {Main}
