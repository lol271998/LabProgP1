
Estrutura ficheiros save

ntoDo -> size de lToDo
nDoing -> size de lDoing
nDone -> size de lDone

Cada tarefa ocupa:

3 linhas para lToDo:
    nome*_*id*_*prioridade
    data de inicio

5 linhas para lDoing:
    nome*_*dono*_*id*_*prioridade
    data de inicio
    data limite

6 linhas para lDone:
    nome*_*dono*_*id*_*prioridade
    data de inicio
    data limite
    data de conclusão

nome        (char*)
dono        (char*)
id          (int)
prioridade  (int)
d m y       (int,int,int)
d m y       (int,int,int)
d m y       (int,int,int)


-------------------------------------------------------------
ntoDo
nome*_*idprioridade
d m y

nDoing
nome
dono
id prioridade
d m y
d m y

nDone
nome
dono
id prioridade
d m y
d m y
d m y


