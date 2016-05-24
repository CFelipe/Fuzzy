import matplotlib.pyplot as plt
import numpy as np

def triangle(x, a1, b, a2):
    if x <= a1:
        return 0
    elif x >= a2:
        return 0
    elif x > a1 and x <= b:
        return (x - a1) / (b - a1)
    elif x > b and x < a2:
        return (a2 - x) / (a2 - b)
    return 0

def trapezoid(x, a1, b1, b2, a2):
    if x <= a1:
        return 0
    elif x >= a2:
        return 0
    elif x > a1 and x <= b1:
        return (x - a1) / (b1 - a1)
    elif x > b2 and x < a2:
        return (a2 - x) / (a2 - b2)
    elif x >= b1 and x <= b2:
        return 1

class Variable:
    def __init__(self, name):
        self.name = name
        self.fuzzy_sets = []

    def add_tri_set(self, name, a1, b, a2):
        fset = {}
        fset["type"] = "tri"
        fset["name"] = name
        fset["a1"] = a1
        fset["b"] = b
        fset["a2"] = a2
        self.fuzzy_sets.append(fset)

    def add_trap_set(self, name, a1, b1, b2, a2):
        fset = {}
        fset["type"] = "trap"
        fset["name"] = name
        fset["a1"] = a1
        fset["a2"] = a2
        fset["b1"] = b1
        fset["b2"] = b2
        self.fuzzy_sets.append(fset)

class Rule():
    def __init__(self, in_vars, out_var):
        self.in_vars = in_vars
        self.out_var = out_var

service = Variable("service")
service.add_tri_set("poor",         -1, 0, 5)
service.add_tri_set("good",         0, 5, 10)
service.add_tri_set("excellent",    5, 10, 15)

food = Variable("food")
food.add_trap_set("awful",       -1, 0, 1, 3)
food.add_trap_set("delicious",   7, 9, 10, 15)

tip = Variable("tip")
tip.add_tri_set("low",      0, 5, 10)
tip.add_tri_set("medium",   10, 15, 20)
tip.add_tri_set("high",     20, 25, 30)

r1_in_vars = [(service, "poor")]
r1_out_var = [(tip, "low")]

r2_in_vars = [(service, "good")]
r2_out_var = [(tip, "medium")]

r3_in_vars = [(service, "excellent")]
r3_out_var = [(tip, "high")]

r4_in_vars = [(food, "awful")]
r4_out_var = [(tip, "low")]

r5_in_vars = [(food, "delicious")]
r5_out_var = [(tip, "high")]

service_in = 7.83
food_in = 7.32

for fset in service.fuzzy_sets:
    if fset["type"] == "tri":
        print(fset["name"])
        print(triangle(service_in, fset["a1"], fset["b"], fset["a2"]))
        print("---")
    elif fset["type"] == "trap":
        print(fset["name"])
        print(trapezoid(service_in, fset["a1"], fset["b1"], fset["b2"], fset["a2"]))
        print("---")

for fset in food.fuzzy_sets:
    if fset["type"] == "tri":
        print(fset["name"])
        print(triangle(food_in, fset["a1"], fset["b"], fset["a2"]))
        print("---")
    elif fset["type"] == "trap":
        print(fset["name"])
        print(trapezoid(food_in, fset["a1"], fset["b1"], fset["b2"], fset["a2"]))
        print("---")


#x = np.arange(0, 10, 0.1)
#trap = [trapezoid(i, 2, 5, 7, 9) for i in x]
#tri = [triangle(i, 1, 3, 8) for i in x]
#op = [triangle(i, 1, 3, 8) + trapezoid(i, 2, 5, 7, 9) - triangle(i, 1, 3, 8) *
#        trapezoid(i, 2, 5, 7, 9) for i in x]
#max_ = [max(triangle(i, 1, 3, 8), trapezoid(i, 2, 5, 7, 9)) for i in x]
#
#plt.gca().set_ylim([-0.1, 1.1])
#plt.plot(x, trap)
#plt.plot(x, tri)
#plt.plot(x, max_)
#plt.plot(x, op)
#
#plt.show()
