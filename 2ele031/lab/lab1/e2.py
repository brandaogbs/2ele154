# Crie um funcao que recebe a nota final e a porcentagem de faltas e ve se passou ou nao. Media=>60 e faltas<=25 

def passouOuNao(nota, faltas):
    if nota>=60 and faltas<=25:
        return "Passou!!"
  
    elif nota<60 :
        return "Reprovou :´("
  
    elif nota>=60 and faltas>25:
        return "Reprovou por faltas"

print(passouOuNao(100, 0)) #passa
print(passouOuNao(20, 20)) #reprova
print(passouOuNao(63, 30)) #reprovaFalta
