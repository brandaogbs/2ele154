# declaracao de uma string
texto = "Eu adoro comer no RU"


print("Texto Original: {}".format(texto))
print("Texto maiusculo: {}".format(texto.upper()))

print("Primeira Letra: {}".format(texto[0]))
print("Ultima Letra: {}".format(texto[-1]))

print("Os primeiros 8 caracter: {}".format(texto[0:8]))
print("A posicao do 'c': {}".format(texto.index('c')))

print("Trocar uma substring: {}".format(texto.replace("RU","BECO").replace("comer", "beber") ))