# 数组乘积
a = [6, 4, 2, 0, 1, 5]
b = []
mul = 1
for i in a:
    if i == 0:
        continue

    mul = mul * i

for i in range(len(a)):
    if 0 in a[:i] or 0 in a[min(len(a), i+1):]:
        b.append(0)
    else:
        if a[i] == 0:
            b.append(mul)
        else:
            b.append(mul / a[i])

print(b)

# 字符串组合
strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
res = dict()
for s in strs:
    ss = sorted(s)
    ss = ''.join(ss)
    if ss in res.keys():
        res[ss].append(s)
    else:
        res[ss] = [s]

print(res)
