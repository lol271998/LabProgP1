
Estrutura ficheiros save

ntoDo -> size de lToDo
nDoing -> size de lDoing
nDone -> size de lDone

Cada tarefa ocupa:

4 linhas para lToDo:
    nome
    id
    prioridade
    data de inicio

6 linhas para lDoing:
    nome
    dono
    id
    prioridade
    data de inicio
    data limite

7 linhas para lDone:
    nome
    dono
    id
    prioridade
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
nome
id
prioridade
d m y

nDoing
nome
dono
id
prioridade
d m y
d m y

nDone
nome
dono
id
prioridade
d m y
d m y
d m y


