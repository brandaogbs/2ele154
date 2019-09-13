
def calc_preco_cervejada(lote, preco_promocional):

    preco_final = float(preco_promocional)
    if lote == '0':
        return preco_final
    elif lote == '1':
        preco_final = preco_final + 5   
        return preco_final
    elif lote == '2':
        preco_final = preco_final + 10   
        return preco_final
    else:
        preco_final = 50
        return preco_final

lote = input("Qual o lote?")
promocional = input("Qual o promocional?")

print(calc_preco_cervejada(lote, promocional))