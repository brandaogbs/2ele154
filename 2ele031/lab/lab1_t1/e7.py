def calc_preco_cervejada(lote, preco_promocional):

    if str(lote) == "1":
        preco = int(preco_promocional) + 5
    elif str(lote) == "2":
        preco = int(preco_promocional) + 10
    else:
        preco = int(preco_promocional) + 15
    return preco

meu_lote = 1
promo = "30"

preco_final = calc_preco_cervejada(meu_lote, promo)

print("Eu comprei o {} lote por {}".format(meu_lote, preco_final))