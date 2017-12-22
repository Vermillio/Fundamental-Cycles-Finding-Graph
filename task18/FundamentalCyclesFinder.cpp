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
{ �������������� ����� ������ }
{ �� ����������� �������� � ������ ��������� }
{ yes - ������� ���������� ��������� ������ ��������� }
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
nC:Integer); {������ ����� �� �����}
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
	�������� ����� � ���������� ������� - ������ ����
}
jC: = jC + 1;
PrintCycle(v, C, nC);
end;
nC: = nC - 1;
end;
end;


procedure DepthCycle;
{������ � ������� �� �������}
var
v : Integer;
begin
jC : = 0; {������� ����� ������}
nC: = 0; {� - ���� ������ ������ }
count: = 0; {����� ����� �������}
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
Reset(f); {���� ������ ��� ������}
{���� ������ ���������}
Read(f, n); {���������� ����� � ������}
Fst[1] : = 0; {��������� ������ ������ ������ ������}
for i: = 1 to n do
begin
Read(f, Vtx[i]); {����� �������}
Read(f, Nbr[i]); {���������� ������ � ������}
for j: = 1 to Nbr[i] do
Read(f, Adj[Fst[i] + j]);
{������ ������� ������}
Fst[i + 1]: = Fst[i] + Nbr[i]; {��������� ������ ��������� ������ � ������}
end;
Close(f);
Assign(f, 'Cycle.out');
Rewrite(f); {���� ������ ��� ������}
Init(yes);
if Not yes then
begin
WriteLn(f, '������ ��������� ��������� �����!');
Close(f);
exit;
end;
DepthCycle;
Close(f);
end. {Main}
