import math
a = 1
b = -5
c = 6
d = b**2 - 4*a*c
if d > 0:
    x1 = (-b + math.sqrt(d)) / (2*a)
    x2 = (-b - math.sqrt(d)) / (2*a)
    print("roots are real and different", x1, x2)
elif d == 0:
    x = -b / (2*a)
    print("equal roots:", x)
else:
    print("not equal roots")