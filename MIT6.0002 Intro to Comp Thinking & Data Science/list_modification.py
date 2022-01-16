def test():
    L = [1,2,3]
    print('origin list: ', end = '')
    print (L)
    def add(L):
        L = L + [1]
    add(L)
    print('after L = L + [1] inside function: ', end = '')
    print(L)
    def add_assign(L):
        L += [1]
    add_assign(L)
    print('after L += [1] inside function: ', end = '')
    print(L)

def test_number():
    L = 5
    print('origin number: ', end = '')
    print (L)
    def add(L):
        L = L + 1
    add(L)
    print('after L = L + 1 inside function: ', end = '')
    print(L)
    def add_assign(L):
        L += 1
    add_assign(L)
    print('after L += 1 inside function: ', end = '')
    print(L)
test()
test_number()