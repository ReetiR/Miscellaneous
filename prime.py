import math

n = int(raw_input())

if n == 1 or n<0:
    print "Not Prime"
elif n % 2 == 0 and n != 2:
    print "Not Prime"
    print "Factor: ", 2
else:
    flag = 0
    for i in xrange(3, int(math.sqrt(n))):
        if n% i == 0:
            print "Not Prime"
            print "Factor: ", i
            flag = 1
            quit()
    if flag==0:
        print "Prime"