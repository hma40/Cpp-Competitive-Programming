s = input()
if(s[-1] == 'E'):
    print("INVALID")
    exit(0)

start = 1
smallest = -1
def IsPow2(n):
    temp = n
    while temp != 1:
        if temp%2==1:
            return False
        temp/=2
    return True
for j in range(150):
    ok = True
    cur = start
    for k in range(len(s)):
        if s[-k-1]=='O':
            if (cur-1)%3 != 0 or (cur-1)//3 %2 != 1:
                ok = False
            else:
                cur=(cur-1)//3
        else:
            cur=cur*2
        if(IsPow2(cur)):
            ok = False
    start*=2
    if not ok:
        continue
    if smallest==-1:
        smallest = cur
    else:
        smallest = min(smallest, cur)
if(smallest==-1): 
    print("INVALID")
else:
    print(smallest)