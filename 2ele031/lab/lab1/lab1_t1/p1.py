# crie um funcao que calcule x^3
# imprima o valor de o cubo de 3 elevado ao cubo
def calc_cubo(x):
    cubo = x*x*x
    return cubo 

numero = int(input("Informe x: "))

cubo = calc_cubo(numero)

print("O cubo do cubo de {} é: {}".format(numero, calc_cubo(cubo)))