s = input()
lim = 1
cur = 1
n=len(s)
def test(x):
    # print("line 6", x)
    for i in range(len(s)):
        if s[n-i-1]=='O':
            if x%2==1:
                return None
            if (x-1)%3!=0:
                return None
            x=(x-1)//3
            if x==1:
                return None
        else:
            x=2*x
    # print("Returning", x)
    return x
for i in range(47):
    lim*=2
answers = []
for i in range(150):
    cur*=2
    temp=cur
    y = test(temp)
    if y is None:
        continue
    elif y>lim:
        continue
    else:
        answers.append(y)
if len(answers)==0:
    print("INVALID")
else:
    answers.sort()
    print(int(answers[0]))