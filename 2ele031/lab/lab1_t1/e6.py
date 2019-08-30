def calc_media(notas):
    soma = notas[0] + notas[1]
    media = soma/2
    return media

lista_notas = []
n1 = input("Nota 1: ")
n2 = input("Nota 2: ")

lista_notas.append(int(n1))
lista_notas.append(int(n2))

minha_media = calc_media(lista_notas)

print(minha_media/10)
