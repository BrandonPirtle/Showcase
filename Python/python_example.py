#########################################################################
# FILENAME :    python_example.py
#
# DESCRIPTION :
#       Exhibits fuctionality of Python3.5
#
# NOTES :
#       Executed using Python3.5
# 
# AUTHOR :    Brandon Pirtle        START DATE :    30 Oct 15
#									EDIT  DATE :    13 Dec 17
#
####

import this # Magic

# Simple swap
print('\n\nSimple Swap:')
a,b=1,2
print(a,b)
a,b=b,a
print(a,b)

# Sets
print('\nSets:')
A = set([1, 2, 3, 3, 4])
B = set([3, 4, 5, 7, 8])
print("A: " + str(A))
print("B: " + str(B))
print("A | B: " + str(A | B)) # A or  B
print("A & B: " + str(A & B)) # A and B
print("A - B: " + str(A - B)) # A without B
print("B - A: " + str(B - A)) # B without A
print("A ^ B: " + str(A ^ B)) # In A or B but not both
print("(A ^ B) == ((A - B) | (B - A)): " + str((A ^ B) == ((A - B) | (B - A)))) # Checking equivalence
print("(A | (B | set([10]))) == set([1, 2, 3, 4, 5, 7, 8, 10]): " + str((A | (B) | set([10]))) == set([1, 2, 3, 4, 5, 7, 8, 10]))

# Short and sweet Bubble Sort
def bubble_sort(data):
	n = len(data)
	while n > 0:
		new_n = 0
		for i in range(1,n):
			if data[i-1] > data[i]:
				data[i-1],data[i]=data[i],data[i-1]
				new_n = i
		n = new_n
	return data

array = [1,2,5,8,3,5,8,2,5]
print('\nBubble Sort:')
print(array)
print(bubble_sort(array))

# Conditional Assignment
print('\nConditional Assignments:')
this = 42
print('this = ',this)
that = 'whoa' if this == 42 else 'lame'
print('that = ',that)
this = 9001
print('this = ',this)
that = 'whoa' if this == 42 else 'lame'
print('that = ',that)

# Formatting (locals() is a dictionary)
print('\nFormatting with \'locals()\':')
print("Is %(this)i %(that)s?" % locals())

# For loop range in assignments
print('\nFor loop range in assignments:')
values = [x for x in range(1,11)]
print(values)

# Multiline strings
print('\nMultiline Strings:')
string1 = "Hello \
World!"
string2 = """Hello
World!"""
string3 = ("Hello "
		   "World!")
print(string1)
print(string2)
print(string3)

# Find string in string
print('\nFind string in string:')
print('Hello' in string1)