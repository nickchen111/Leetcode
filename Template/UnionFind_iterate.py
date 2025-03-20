def find(x:int)->int:
    rt = x
    while rt != pa[rt]: rt = pa[rt]
    while pa[x] != rt:
        pa[x], x = rt, pa[x]
    return rt
