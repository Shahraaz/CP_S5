# Python3 code to demonstrate 
# generating random strings 
# using random.choices() 
import string 
import random 

# initializing size of string 
N = 100000

# using random.choices() 
# generating random strings 
res = ''.join(random.choices(string.ascii_lowercase, k = N)) 

# print result 
print("1\n" + str(res)) 
