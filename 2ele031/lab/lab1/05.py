# declaracao de funcao
# def nome_da_funcao():
#     print("Arquivo de funcoes")

# print("Nao se esquecam")
# nome_da_funcao() #chama a funcao nome_da_funcao
# print("da ordem!")

def somaDoisNumeros(n1, n2):
    soma = n1+n2
    print("A soma de n1: {} e n2: {} é: {}".format(n1, n2, soma)) 
    return soma

# somaDoisNumeros(1, 3)

def somaTresNumero():
    n1 = float(input("Insira o n1: "))
    n2 = float(input("Insira o n2: "))
    n3 = float(input("Insira o n3: "))

    soma = n1 + n2 + n3
    print("A soma de n1: {}, n2: {} e n3: {} é: {}".format(n1, n2, n3,soma))

# somaTresNumero()

def somaQuatro(n1, n2, n3, n4):
    soma1 = somaDoisNumeros(n1, n2)
    soma2 = somaDoisNumeros(n3, n4)
    somaFinal = somaDoisNumeros(soma1, soma2)

    print("A soma de {} + {} + {} + {} é: {}".format(n1, n2, n3, n4, somaFinal))

somaQuatro(1, 2, 3, 4)