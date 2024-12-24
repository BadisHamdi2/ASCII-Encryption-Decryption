def ConditionsProblem(x):
    if len(x)==0: return True
    else:
        a = x[0]==' '
        b = False
        for i in range(len(x)) :
            b = b or (x[i] not in '0123456789 ')       
        return a or b

while True:
    c=' '
    while ConditionsProblem(c):
        c=input('Your code : ')

    if c[len(c)-1]!=' ':c+=' '
    s=''
    t=''
    for i in range(len(c)) :
        if c[i]!=' ':
            t+=c[i]
        elif ConditionsProblem(t):t=''
        else:
            s+=chr(int(t))
            t=''
    print(s)
