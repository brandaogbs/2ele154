falcao = "Eu nao sou cachorro nao"
pato = "oi boi"

print("Texto normal: {}".format(falcao))

print("Texto maiusculo: {}".format(falcao.upper()))
print("Primeira letra: {}".format(falcao[0] ))
print("Ultima letra: {}".format(falcao[-1] ))
print("Oito primeira letras: {}".format(falcao[0:8] ))
print("Onde esta 'o': {}".format(falcao.index('o') ))
print("Quanto 'o' tem?: {}".format(falcao.count('o')))
print("Troca cachorro por pomba: {}".format(falcao.replace("cachorro", "pomba")))