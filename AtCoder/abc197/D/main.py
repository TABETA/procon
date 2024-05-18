import cmath
import math

n = int(input())
[x,y] = [int(x) for x in input().split()]
a = complex(x,y)
[x,y] = [int(x) for x in input().split()]
b = complex(x,y)
m = (a+b)/2.0
ans = m + (a-m)*cmath.rect(1,2*math.pi/n)
print(f"{ans.real:.10f} {ans.imag:.10f}")