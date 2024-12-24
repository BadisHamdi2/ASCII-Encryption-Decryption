while True:
    s=input('Your sentence : ')
    c=''
    for i in s:
        c+=str(ord(i))+' '
    print(c)
